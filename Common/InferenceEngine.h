#pragma once

#include <string>

#include "PrePostProcessor.h"

namespace Common
{
    class InferenceEngine
    {
    private:
        /* data */
    public:
        InferenceEngine(PrePostProcessor* pre_post_processor);
        virtual ~InferenceEngine();

        bool Initialize(const std::string& model_path);

        /// @brief 输入图像，进行推理
        /// @param image 
        /// @return 
        std::vector<BoundingBox> Infer(const cv::Mat& image);

    protected:

        /// @brief 
        /// @param input_tensor 
        /// @return 
        virtual std::vector<ov::Tensor> Infer(const std::vector<ov::Tensor>& input_tensor);

        /// @brief 判断GPU是否可用
        /// @return true 则可用
        bool IsGPUAvailable();


        

    protected:
        std::unique_ptr<PrePostProcessor> m_pre_post_processor;

        std::shared_ptr<ov::Model> m_ov_model;
        ov::CompiledModel m_ov_compiled_model;
        ov::InferRequest m_ov_infer_request;
    };
}




