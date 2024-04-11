#pragma once
#include "InferenceEngine.h"

namespace yolov3
{
    class Yolov3Inference: public Common::InferenceEngine
    {
    public:
        Yolov3Inference();
        ~Yolov3Inference();
    };
    
    

};