cmake_minimum_required(VERSION 3.14)

project(Common)

find_package(OpenVINO COMPONENTS Runtime)
include_directories(${OpenVINO_INCLUDE_DIRS}/include)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})


# Add block of files to the project
add_library(${CMAKE_PROJECT_NAME} 
    STATIC 
    src/ImageOperations.cpp
    src/InferenceEngine.cpp
    src/PrePostProcessor.cpp
    )

target_link_libraries(
    ${CMAKE_PROJECT_NAME}
    ${OpenCV_LIBS}
    openvino::runtime
)

target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)






