#pragma once

#include <string>
#include <opencv2/opencv.hpp>

#include "crnnPrePostProcessor.h"

namespace crnn
{
    class crnnInference
    {
    private:
        
    public:
        crnnInference(/* args */);
        ~crnnInference();

        bool Initialize(const std::string& model_path);

        std::string Infer(const cv::Mat& image);
    private:
        std::vector<ov::Tensor> InternalInfer(const std::vector<ov::Tensor>& input_tensor);

    private:
        std::unique_ptr<crnnPrePostProcessor> m_pre_post_processor;

        std::shared_ptr<ov::Model> m_ov_model;
        ov::CompiledModel m_ov_compiled_model;
        ov::InferRequest m_ov_infer_request;
    };
    
    

};