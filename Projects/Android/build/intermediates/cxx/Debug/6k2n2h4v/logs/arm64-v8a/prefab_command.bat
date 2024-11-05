@echo off
"C:\\Program Files\\Android\\Android Studio\\jbr\\bin\\java" ^
  --class-path ^
  "C:\\Users\\Mohammad.Elahi\\.gradle\\caches\\modules-2\\files-2.1\\com.google.prefab\\cli\\2.1.0\\aa32fec809c44fa531f01dcfb739b5b3304d3050\\cli-2.1.0-all.jar" ^
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
  26 ^
  --output ^
  "C:\\Users\\MOHAMM~1.ELA\\AppData\\Local\\Temp\\agp-prefab-staging11910675178782677375\\staged-cli-output" ^
  "C:\\Users\\Mohammad.Elahi\\.gradle\\caches\\transforms-4\\bd05a00a237c14c43f0c4fabb9c2fc44\\transformed\\openxr_loader_for_android-1.1.41\\prefab"
