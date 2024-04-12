#include "rtdetrPrePostProcessor.h"

#include "Utils.h"

namespace rtdetr
{
    rtdetrPrePostProcessor::rtdetrPrePostProcessor()
    {
    }
    
    rtdetrPrePostProcessor::~rtdetrPrePostProcessor()
    {

    }

    std::shared_ptr<ov::Model> rtdetrPrePostProcessor::OvPrePostprocessing(std::shared_ptr<ov::Model> ov_model)
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

    std::vector<Common::BoundingBox> rtdetrPrePostProcessor::Postprocessing(std::vector<ov::Tensor>& output_tensor)
    {
        std::vector<Common::BoundingBox> result;
        ov::Tensor tensor = output_tensor.at(0);
        float *raw_ptr = reinterpret_cast<float*>(tensor.data());

        for(int idx = 0; idx < m_anchor_size; idx++)
        {
            float* start_cls = raw_ptr + idx * m_output_box_size + RtdetrRawOutputEleNum;
            float* end_cls = start_cls + m_class_nums;
            auto maxInfo = Common::MaxEle<float>(start_cls, end_cls);
            pRtdetrRawOutput bbox = reinterpret_cast<pRtdetrRawOutput>(&raw_ptr[idx * m_output_box_size]);
            
            if(maxInfo.first < m_conf_threshold)
                continue;

            int left = static_cast<int>((bbox->cx - 0.5 * bbox->w) * m_original_shape.width);
            int top = static_cast<int>((bbox->cy - 0.5 * bbox->h) * m_original_shape.height);
            int width = static_cast<int>(bbox->w * m_original_shape.width);
            int height = static_cast<int>(bbox->h * m_original_shape.height);


            result.push_back(
                {
                    left, top, width, height,
                    maxInfo.second,
                    maxInfo.first
                }
            );

        }

        // ov::Tensor labels_tensor = output_tensor.at(0);
        // ov::Tensor boxes_tensor = output_tensor.at(1);
        // ov::Tensor scores_tensor = output_tensor.at(2);

        // int64_t* labels_raw_ptr = reinterpret_cast<int64_t*>(labels_tensor.data());
        // float* boxes_raw_ptr = reinterpret_cast<float*>(boxes_tensor.data());
        // float* scores_raw_ptr = reinterpret_cast<float*>(scores_tensor.data());
        

        // // this output is sorted 
        // for(int idx = 0; idx < m_anchor_size; idx++) {
        //     int64_t label_idx = labels_raw_ptr[idx];
        //     float score = scores_raw_ptr[idx];
        //     pRtdetrRawOutput bbox = reinterpret_cast<pRtdetrRawOutput>(&boxes_raw_ptr[idx * m_output_box_size]);


        //     if(score < m_conf_threshold)
        //         break;

        //     float r = m_current_shape.width / m_original_shape.width;

        //     int left = static_cast<int>(bbox->x / r);
        //     int top = static_cast<int>(bbox->y / r);
        //     int width = static_cast<int>(bbox->w / r);
        //     int height = static_cast<int>(bbox->h  / r);

        //     result.push_back(
        //         {
        //             left, top, width, height, 
        //             label_idx,
        //             score
        //         }
        //     );

        // }

        // cv::Mat rendered = Common::RenderBoundingBoxes(m_tmp, result);

        // cv::imwrite("result.jpg", rendered);

        return result;
    }
    
    std::vector<ov::Tensor> rtdetrPrePostProcessor::Preprocessing(const cv::Mat& image)
    {
        m_original_shape = image.size();
        cv::resize(image, m_tmp, cv::Size(m_input_width, m_input_height));
        m_current_shape = m_tmp.size();

        return CreateTensor(m_tmp);
    }


    void rtdetrPrePostProcessor::ParseModelIO(std::shared_ptr<ov::Model> ov_model)
    {
        ov::Shape input_dims = ov_model->input().get_shape();
        ov::Shape output_dims = ov_model->output().get_shape();
        std::cout << "output:" << output_dims;

        for(auto c: input_dims)
            m_input_dims.push_back(c);
        
        for(auto c: output_dims)
            m_output_dims.push_back(c);

        
        assert(m_input_dims.size() == 4);
        assert(m_output_dims.size() == 3);

        m_input_channels = m_input_dims.at(1);
        m_input_height = m_input_dims.at(2);
        m_input_width = m_input_dims.at(3);

        m_anchor_size = m_output_dims.at(1);
        m_output_box_size = m_output_dims.at(2);
        m_class_nums = m_output_box_size - RtdetrRawOutputEleNum;
        /*
        ov::Shape input_shape_image = ov_model->input(0).get_shape();
        ov::Shape intput_shape_ori_size = ov_model->input(1).get_shape();
        
        ov::Shape output_shape_labels = ov_model->output(0).get_shape();
        ov::Shape output_shape_boxes = ov_model->output(1).get_shape(); 
        ov::Shape output_shape_scores = ov_model->output(2).get_shape();


        for(auto c : input_shape_image)
            m_input_images.push_back(c);
        

        for(auto c : intput_shape_ori_size)
            m_input_orig_size.push_back(c);

        for(auto c: output_shape_labels)
            m_output_labels.push_back(c);

        for(auto c: output_shape_boxes)
            m_output_boxes.push_back(c);

        for(auto c: output_shape_scores)
            m_output_socres.push_back(c);
        
        assert(input_shape_image.size() == 4);
        assert(output_shape_boxes.size() == 3);

        m_input_channels = input_shape_image.at(1);
        m_input_width = input_shape_image.at(2);
        m_input_height = input_shape_image.at(3);

        m_output_box_size = output_shape_boxes.at(2);
        m_anchor_size = output_shape_labels.at(1);*/
    }

    std::vector<ov::Tensor> rtdetrPrePostProcessor::CreateTensor(const cv::Mat& image)
    {
        return { ov::Tensor(ov::element::u8,
                    { static_cast<std::size_t>(m_input_batch), 
                        static_cast<std::size_t>(m_input_width), 
                        static_cast<std::size_t>(m_input_height), 
                        static_cast<std::size_t>(m_input_channels) }, // 1, 640, 640, 3
                    image.data
            )};
    }
};