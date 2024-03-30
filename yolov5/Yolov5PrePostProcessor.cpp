#include "Yolov5PrePostProcessor.h"


namespace Yolov5
{
    Yolov5PrePostProcessor::Yolov5PrePostProcessor(/* args */)
    {
    }

    Yolov5PrePostProcessor::~Yolov5PrePostProcessor()
    {
    }

    std::shared_ptr<ov::Model> Yolov5PrePostProcessor::OvPrePostprocessing(std::shared_ptr<ov::Model> ov_model)
    {
        return ov_model;
    }

    std::vector<Common::BoundingBox> Yolov5PrePostProcessor::Postprocessing(std::vector<ov::Tensor> &output_tensor)
    {
        ov::Tensor tensor = output_tensor.at(0);

        
    }

    std::vector<ov::Tensor> Yolov5PrePostProcessor::Preprocessing(const cv::Mat& image)
    {

    }


   

}
