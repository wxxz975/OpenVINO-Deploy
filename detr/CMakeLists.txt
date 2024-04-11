cmake_minimum_required(VERSION 3.14)


project(detr)



# Add executable for the demo
add_executable(
    ${PROJECT_NAME} 
    main.cpp
    detrInference.cpp
    detrPrePostProcessor.cpp
    )



# Link the common library
target_link_libraries(${PROJECT_NAME} 
    Common
    ${OpenCV_LIBS}
    openvino::runtime
    )