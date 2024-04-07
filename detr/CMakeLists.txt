cmake_minimum_required(VERSION 3.14)


project(detr)


find_package(OpenVINO COMPONENTS Runtime)
include_directories(${OpenVINO_INCLUDE_DIRS}/include)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_subdirectory(../Common Common)

# Add executable for the demo
add_executable(
    ${PROJECT_NAME} 
    main.cpp
    detrInference.cpp
    detrPrePostProcessor.cpp
    )


add_dependencies(${CMAKE_PROJECT_NAME} Common)



# Link the common library
target_link_libraries(${PROJECT_NAME} 
    Common
    ${OpenCV_LIBS}
    openvino::runtime
    )