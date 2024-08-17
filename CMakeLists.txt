cmake_minimum_required(VERSION 3.22.0)
project(monsoon)

set(CMAKE_CXX_STANDARD 11)
set(CMKAE_VERBOSE_MAKEFILE ON)
#set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -rdynamic -O0 -ggdb -std=c++11 -Wall -Wno-deprecated -Werror -Wno-unused-function")

# 设置输出路径
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

# 设置项目库文件搜索路径 -L
link_directories(${PROJECT_SOURCE_DIR}/lib)

# 添加包含目录，以确保编译器找到头文件
include_directories(${PROJECT_SOURCE_DIR}/src/cmd/include)
include_directories(${PROJECT_SOURCE_DIR}/src/client/include)
include_directories(${PROJECT_SOURCE_DIR}/src/client/sdk/include)
include_directories(${PROJECT_SOURCE_DIR}/src/common/include)
include_directories(${PROJECT_SOURCE_DIR}/src/ipconf/include)
include_directories(${PROJECT_SOURCE_DIR}/src/state/include)

# 查找所有的源文件（.cpp 文件）
file(GLOB_RECURSE SRC_FILES ${CMAKE_SOURCE_DIR}/src/*.cpp)

# 添加可执行文件目标
add_executable(monsoon ${SRC_FILES})

find_package(CLI11 REQUIRED)
find_package(ftxui REQUIRED)

# 添加所有相关代码
add_subdirectory(src)

# 链接 CLI11 库（假设 CLI11 是 header-only 的，不需要实际链接库文件）
target_link_libraries(monsoon CLI11::CLI11 ftxui::dom ftxui::component) 
