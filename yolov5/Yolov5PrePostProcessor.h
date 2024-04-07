#pragma once
#include "PrePostProcessor.h"


namespace yolov5
{
    class Yolov5PrePostProcessor: public Common::PrePostProcessor
    {
    private:
        /* data */
    public:
        Yolov5PrePostProcessor();
        ~Yolov5PrePostProcessor();

    public:

        std::shared_ptr<ov::Model> OvPrePostprocessing(std::shared_ptr<ov::Model> ov_model) override;

        std::vector<Common::BoundingBox> Postprocessing(std::vector<ov::Tensor>& output_tensor) override;

        std::vector<ov::Tensor> Preprocessing(const cv::Mat& image) override;

    private:
        

        std::vector<ov::Tensor> CreateTensor(const cv::Mat& image);

        

        
        std::size_t m_input_width;
        std::size_t m_input_height;
        std::size_t m_input_channels;

        std::vector<std::size_t> m_input_dims;
        std::vector<std::size_t> m_output_dims;

        const std::size_t m_input_batch = 1;
    };

}


