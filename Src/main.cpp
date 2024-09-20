#include <cstdint>
#include <cstdio>
#include <array>
#include <fstream>
#include <chrono>
#include <vector>
#include <string>

#include "XrApp.h"
#include "Input/TinyUI.h"


class XrBodyFaceEyeSocialApp : public OVRFW::XrApp {
public:
    XrBodyFaceEyeSocialApp() : OVRFW::XrApp() {
        BackgroundColor = OVR::Vector4f(0.60f, 0.95f, 0.4f, 1.0f);
    }

    // Returns a list of OpenXr extensions needed for this app
    virtual std::vector<const char*> GetExtensions() override {
        std::vector<const char*> extensions = XrApp::GetExtensions();
        return extensions;
    }

    virtual bool AppInit(const xrJava* context) override {
        if (false == ui_.Init(context, GetFileSys())) {
            ALOG("TinyUI::Init FAILED.");
            return false;
        }
        return true;
    }

    virtual void AppShutdown(const xrJava* context) override {
        // Save collected data to CSV file
        SaveHeadTrackingDataToCSV();

        ui_.Shutdown();
        OVRFW::XrApp::AppShutdown(context);
    }

    virtual bool SessionInit() override {
        return true;
    }

    virtual void SessionEnd() override {
        ui_.Shutdown();
    }

    virtual void Update(const OVRFW::ovrApplFrameIn& in) override {
        // Collect head tracking data
        CollectHeadTrackingData(in);

        ui_.Update(in);
    }

    virtual void Render(const OVRFW::ovrApplFrameIn& in, OVRFW::ovrRendererOutput& out) override {
        ui_.Render(in, out);
    }

private:
    OVRFW::TinyUI ui_;

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

