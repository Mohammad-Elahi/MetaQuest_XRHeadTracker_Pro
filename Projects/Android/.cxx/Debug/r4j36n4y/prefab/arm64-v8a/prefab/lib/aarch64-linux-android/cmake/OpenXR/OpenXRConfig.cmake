if(NOT TARGET OpenXR::headers)
add_library(OpenXR::headers INTERFACE IMPORTED)
set_target_properties(OpenXR::headers PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "C:/Users/Mohammad.Elahi/.gradle/caches/transforms-4/bd05a00a237c14c43f0c4fabb9c2fc44/transformed/openxr_loader_for_android-1.1.41/prefab/modules/headers/include"
    INTERFACE_LINK_LIBRARIES ""
)
endif()

if(NOT TARGET OpenXR::openxr_loader)
add_library(OpenXR::openxr_loader SHARED IMPORTED)
set_target_properties(OpenXR::openxr_loader PROPERTIES
    IMPORTED_LOCATION "C:/Users/Mohammad.Elahi/.gradle/caches/transforms-4/bd05a00a237c14c43f0c4fabb9c2fc44/transformed/openxr_loader_for_android-1.1.41/prefab/modules/openxr_loader/libs/android.arm64-v8a/libopenxr_loader.so"
    INTERFACE_LINK_LIBRARIES "OpenXR::headers"
)
endif()

