cmake_minimum_required(VERSION 3.10)

project(yolov3)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_BUILD_TYPE Debug)



add_executable(
    ${PROJECT_NAME} 
    main.cpp
    Yolov3Inference.cpp
    Yolov3PrePostProcessor.cpp
    )

target_link_libraries(
    ${PROJECT_NAME}
    ${OpenCV_LIBS}
    openvino::runtime
    Common
)


