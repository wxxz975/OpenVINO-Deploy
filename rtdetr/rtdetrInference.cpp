#include "rtdetrInference.h"

#include "rtdetrPrePostProcessor.h"

namespace rtdetr
{
    rtdetrInference::rtdetrInference()
        :Common::InferenceEngine(new rtdetrPrePostProcessor())
    {
    }
    
    rtdetrInference::~rtdetrInference()
    {
    }

    std::vector<ov::Tensor> rtdetrInference::InternalInfer(const std::vector<ov::Tensor> &input_tensor)
    {
        m_ov_infer_request.set_input_tensors(input_tensor);
        m_ov_infer_request.infer();

        return {m_ov_infer_request.get_output_tensor()};
    }
};