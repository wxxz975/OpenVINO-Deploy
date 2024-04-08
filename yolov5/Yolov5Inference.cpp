#include "Yolov5Inference.h"

#include "Yolov5PrePostProcessor.h"

namespace yolov5
{
    Yolov5Inference::Yolov5Inference()
        :Common::InferenceEngine(new Yolov5PrePostProcessor())
    {
        
    }

    Yolov5Inference::~Yolov5Inference()
    {
    }
}

