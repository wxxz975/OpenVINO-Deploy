#pragma once
#include "Common/PrePostProcessor.h"


namespace yolov5
{
    class Yolov5PrePostProcessor: public Common::PrePostProcessor
    {
    private:
        /* data */
    public:
        Yolov5PrePostProcessor(ov::CompiledModel& ov_compiled_model);
        ~Yolov5PrePostProcessor();

    public:

        std::shared_ptr<ov::Model> OvPrePostprocessing(std::shared_ptr<ov::Model> ov_model) override;

        std::vector<Common::BoundingBox> Postprocessing(std::vector<ov::Tensor>& output_tensor) override;

        std::vector<ov::Tensor> Preprocessing(const cv::Mat& image) override;

    private:
        

        std::vector<ov::Tensor> CreateTensor(const cv::Mat& image);

        
    };

}


