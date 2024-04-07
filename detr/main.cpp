#include "detrInference.h"

#include <string>

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