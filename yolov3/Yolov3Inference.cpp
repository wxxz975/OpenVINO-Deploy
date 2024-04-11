#include "Yolov3Inference.h"
#include "Yolov3PrePostProcessor.h"

namespace yolov3
{
    Yolov3Inference::Yolov3Inference()
        :Common::InferenceEngine(new Yolov3PrePostProcessor())
    {
    }
    
    Yolov3Inference::~Yolov3Inference()
    {
    }
    
};