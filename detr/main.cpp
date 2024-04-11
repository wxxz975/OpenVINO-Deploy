#include "detrInference.h"

#include <string>


/*
    TODO: 置信度和这个标签索引是对的，但是box坐标的不对，并且带有重合率较高的box，就好似没有nms一样
*/
int main(int argc, char* argv[])
{
    detr::detrInference engine;
    
    std::string model_path = "";
    std::string image_path = "";

    cv::Mat image = cv::imread(image_path);

    if(engine.Initialize(model_path)) {
        std::vector<Common::BoundingBox> result = engine.Infer(image);
    }

    return 0;
}