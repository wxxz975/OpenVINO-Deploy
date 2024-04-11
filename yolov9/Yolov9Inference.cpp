#include "Yolov9Inference.h"

#include "Yolov9PrePostProcessor.h"


namespace yolov9
{
    Yolov9Inference::Yolov9Inference(/* args */)
        :Common::InferenceEngine(new Yolov9PrePostProcessor())
    {
        
    }
    
    Yolov9Inference::~Yolov9Inference()
    {
    }

    std::vector<ov::Tensor> Yolov9Inference::InternalInfer(const std::vector<ov::Tensor> &input_tensor)
    {
        m_ov_infer_request.set_input_tensors(input_tensor);
        m_ov_infer_request.infer();

        return {m_ov_infer_request.get_output_tensor(0)};
    }
}