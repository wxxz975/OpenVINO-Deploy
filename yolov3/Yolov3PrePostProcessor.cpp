#include "Yolov3PrePostProcessor.h"
#include "ImageOperations.h"
#include "Utils.h"

namespace yolov3
{
    
    Yolov3PrePostProcessor::Yolov3PrePostProcessor(/* args */)
    {
    }
    
    Yolov3PrePostProcessor::~Yolov3PrePostProcessor()
    {
    }

    std::shared_ptr<ov::Model> Yolov3PrePostProcessor::OvPrePostprocessing(std::shared_ptr<ov::Model> ov_model)
    {
        ParseModelIO(ov_model);
        ov::preprocess::PrePostProcessor ppp(ov_model);

        ppp.input().tensor()
            .set_layout("NHWC")
            .set_color_format(ov::preprocess::ColorFormat::BGR)
            .set_element_type(ov::element::u8);

        ppp.input().preprocess()
            .convert_element_type(ov::element::f32)
            .convert_color(ov::preprocess::ColorFormat::RGB)
            .convert_layout("NCHW")
            .scale(255.f);

        return ppp.build();
    }

    std::vector<Common::BoundingBox> Yolov3PrePostProcessor::Postprocessing(std::vector<ov::Tensor>& output_tensor)
    {
        // 1. parse raw to box
        // 2. nms
        // 3. restore coords
        ov::Tensor tensor = output_tensor.at(0);
        std::vector<Common::BoundingBox> boxes = ParseRawOutput(tensor, m_conf_threshold);
        NMS(boxes, m_iou_threshold);
        RestoreCoords(boxes, m_original_shape, m_current_shape);

        return boxes;
    }

    std::vector<ov::Tensor> Yolov3PrePostProcessor::Preprocessing(const cv::Mat& image)
    {
        m_original_shape = image.size();
        cv::Mat new_mat = Common::Letterbox(image, cv::Size(m_input_width, m_input_height));

        m_current_shape = new_mat.size();

        return CreateTensor(new_mat);
    }


    void Yolov3PrePostProcessor::ParseModelIO(std::shared_ptr<ov::Model> ov_model)
    {
        ov::Shape input_shape = ov_model->input().get_shape();
        ov::Shape output_shape = ov_model->output().get_shape();
        
        for(auto c : input_shape)
            m_input_dims.push_back(c);
        
        for(auto c : output_shape)
            m_output_dims.push_back(c);

        assert(m_input_dims.size() == 4);
        assert(m_output_dims.size() == 3);

        m_input_channels = m_input_dims.at(1);
        m_input_width = m_input_dims.at(2);
        m_input_height = m_input_dims.at(3);

        m_output_bbox_ele_size = m_output_dims.at(2);
        m_class_nums = m_output_bbox_ele_size - Yolov3RawOutputEleNum;
    }

    std::vector<ov::Tensor> Yolov3PrePostProcessor::CreateTensor(const cv::Mat &image)
    {
        return { ov::Tensor(ov::element::u8,
                    { static_cast<std::size_t>(m_input_batch), 
                        static_cast<std::size_t>(m_input_width), 
                        static_cast<std::size_t>(m_input_height), 
                        static_cast<std::size_t>(m_input_channels) }, // 1, 640, 640, 3
                    image.data
            )};
    }
    
    

    std::vector<Common::BoundingBox> Yolov3PrePostProcessor::ParseRawOutput(ov::Tensor tensor, float conf_threshold)
    {
        std::vector<Common::BoundingBox> result;
        float* raw_ptr = reinterpret_cast<float*>(tensor.data());
        std::size_t ele_size = tensor.get_size();
        std::vector<float> vec(raw_ptr, raw_ptr + ele_size);

        for(auto iter = vec.begin(); iter != vec.end(); iter += m_output_bbox_ele_size)
        {
            pYolov3RawOutput bbox = reinterpret_cast<pYolov3RawOutput>(&(*iter));
            if(bbox->box_conf < conf_threshold)
                continue;

            auto cls_conf_start = iter + Yolov3RawOutputEleNum;
            auto cls_conf_end = iter + m_output_bbox_ele_size;
            auto max_info = Common::MaxEle<float>(cls_conf_start, cls_conf_end);
            if(max_info.first < conf_threshold) 
                continue;

            std::int32_t width = static_cast<std::int32_t>(bbox->w);
            std::int32_t height = static_cast<std::int32_t>(bbox->h);
            std::int32_t left = static_cast<std::int32_t>(bbox->cx) - width / 2;
            std::int32_t top = static_cast<std::int32_t>(bbox->cy) - height / 2;            

            result.push_back({ left, top, width, height,
				max_info.second,
				static_cast<float>(max_info.first * bbox->box_conf) });
        }

        return result;
    }

    void Yolov3PrePostProcessor::NMS(std::vector<Common::BoundingBox>& boxes, float iou_threshold)
    {
        boxes = Common::NMS(boxes, iou_threshold);
    }

    void Yolov3PrePostProcessor::RestoreCoords(std::vector<Common::BoundingBox> &boxes, cv::Size original_shape, cv::Size current_shape)
    {
        for(auto& box : boxes) 
        {
            cv::Rect rect = {box.left, box.top, box.width, box.height};
            Common::CalcOriCoords(current_shape, original_shape, rect);

            box.left = rect.x;
            box.top = rect.y;
            box.width = rect.width;
            box.height = rect.height;
        }
    }
};