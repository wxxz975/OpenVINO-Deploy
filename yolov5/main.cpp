#include "Yolov5Inference.h"



int main(int argc, char* argv[])
{
    yolov5::Yolov5Inference infer;

    if(infer.Initialize("/home/wxxz/workspace/weights/x_ray.onnx")) {
        
    }

    return 0;
}