#include "Yolov7Inference.h"

#include "Yolov7PrePostProcessor.h"

namespace yolov7
{
    Yolov7Inference::Yolov7Inference()
        :Common::InferenceEngine(new Yolov7PrePostProcessor())
    {
        
    }

    Yolov7Inference::~Yolov7Inference()
    {
    }
}

