#pragma once
#include "InferenceEngine.h"

namespace rtdetr
{
    class rtdetrInference: public Common::InferenceEngine
    {
    public:
        rtdetrInference();
        ~rtdetrInference();


    private:
        std::vector<ov::Tensor> InternalInfer(const std::vector<ov::Tensor>& input_tensor) override;

    };
};