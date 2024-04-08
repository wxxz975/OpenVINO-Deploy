#pragma once

#include "PrePostProcessor.h"

namespace yolov8
{
    class Yolov8PrePostProcessor: public Common::PrePostProcessor
    {
    private:
        /* data */
    public:
        Yolov8PrePostProcessor();
        ~Yolov8PrePostProcessor();

        std::shared_ptr<ov::Model> OvPrePostprocessing(std::shared_ptr<ov::Model> ov_model) override;

        std::vector<Common::BoundingBox> Postprocessing(std::vector<ov::Tensor>& output_tensor) override;

        std::vector<ov::Tensor> Preprocessing(const cv::Mat& image) override;


        cv::Mat m_tmp;

        cv::Size m_original_shape;
        cv::Size m_current_shape;


        std::vector<std::size_t> m_input_dims;
        std::size_t m_input_width;
        
    
    };
    
    
    

}