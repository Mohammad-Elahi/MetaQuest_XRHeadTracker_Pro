#include <cstdint>
#include <cstdio>
#include <array>
#include <fstream>
#include <chrono>
#include <vector>
#include <string>

#include "XrApp.h"
#include "Input/TinyUI.h"

// Add Passthrough function pointers
PFN_xrCreatePassthroughFB xrCreatePassthroughFB = nullptr;
PFN_xrDestroyPassthroughFB xrDestroyPassthroughFB = nullptr;
PFN_xrPassthroughStartFB xrPassthroughStartFB = nullptr;
PFN_xrPassthroughPauseFB xrPassthroughPauseFB = nullptr;
PFN_xrCreatePassthroughLayerFB xrCreatePassthroughLayerFB = nullptr;
PFN_xrDestroyPassthroughLayerFB xrDestroyPassthroughLayerFB = nullptr;
PFN_xrPassthroughLayerSetStyleFB xrPassthroughLayerSetStyleFB = nullptr;
PFN_xrPassthroughLayerPauseFB xrPassthroughLayerPauseFB = nullptr;
PFN_xrPassthroughLayerResumeFB xrPassthroughLayerResumeFB = nullptr;

class XrBodyFaceEyeSocialApp : public OVRFW::XrApp {
public:
    XrBodyFaceEyeSocialApp() : OVRFW::XrApp() {
        BackgroundColor = OVR::Vector4f(0.0f, 0.0f, 0.0f, 0.0f);
    }

    virtual std::vector<const char*> GetExtensions() override {
        std::vector<const char*> extensions = XrApp::GetExtensions();
        extensions.push_back(XR_FB_PASSTHROUGH_EXTENSION_NAME);
        return extensions;
    }

    virtual bool AppInit(const xrJava* context) override {
        if (false == ui_.Init(context, GetFileSys())) {
            ALOG("TinyUI::Init FAILED.");
            return false;
        }

        // Initialize Passthrough function pointers
        OXR(xrGetInstanceProcAddr(GetInstance(), "xrCreatePassthroughFB", (PFN_xrVoidFunction*)&xrCreatePassthroughFB));
        OXR(xrGetInstanceProcAddr(GetInstance(), "xrDestroyPassthroughFB", (PFN_xrVoidFunction*)&xrDestroyPassthroughFB));
        OXR(xrGetInstanceProcAddr(GetInstance(), "xrPassthroughStartFB", (PFN_xrVoidFunction*)&xrPassthroughStartFB));
        OXR(xrGetInstanceProcAddr(GetInstance(), "xrPassthroughPauseFB", (PFN_xrVoidFunction*)&xrPassthroughPauseFB));
        OXR(xrGetInstanceProcAddr(GetInstance(), "xrCreatePassthroughLayerFB", (PFN_xrVoidFunction*)&xrCreatePassthroughLayerFB));
        OXR(xrGetInstanceProcAddr(GetInstance(), "xrDestroyPassthroughLayerFB", (PFN_xrVoidFunction*)&xrDestroyPassthroughLayerFB));
        OXR(xrGetInstanceProcAddr(GetInstance(), "xrPassthroughLayerSetStyleFB", (PFN_xrVoidFunction*)&xrPassthroughLayerSetStyleFB));
        OXR(xrGetInstanceProcAddr(GetInstance(), "xrPassthroughLayerPauseFB", (PFN_xrVoidFunction*)&xrPassthroughLayerPauseFB));
        OXR(xrGetInstanceProcAddr(GetInstance(), "xrPassthroughLayerResumeFB", (PFN_xrVoidFunction*)&xrPassthroughLayerResumeFB));

        return true;
    }

    virtual void AppShutdown(const xrJava* context) override {
        SaveHeadTrackingDataToCSV();
        ui_.Shutdown();
        OVRFW::XrApp::AppShutdown(context);
    }

    virtual bool SessionInit() override {
        if (!OVRFW::XrApp::SessionInit()) {
            return false;
        }

        // Create Passthrough
        XrPassthroughCreateInfoFB ptci = {XR_TYPE_PASSTHROUGH_CREATE_INFO_FB};
        OXR(xrCreatePassthroughFB(GetSession(), &ptci, &passthrough));

        // Create Passthrough Layer
        XrPassthroughLayerCreateInfoFB plci = {XR_TYPE_PASSTHROUGH_LAYER_CREATE_INFO_FB};
        plci.passthrough = passthrough;
        plci.purpose = XR_PASSTHROUGH_LAYER_PURPOSE_RECONSTRUCTION_FB;
        OXR(xrCreatePassthroughLayerFB(GetSession(), &plci, &passthroughLayer));

        // Start Passthrough
        OXR(xrPassthroughStartFB(passthrough));
        OXR(xrPassthroughLayerResumeFB(passthroughLayer));

        return true;
    }

    virtual void SessionEnd() override {
        // Stop and destroy Passthrough
        if (passthrough != XR_NULL_HANDLE) {
            OXR(xrPassthroughPauseFB(passthrough));
            OXR(xrDestroyPassthroughLayerFB(passthroughLayer));
            OXR(xrDestroyPassthroughFB(passthrough));
            passthrough = XR_NULL_HANDLE;
            passthroughLayer = XR_NULL_HANDLE;
        }

        ui_.Shutdown();
    }

    virtual void Update(const OVRFW::ovrApplFrameIn& in) override {
        CollectHeadTrackingData(in);
        ui_.Update(in);
    }

    virtual void Render(const OVRFW::ovrApplFrameIn& in, OVRFW::ovrRendererOutput& out) override {
        ui_.Render(in, out);

        // Add Passthrough layer to the frame
        XrCompositionLayerPassthroughFB passthrough_layer = {XR_TYPE_COMPOSITION_LAYER_PASSTHROUGH_FB};
        passthrough_layer.layerHandle = passthroughLayer;
        passthrough_layer.flags = XR_COMPOSITION_LAYER_BLEND_TEXTURE_SOURCE_ALPHA_BIT;
        passthrough_layer.space = XR_NULL_HANDLE;

        layerList.push_back(reinterpret_cast<XrCompositionLayerBaseHeader*>(&passthrough_layer));
    }

private:
    OVRFW::TinyUI ui_;
    XrPassthroughFB passthrough = XR_NULL_HANDLE;
    XrPassthroughLayerFB passthroughLayer = XR_NULL_HANDLE;
    std::vector<XrCompositionLayerBaseHeader*> layerList;

    struct HeadTrackingData {
        int64_t timestamp;
        float posX, posY, posZ;
        float rotQx, rotQy, rotQz, rotQw;
    };

    std::vector<HeadTrackingData> headTrackingData;

    void CollectHeadTrackingData(const OVRFW::ovrApplFrameIn& in) {
        XrSpaceLocation viewLocation{XR_TYPE_SPACE_LOCATION};
        OXR(xrLocateSpace(GetHeadSpace(), GetStageSpace(), ToXrTime(in.PredictedDisplayTime), &viewLocation));

        if ((viewLocation.locationFlags & XR_SPACE_LOCATION_POSITION_VALID_BIT) != 0 &&
            (viewLocation.locationFlags & XR_SPACE_LOCATION_ORIENTATION_VALID_BIT) != 0) {

            HeadTrackingData data;
            data.timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(
                    std::chrono::system_clock::now().time_since_epoch()).count();
            data.posX = viewLocation.pose.position.x;
            data.posY = viewLocation.pose.position.y;
            data.posZ = viewLocation.pose.position.z;
            data.rotQx = viewLocation.pose.orientation.x;
            data.rotQy = viewLocation.pose.orientation.y;
            data.rotQz = viewLocation.pose.orientation.z;
            data.rotQw = viewLocation.pose.orientation.w;

            headTrackingData.push_back(data);
        }
    }

    void SaveHeadTrackingDataToCSV() {
        const std::string filePath = "/storage/emulated/0/Download/HeadsetTrackingData.csv";
        std::ofstream file(filePath);

        if (file.is_open()) {
            file << "Timestamp,PositionX,PositionY,PositionZ,RotationQx,RotationQy,RotationQz,RotationQw\n";

            for (const auto& data : headTrackingData) {
                file << data.timestamp << ","
                     << data.posX << "," << data.posY << "," << data.posZ << ","
                     << data.rotQx << "," << data.rotQy << "," << data.rotQz << "," << data.rotQw << "\n";
            }

            file.close();
            ALOG("Head tracking data saved to: %s", filePath.c_str());
        } else {
            ALOG("Failed to open file for saving head tracking data");
        }
    }
};

ENTRY_POINT(XrBodyFaceEyeSocialApp);