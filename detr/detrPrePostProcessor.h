#pragma once
#include "PrePostProcessor.h"

namespace detr
{

    struct detrRawOutput
    {
        float cx;
        float cy;
        float bw;
        float bh;
        // n confidence
    };
    typedef detrRawOutput* pDetrRawOutput;
    #define DETR_ELE_SIZE  (sizeof(detrRawOutput) / sizeof(float))

    class detrPrePostProcessor: public Common::PrePostProcessor
    {
    private:
        /* data */
    public:
        detrPrePostProcessor();
        ~detrPrePostProcessor();

        std::vector<ov::Tensor> Preprocessing(const cv::Mat& image) override;

        std::vector<Common::BoundingBox> Postprocessing(std::vector<ov::Tensor>& output_tensor) override;

        std::shared_ptr<ov::Model> OvPrePostprocessing(std::shared_ptr<ov::Model> ov_model) override;

    private:
        std::vector<ov::Tensor> CreateTensor(const cv::Mat& image);

    private:
        const std::size_t m_input_batch = 1;
        std::size_t m_input_width;
        std::size_t m_input_height;
        std::size_t m_input_channels;

        const std::vector<float> m_means = {0.485, 0.456, 0.406}; // Subtracts
        const std::vector<float> m_std = {0.229, 0.224, 0.225}; // Divides each element


        cv::Size m_image_shape;
    };
    
   
    

};