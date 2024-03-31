#pragma once
#include "Common/InferenceEngine.h"
#include "Yolov5PrePostProcessor.h"

namespace yolov5
{
    class Yolov5Inference: public Common::InferenceEngine
    {
    private:
        /* data */
    public:
        Yolov5Inference();
        ~Yolov5Inference();

    private:
        Yolov5PrePostProcessor m_pre_post_processor;
    };

}


