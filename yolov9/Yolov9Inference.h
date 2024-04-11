#pragma once

#include "InferenceEngine.h"

namespace yolov9
{

    class Yolov9Inference: public Common::InferenceEngine
    {
    private:
        /* data */
    public:
        Yolov9Inference();
        ~Yolov9Inference();



        std::vector<ov::Tensor> InternalInfer(const std::vector<ov::Tensor>& input_tensor) override;

    };
    
    
    


}