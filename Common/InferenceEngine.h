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
        InferenceEngine();
        ~InferenceEngine();

        bool Initialize(const std::string& model_path);

        std::vector<BoundingBox> Infer(const cv::Mat& image);

    protected:

        // 默认只有一个返回
        virtual std::vector<ov::Tensor> Infer(const std::vector<ov::Tensor>& input_tensor);


    protected:
        std::unique_ptr<PrePostProcessor> m_pre_post_processor;

        std::shared_ptr<ov::Model> m_ov_model;
        ov::CompiledModel m_ov_compiled_model;
        ov::InferRequest m_ov_infer_request;
    };
}




