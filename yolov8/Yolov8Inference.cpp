#include "Yolov8Inference.h"

#include "Yolov8PrePostProcessor.h"

namespace yolov8
{
    
    Yolov8Inference::Yolov8Inference()
        :InferenceEngine(new Yolov8PrePostProcessor())
    {
    }

    Yolov8Inference::~Yolov8Inference()
    {
    }


};