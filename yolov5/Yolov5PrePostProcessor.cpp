#include "Yolov5PrePostProcessor.h"
#include "Common/ImageOperations.h"

namespace yolov5
{
    Yolov5PrePostProcessor::Yolov5PrePostProcessor(ov::CompiledModel& ov_compiled_model)
        :PrePostProcessor(ov_compiled_model)
    {
    }

    Yolov5PrePostProcessor::~Yolov5PrePostProcessor()
    {

    }

    std::shared_ptr<ov::Model> Yolov5PrePostProcessor::OvPrePostprocessing(std::shared_ptr<ov::Model> ov_model)
    {
        ov::preprocess::PrePostProcessor ppp(ov_model);
        
        ov::Shape shape = ov_model->input().get_shape();
        std::size_t size = shape.size();
        
        std::cout << "shape:";
        for(auto it:shape)
        {
            std::cout << " "<<it;
        }
        std::cout << std::endl;
         
        ppp.input().tensor()
            .set_layout("NHWC")
            .set_color_format(ov::preprocess::ColorFormat::BGR)
            .set_element_type(ov::element::u8);
            //.set_shape();

        ppp.input().preprocess()
            .convert_layout("NCHW")
            .convert_color(ov::preprocess::ColorFormat::RGB)
            .convert_element_type(ov::element::f32);

        return ppp.build();
    }

    std::vector<Common::BoundingBox> Yolov5PrePostProcessor::Postprocessing(std::vector<ov::Tensor> &output_tensor)
    {
        ov::Tensor tensor = output_tensor.at(0);
        float* raw_ptr = reinterpret_cast<float*>(tensor.data());
        std::size_t ele_size = tensor.get_size();
        
        std::vector<float> vec(raw_ptr, raw_ptr + ele_size);


    }

    std::vector<ov::Tensor> Yolov5PrePostProcessor::Preprocessing(const cv::Mat& image)
    {
        cv::Mat new_image = Common::Letterbox(image);
        return CreateTensor(new_image);
    }

    std::vector<ov::Tensor> Yolov5PrePostProcessor::CreateTensor(const cv::Mat &image)
    {
        return { ov::Tensor(m_ov_compiled_model.input().get_element_type(),
                    m_ov_compiled_model.input().get_shape(),
                    image.data
            )};
    }
}
