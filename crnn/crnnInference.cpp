#include "crnnInference.h"
#include "crnnPrePostProcessor.h"
#include "Filesystem.h"


namespace crnn
{
    
    crnnInference::crnnInference()
        :m_pre_post_processor(new crnnPrePostProcessor())
    {

    }
    
    crnnInference::~crnnInference()
    {

        
    }

    bool crnnInference::Initialize(const std::string &model_path)
    {
        if(!Common::IFilesystem::IsExist(model_path))
            return false;
        ov::Core ov_core;
        m_ov_model = ov_core.read_model(model_path);
        m_ov_model = m_pre_post_processor->OvPrePostprocessing(m_ov_model);

        m_ov_compiled_model = ov_core.compile_model(m_ov_model, "AUTO");

        m_ov_infer_request = m_ov_compiled_model.create_infer_request();

        return true;
    }
    
    std::string crnnInference::Infer(const cv::Mat &image)
    {
        std::vector<ov::Tensor> input_tensor = m_pre_post_processor->Preprocessing(image);

        std::vector<ov::Tensor> output_tensor = InternalInfer(input_tensor);

        return m_pre_post_processor->Postprocessing(output_tensor);
    }

    std::vector<ov::Tensor> crnnInference::InternalInfer(const std::vector<ov::Tensor>& input_tensor)
    {
        m_ov_infer_request.set_input_tensors(input_tensor);
        m_ov_infer_request.infer();

        return {m_ov_infer_request.get_output_tensor()};
    }
};