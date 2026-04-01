cmake_minimum_required(VERSION 3.20)
project(KineticProject VERSION 0.1.0 LANGUAGES C CXX)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. 查找依赖库
find_package(Qt6 REQUIRED COMPONENTS Widgets WaylandClient)
find_package(PkgConfig REQUIRED)

# 使用 PkgConfig 查找 wlroots 和 wayland 协议
pkg_check_modules(WLR REQUIRED wlroots>=0.17.0)
pkg_check_modules(WAYLAND_PROTOCOLS REQUIRED wayland-protocols)
pkg_check_modules(WAYLAND_CLIENT REQUIRED wayland-client)

# 2. 包含头文件目录
include_directories(
    src
    ${WLR_INCLUDE_DIRS}
    ${WAYLAND_CLIENT_INCLUDE_DIRS}
)

# 3. 定义子目录（后续我们会往里面写代码）
# add_subdirectory(src/compositor)
# add_subdirectory(src/shell/panel)

message(STATUS "Flux Environment 配置完成！")
# 定义可执行文件
add_executable(kinetic-panel src/shell/panel/main.cpp)

# 链接 Qt 库
target_link_libraries(kinetic-panel PRIVATE Qt6::Widgets Qt6::WaylandClient)
# 合成器编译配置
add_executable(kinetic-compositor src/compositor/main.c)

# 链接 wlroots 和 wayland-server
target_link_libraries(kinetic-compositor PRIVATE 
    ${WLR_LIBRARIES} 
    wayland-server
)

# 包含路径
target_include_directories(kinetic-compositor PRIVATE 
    ${WLR_INCLUDE_DIRS}
)
add_definitions(-DWLR_USE_UNSTABLE)
