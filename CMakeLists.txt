cmake_minimum_required(VERSION 3.14)

# Define your project name
project(OpenVINO-Deploy)


find_package(OpenVINO COMPONENTS Runtime)
include_directories(${OpenVINO_INCLUDE_DIRS}/include)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})


# Add subdirectories
add_subdirectory(Common)
add_subdirectory(yolov3)
add_subdirectory(yolov5)
add_subdirectory(yolov7)
add_subdirectory(yolov8)
add_subdirectory(yolov9)

add_subdirectory(rtdetr)