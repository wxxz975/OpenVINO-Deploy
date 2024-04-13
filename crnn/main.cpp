#include "crnnInference.h"

#include "ImageOperations.h"

#include <string>
#include <iostream>


int main(int argc, char* argv[])
{
    if(argc != 3) {
        std::cout << "Usage:" << argv[0] << " <model_path> <image_path>\n";
        return -1;
    }
    std::string model_path = argv[1];
    std::string image_path = argv[2];

    crnn::crnnInference engine;

    cv::Mat image = cv::imread(image_path);
    
    
    if(engine.Initialize(model_path)) {
        auto result = engine.Infer(image);

        
    }

    return 0;
}