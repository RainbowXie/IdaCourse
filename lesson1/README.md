# Build
1. 在 CMakeLists.txt 中设置 NDK 路径
2. 编译 
    ```bash
    cmake -B build -GNinja
    cmake --build build -j4
    ```