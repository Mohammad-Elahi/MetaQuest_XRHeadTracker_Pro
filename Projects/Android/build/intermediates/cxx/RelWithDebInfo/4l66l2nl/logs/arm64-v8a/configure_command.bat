@echo off
"C:\\Users\\Mohammad.Elahi\\AppData\\Local\\Android\\Sdk\\cmake\\3.22.1\\bin\\cmake.exe" ^
  "-HA:\\Mohammad\\Android\\XRProject- 23.10\\Samples" ^
  "-DCMAKE_SYSTEM_NAME=Android" ^
  "-DCMAKE_EXPORT_COMPILE_COMMANDS=ON" ^
  "-DCMAKE_SYSTEM_VERSION=29" ^
  "-DANDROID_PLATFORM=android-29" ^
  "-DANDROID_ABI=arm64-v8a" ^
  "-DCMAKE_ANDROID_ARCH_ABI=arm64-v8a" ^
  "-DANDROID_NDK=C:\\Users\\Mohammad.Elahi\\AppData\\Local\\Android\\Sdk\\ndk\\26.3.11579264" ^
  "-DCMAKE_ANDROID_NDK=C:\\Users\\Mohammad.Elahi\\AppData\\Local\\Android\\Sdk\\ndk\\26.3.11579264" ^
  "-DCMAKE_TOOLCHAIN_FILE=C:\\Users\\Mohammad.Elahi\\AppData\\Local\\Android\\Sdk\\ndk\\26.3.11579264\\build\\cmake\\android.toolchain.cmake" ^
  "-DCMAKE_MAKE_PROGRAM=C:\\Users\\Mohammad.Elahi\\AppData\\Local\\Android\\Sdk\\cmake\\3.22.1\\bin\\ninja.exe" ^
  "-DCMAKE_LIBRARY_OUTPUT_DIRECTORY=A:\\Mohammad\\Android\\XRProject- 23.10\\Samples\\XrSamples\\XrBodyFaceEyeSocial\\Projects\\Android\\build\\intermediates\\cxx\\RelWithDebInfo\\4l66l2nl\\obj\\arm64-v8a" ^
  "-DCMAKE_RUNTIME_OUTPUT_DIRECTORY=A:\\Mohammad\\Android\\XRProject- 23.10\\Samples\\XrSamples\\XrBodyFaceEyeSocial\\Projects\\Android\\build\\intermediates\\cxx\\RelWithDebInfo\\4l66l2nl\\obj\\arm64-v8a" ^
  "-DCMAKE_BUILD_TYPE=RelWithDebInfo" ^
  "-DCMAKE_FIND_ROOT_PATH=A:\\Mohammad\\Android\\XRProject- 23.10\\Samples\\XrSamples\\XrBodyFaceEyeSocial\\Projects\\Android\\.cxx\\RelWithDebInfo\\4l66l2nl\\prefab\\arm64-v8a\\prefab" ^
  "-BA:\\Mohammad\\Android\\XRProject- 23.10\\Samples\\XrSamples\\XrBodyFaceEyeSocial\\Projects\\Android\\.cxx\\RelWithDebInfo\\4l66l2nl\\arm64-v8a" ^
  -GNinja