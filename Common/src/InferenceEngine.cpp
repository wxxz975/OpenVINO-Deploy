#include "InferenceEngine.h"
#include "Filesystem.h"

namespace Common
{
    InferenceEngine::InferenceEngine(PrePostProcessor* pre_post_processor)
        :m_pre_post_processor(pre_post_processor)
    {

    }

    InferenceEngine::~InferenceEngine()
    {

    }

    bool InferenceEngine::Initialize(const std::string& model_path)
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

    std::vector<BoundingBox> InferenceEngine::Infer(const cv::Mat& image)
    {   
        std::vector<ov::Tensor> input_tensor = m_pre_post_processor->Preprocessing(image);

        std::vector<ov::Tensor> output_tensor = InternalInfer(input_tensor);

        return m_pre_post_processor->Postprocessing(output_tensor);
    }

    std::vector<ov::Tensor> InferenceEngine::InternalInfer(const std::vector<ov::Tensor>& input_tensor)
    {
        m_ov_infer_request.set_input_tensors(input_tensor);
        m_ov_infer_request.infer();

        return {m_ov_infer_request.get_output_tensor()};
    }

    bool InferenceEngine::IsGPUAvailable()
    {
        ov::Core ov_core;
        std::vector<std::string> avaliableDevice = ov_core.get_available_devices();
    
        auto iter = std::find(avaliableDevice.begin(), avaliableDevice.end(), "GPU");

        return iter != avaliableDevice.end();
    }
}


