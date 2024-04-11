
#include "Yolov9Inference.h"

#include "ImageOperations.h"

int main(int argc, char* argv[])
{
    if(argc != 3) {
        std::cout << "Usage:" << argv[0] << " <model_path> <image_path>\n";
        return -1;
    }
    std::string model_path = argv[1];
    std::string image_path = argv[2];

    yolov9::Yolov9Inference engine;

    cv::Mat image = cv::imread(image_path);

    if(engine.Initialize(model_path)) {
        auto result = engine.Infer(image);

        for(const auto& box : result) {
            std::cout << "idx:" << box.classIndex 
                << " conf:" << box.confidence
                << " x:" << box.left
                << " y:" << box.top
                << " width:" << box.width
                << " height:" << box.height
                << "\n";
        }

        cv::Mat rendered = Common::RenderBoundingBoxes(image, result);

        cv::imwrite("result.jpg", rendered);
    }

}