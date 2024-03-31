#include "Yolov5Inference.h"



namespace yolov5
{
    Yolov5Inference::Yolov5Inference()
        :m_pre_post_processor(m_ov_compiled_model), Common::InferenceEngine(&m_pre_post_processor)
    {
        
    }

    Yolov5Inference::~Yolov5Inference()
    {
    }
}

