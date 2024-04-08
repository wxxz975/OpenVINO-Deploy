#include "Yolov8PrePostProcessor.h"



namespace yolov8
{
    Yolov8PrePostProcessor::Yolov8PrePostProcessor(/* args */)
    {

    }
    
    Yolov8PrePostProcessor::~Yolov8PrePostProcessor()
    {
        
    }

    std::shared_ptr<ov::Model> Yolov8PrePostProcessor::OvPrePostprocessing(std::shared_ptr<ov::Model> ov_model)
    {

    }

    std::vector<Common::BoundingBox> Yolov8PrePostProcessor::Postprocessing(std::vector<ov::Tensor>& output_tensor)
    {

    }

    std::vector<ov::Tensor> Yolov8PrePostProcessor::Preprocessing(const cv::Mat& image)
    {
        
    }

}