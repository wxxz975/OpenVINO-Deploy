#include "detrPrePostProcessor.h"

#include "Utils.h"

namespace detr
{
    detrPrePostProcessor::detrPrePostProcessor()
    {
    }
    
    detrPrePostProcessor::~detrPrePostProcessor()
    {
    }

    std::vector<ov::Tensor> detrPrePostProcessor::Preprocessing(const cv::Mat& image)
    {
        return CreateTensor(image);
    }

    std::vector<Common::BoundingBox> detrPrePostProcessor::Postprocessing(std::vector<ov::Tensor> &output_tensor)
    {
        std::vector<Common::BoundingBox> result;
        ov::Tensor tensor = output_tensor.at(0);
        float* ptr = reinterpret_cast<float*>(tensor.data());
        std::size_t output_size = tensor.get_size();
        std::vector<float> vec = std::vector<float>(ptr, ptr + output_size);
        std::size_t box_size = 10; // 这个是DETR_ELE_SIZE + 类别数量

        for (auto iter = vec.begin(); iter != vec.end(); iter += box_size)
        {
            pDetrRawOutput box = reinterpret_cast<pDetrRawOutput>(&(*iter));
            int left = (box->cx - box->bw / 2) *  m_image_shape.width;
            int top = (box->cy - box->bh / 2) * m_image_shape.height;
            int right = (box->cx + box->bw / 2) * m_image_shape.width;
            int bottom = (box->cy + box->bh / 2) * m_image_shape.height;

            auto start_conf = iter + DETR_ELE_SIZE;
            auto end_conf = iter + box_size;
            auto maxEle = Common::MaxEle<float>(start_conf, end_conf);

            result.push_back({
                left, top, right - left, bottom - top, 
                maxEle.second,
                maxEle.first
            });
        }

        return result;
    }

    std::shared_ptr<ov::Model> detrPrePostProcessor::OvPrePostprocessing(std::shared_ptr<ov::Model> ov_model)
    {
        ov::preprocess::PrePostProcessor ppp(ov_model);
        ppp.input().tensor()
            .set_element_type(ov::element::u8)
            .set_color_format(ov::preprocess::ColorFormat::BGR)
            .set_layout("NHWC");

        ppp.input().preprocess()
            .resize(ov::preprocess::ResizeAlgorithm::RESIZE_LINEAR, m_input_height, m_input_width)
            .convert_color(ov::preprocess::ColorFormat::RGB)
            .convert_element_type(ov::element::f32)
            .convert_layout("NCHW")
            .scale(225.0)
            .mean(m_means)
            .scale(m_std);

    }
    std::vector<ov::Tensor> detrPrePostProcessor::CreateTensor(const cv::Mat &image)
    {
        auto size = image.size();
        return {
            ov::Tensor( 
                ov::element::u8,
                { m_input_batch, 
                    static_cast<unsigned long>(size.width), 
                    static_cast<unsigned long>(size.height), 
                    m_input_channels },
                image.data
            )
        };
    }
};