#pragma once
#include "Common/PrePostProcessor.h"


namespace Yolov5
{
    class Yolov5PrePostProcessor: public Common::PrePostProcessor
    {
    private:
        /* data */
    public:
        Yolov5PrePostProcessor();
        ~Yolov5PrePostProcessor();

        std::shared_ptr<ov::Model> OvPrePostprocessing(std::shared_ptr<ov::Model> ov_model) override;

        std::vector<Common::BoundingBox> Postprocessing(std::vector<ov::Tensor>& output_tensor) override;

        std::vector<ov::Tensor> Preprocessing(const cv::Mat& image) override;

        
    };

}


