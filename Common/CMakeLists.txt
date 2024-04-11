cmake_minimum_required(VERSION 3.14)

project(Common)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


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

#message("CMakeProjectName:${CMAKE_PROJECT_NAME}" )  # 这个展示的是整个项目的名称
#message("ProjectName:${PROJECT_NAME}")  # 这个展示的是当前CMakeLists的名称
#message("CMAKE_CURRENT_SOURCE_DIR:${CMAKE_CURRENT_SOURCE_DIR}") # 这个是当前CMakeLists.txt项目的路径
#message("CMAKE_SOURCE_DIR:${CMAKE_SOURCE_DIR}") # 这个是整个项目根目录



