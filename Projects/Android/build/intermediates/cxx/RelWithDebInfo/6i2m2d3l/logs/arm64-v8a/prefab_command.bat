@echo off
"C:\\Program Files\\Android\\Android Studio\\jbr\\bin\\java" ^
  --class-path ^
  "C:\\Users\\Mohammad.Elahi\\.gradle\\caches\\modules-2\\files-2.1\\com.google.prefab\\cli\\2.0.0\\f2702b5ca13df54e3ca92f29d6b403fb6285d8df\\cli-2.0.0-all.jar" ^
  com.google.prefab.cli.AppKt ^
  --build-system ^
  cmake ^
  --platform ^
  android ^
  --abi ^
  arm64-v8a ^
  --os-version ^
  26 ^
  --stl ^
  c++_static ^
  --ndk-version ^
  23 ^
  --output ^
  "C:\\Users\\MOHAMM~1.ELA\\AppData\\Local\\Temp\\agp-prefab-staging13673766294254318498\\staged-cli-output" ^
  "C:\\Users\\Mohammad.Elahi\\.gradle\\caches\\transforms-3\\d88a0c0ce9d00191a3a2fe3115bb6df7\\transformed\\openxr_loader_for_android-1.1.36\\prefab"
