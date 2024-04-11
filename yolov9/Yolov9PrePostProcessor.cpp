#include "Yolov9PrePostProcessor.h"

#include "Utils.h"
#include "ImageOperations.h"



namespace yolov9
{
    Yolov9PrePostProcessor::Yolov9PrePostProcessor(/* args */)
    {
        
    }
    
    Yolov9PrePostProcessor::~Yolov9PrePostProcessor()
    {
    }


    std::shared_ptr<ov::Model> Yolov9PrePostProcessor::OvPrePostprocessing(std::shared_ptr<ov::Model> ov_model)
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

    std::vector<Common::BoundingBox> Yolov9PrePostProcessor::Postprocessing(std::vector<ov::Tensor>& output_tensor)
    {
        ov::Tensor tensor = output_tensor.at(0);
        std::vector<Common::BoundingBox> result = ParseRawOutput(tensor, m_conf_threshold);
        NMS(result, m_iou_threshold);
        //RestoreCoords(result, m_original_shape, m_current_shape);
        
        return result;
    }

    std::vector<ov::Tensor> Yolov9PrePostProcessor::Preprocessing(const cv::Mat& image)
    {
        m_original_shape = image.size();
        cv::resize(image, m_tmp, {static_cast<int>(m_input_width), static_cast<int>(m_input_height)});
        // m_tmp = Common::Letterbox(image, { static_cast<int>(m_input_width), static_cast<int>(m_input_height) });
        //Common::ConvertSize(m_tmp, { static_cast<int>(m_input_width), static_cast<int>(m_input_height) } );
       
        m_current_shape = m_tmp.size();
        return CreateTensor(m_tmp);
    }

    void Yolov9PrePostProcessor::ParseModelIO(std::shared_ptr<ov::Model> ov_model)
    {
        ov::Shape input_shape = ov_model->input().get_shape();
        ov::Shape output_shape = ov_model->output(0).get_shape();
        
        for(auto c : input_shape)
            m_input_dims.push_back(c);
        
        for(auto c : output_shape)
            m_output_dims.push_back(c);

        assert(m_input_dims.size() == 4);
        assert(m_output_dims.size() == 3);

        m_input_channels = m_input_dims.at(1);
        m_input_width = m_input_dims.at(2);
        m_input_height = m_input_dims.at(3);

        m_output_bbox_ele_size = m_output_dims.at(1);
    }

    std::vector<Common::BoundingBox> Yolov9PrePostProcessor::ParseRawOutput(const ov::Tensor &output_tensor, float conf_threshold)
    {
        std::vector<Common::BoundingBox> result;
        float* raw_ptr = reinterpret_cast<float*>(output_tensor.data());
        std::size_t ele_size = output_tensor.get_size();
        
        // [1, 84, 8400]
        std::size_t num_channels = m_output_dims.at(1); // 84
        std::size_t num_anchors = m_output_dims.at(2);  // 8400
        
        cv::Mat output0 = cv::Mat(cv::Size{ static_cast<int>(num_anchors), static_cast<int>(num_channels)}, CV_32F, raw_ptr).t();
        int image_width = m_original_shape.width;
        int image_height = m_original_shape.height;

        float* pData = output0.ptr<float>();
        for (std::size_t idx = 0; idx < output0.rows; ++idx)
        {
            cv::Mat scores = output0.row(idx).colRange(Yolov9RawOutputEleNum, num_channels);
            const Yolov9RawOutput* bbox = output0.row(idx).ptr<Yolov9RawOutput>();
            cv::Point classIdPoint;
            double score;
            cv::minMaxLoc(scores, 0, &score, 0, &classIdPoint);
            
            if(score < conf_threshold) 
                continue;
  
            std::int32_t width = static_cast<std::int32_t>(bbox->w / m_input_width * image_width);
            std::int32_t height = static_cast<std::int32_t>(bbox->h / m_input_height * image_height);

            std::int32_t left = static_cast<std::int32_t>(bbox->cx / m_input_width * image_width) - width / 2 ;
            std::int32_t top = static_cast<std::int32_t>(bbox->cy / m_input_height * image_height) - height / 2; 

            result.push_back({ left, top, width, height,
                classIdPoint.x,
                static_cast<float>(score) });
            
        }

        return result;
    }

    std::vector<ov::Tensor> Yolov9PrePostProcessor::CreateTensor(const cv::Mat &image)
    {
        return { ov::Tensor(
                    ov::element::u8,
                    { m_input_batch, m_input_height, m_input_width, m_input_channels }, // 1, 640, 640, 3
                    image.data
            )};
    }


    void Yolov9PrePostProcessor::NMS(std::vector<Common::BoundingBox>& boxes, float iou_threshold)
    {
        //cv::dnn::NMSBoxes();
        boxes = Common::NMS(boxes, iou_threshold);
    }

    void Yolov9PrePostProcessor::RestoreCoords(std::vector<Common::BoundingBox>& boxes, cv::Size original_shape, cv::Size current_shape)\
    {


        /*
        auto iter = boxes.begin();
        while (iter != boxes.end()) {
            cv::Rect rect = {iter->left, iter->top, iter->width, iter->height};
            Common::CalcOriCoords(current_shape, original_shape, rect);

            if (rect.x < 0 || rect.y < 0 || rect.width < 0 || rect.height < 0) {
                iter = boxes.erase(iter); // 有可能会出现异常坐标，删除
            } else {
                iter->left = rect.x;
                iter->top = rect.y;
                iter->width = rect.width;
                iter->height = rect.height;
                ++iter;
            }
        }*/

    }
}