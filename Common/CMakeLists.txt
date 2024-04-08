cmake_minimum_required(VERSION 3.14)

project(Common)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(OpenVINO COMPONENTS Runtime)
include_directories(${OpenVINO_INCLUDE_DIRS}/include)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})


include_directories(${CMAKE_SOURCE_DIR}/include)

add_library(
        ${PROJECT_NAME}
        STATIC
        src/ImageOperations.cpp
        src/InferenceEngine.cpp
        src/PrePostProcessor.cpp
        src/Utils.cpp
    )

target_link_libraries(
    ${PROJECT_NAME}
    ${OpenCV_LIBS}
    openvino::runtime
)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

message("CMakeProjectName:${CMAKE_PROJECT_NAME}" )  # 这个展示的是整个项目的名称
message("ProjectName:${PROJECT_NAME}")  # 这个展示的是当前CMakeLists的名称



