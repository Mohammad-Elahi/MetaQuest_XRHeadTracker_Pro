@echo off
"C:\\Users\\Mohammad.Elahi\\AppData\\Local\\Android\\Sdk\\cmake\\3.22.1\\bin\\cmake.exe" ^
  "-HA:\\Mohammad\\XRProject- Android head tracking\\Samples" ^
  "-DCMAKE_SYSTEM_NAME=Android" ^
  "-DCMAKE_EXPORT_COMPILE_COMMANDS=ON" ^
  "-DCMAKE_SYSTEM_VERSION=26" ^
  "-DANDROID_PLATFORM=android-26" ^
  "-DANDROID_ABI=arm64-v8a" ^
  "-DCMAKE_ANDROID_ARCH_ABI=arm64-v8a" ^
  "-DANDROID_NDK=C:\\Users\\Mohammad.Elahi\\AppData\\Local\\Android\\Sdk\\ndk\\26.1.10909125" ^
  "-DCMAKE_ANDROID_NDK=C:\\Users\\Mohammad.Elahi\\AppData\\Local\\Android\\Sdk\\ndk\\26.1.10909125" ^
  "-DCMAKE_TOOLCHAIN_FILE=C:\\Users\\Mohammad.Elahi\\AppData\\Local\\Android\\Sdk\\ndk\\26.1.10909125\\build\\cmake\\android.toolchain.cmake" ^
  "-DCMAKE_MAKE_PROGRAM=C:\\Users\\Mohammad.Elahi\\AppData\\Local\\Android\\Sdk\\cmake\\3.22.1\\bin\\ninja.exe" ^
  "-DCMAKE_LIBRARY_OUTPUT_DIRECTORY=A:\\Mohammad\\XRProject- Android head tracking\\Samples\\XrSamples\\XrBodyFaceEyeSocial\\Projects\\Android\\build\\intermediates\\cxx\\RelWithDebInfo\\525z326u\\obj\\arm64-v8a" ^
  "-DCMAKE_RUNTIME_OUTPUT_DIRECTORY=A:\\Mohammad\\XRProject- Android head tracking\\Samples\\XrSamples\\XrBodyFaceEyeSocial\\Projects\\Android\\build\\intermediates\\cxx\\RelWithDebInfo\\525z326u\\obj\\arm64-v8a" ^
  "-DCMAKE_BUILD_TYPE=RelWithDebInfo" ^
  "-DCMAKE_FIND_ROOT_PATH=A:\\Mohammad\\XRProject- Android head tracking\\Samples\\XrSamples\\XrBodyFaceEyeSocial\\Projects\\Android\\.cxx\\RelWithDebInfo\\525z326u\\prefab\\arm64-v8a\\prefab" ^
  "-BA:\\Mohammad\\XRProject- Android head tracking\\Samples\\XrSamples\\XrBodyFaceEyeSocial\\Projects\\Android\\.cxx\\RelWithDebInfo\\525z326u\\arm64-v8a" ^
  -GNinja
