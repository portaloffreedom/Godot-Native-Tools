# Godot-Native-Tools
Tools for godot written in GDNative C++

## How to configure an android build
ARM 32bits
```
cmake .. -DANDROID_NDK_ROOT=/opt/android-ndk/ -DCMAKE_TOOLCHAIN_FILE=/opt/android-ndk/build/cmake/android.toolchain.cmake -DANDROID_TOOLCHAIN_NAME=llvm -DANDROID_ABI="armeabi-v7a with NEON"
```

ARM 64bits
```
cmake .. -DANDROID_NDK_ROOT=/opt/android-ndk/ -DCMAKE_TOOLCHAIN_FILE=/opt/android-ndk/build/cmake/android.toolchain.cmake -DANDROID_TOOLCHAIN_NAME=llvm -DANDROID_ABI=arm64-v8a
```

x86
```
cmake .. -DANDROID_NDK_ROOT=/opt/android-ndk/ -DCMAKE_TOOLCHAIN_FILE=/opt/android-ndk/build/cmake/android.toolchain.cmake -DANDROID_TOOLCHAIN_NAME=llvm -DANDROID_ABI=x86
```

x86_64
```
cmake .. -DANDROID_NDK_ROOT=/opt/android-ndk/ -DCMAKE_TOOLCHAIN_FILE=/opt/android-ndk/build/cmake/android.toolchain.cmake -DANDROID_TOOLCHAIN_NAME=llvm -DANDROID_ABI=x86_64
```