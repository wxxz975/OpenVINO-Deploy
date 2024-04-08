cmake_minimum_required(VERSION 3.14)

# Define your project name
project(OpenVINO-Deploy)

# Add subdirectories
add_subdirectory(Common)
add_subdirectory(yolov5)

add_subdirectory(yolov8)