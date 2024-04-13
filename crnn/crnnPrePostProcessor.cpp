#include "crnnPrePostProcessor.h"


namespace crnn
{
    crnnPrePostProcessor::crnnPrePostProcessor()
    {
    }
    
    crnnPrePostProcessor::~crnnPrePostProcessor()
    {

    }

    std::shared_ptr<ov::Model> crnnPrePostProcessor::OvPrePostprocessing(std::shared_ptr<ov::Model> ov_model)
    {
        ParseModelIO(ov_model);
        ov::preprocess::PrePostProcessor ppp(ov_model);


        ppp.input().tensor()
            //.set_shape({m_input_batch, m_input_height, m_input_width, m_input_channel})
            .set_layout("NHWC")
            .set_color_format(ov::preprocess::ColorFormat::GRAY)
            .set_element_type(ov::element::u8);

        ppp.input().preprocess()
            .convert_element_type(ov::element::f32)
            .convert_layout("NCHW")
            .scale(255.f)
            .mean(0.5)
            .scale(0.5);

        return ppp.build();
    }

    const std::string alphabet = "-0123456789abcdefghijklmnopqrstuvwxyz";
    std::string strDecode(std::vector<int>& preds, bool raw) {
        std::string str;
        if (raw) {
            for (auto v: preds) {
                str.push_back(alphabet[v]);
            }
        } else {
            for (int i = 0; i < preds.size(); i++) {
                if (preds[i] == 0 || (i > 0 && preds[i - 1] == preds[i])) continue;
                str.push_back(alphabet[preds[i]]);
            }
        }
        return str;
    }

    std::string crnnPrePostProcessor::Postprocessing(std::vector<ov::Tensor> &output_tensor)
    {
        std::string result;
        ov::Tensor tensor = output_tensor.at(0);
        float* raw_ptr = reinterpret_cast<float*>(tensor.data());

        std::vector<int> preds;
        for (int i = 0; i < m_output_seq_len; i++) {
            int maxj = 0;
            for (int j = 1; j < m_output_num_classes; j++) {
                if (raw_ptr[m_output_num_classes * i + j] > raw_ptr[m_output_num_classes * i + maxj]) maxj = j;
            }
            preds.push_back(maxj);
        }
        //std::cout << "raw: " << strDecode(preds, true) << std::endl;
        result = strDecode(preds, false);
        //std::cout << "sim: " << strDecode(preds, false) << std::endl;

        return result;
    }

    std::vector<ov::Tensor> crnnPrePostProcessor::Preprocessing(const cv::Mat& image)
    {
        m_original_shape = image.size();
        cv::resize(image, m_tmp, cv::Size(m_input_width, m_input_height));
        cv::cvtColor(m_tmp, m_tmp, cv::COLOR_BGR2GRAY);

        m_current_shape = image.size();

        return CreateTensor(m_tmp);
    }

    std::vector<ov::Tensor> crnnPrePostProcessor::CreateTensor(const cv::Mat& image)
    {
        return {
            ov::Tensor(
                ov::element::u8,
                {
                    static_cast<std::size_t>(m_input_batch),
                    static_cast<std::size_t>(m_input_height), 
                    static_cast<std::size_t>(m_input_width), 
                    static_cast<std::size_t>(m_input_channel)
                },
                image.data
            )
        };
    }


    void crnnPrePostProcessor::ParseModelIO(std::shared_ptr<ov::Model> ov_model)
    {
        ov::Shape input_shape = ov_model->input().get_shape();
        ov::Shape output_shape = ov_model->output().get_shape();

        for(auto c : input_shape)
            m_input_dims.push_back(c);

        for(auto c : output_shape)
            m_output_dims.push_back(c);

        
        assert(m_input_dims.size() == 4);
        assert(m_output_dims.size() == 3);

        m_input_channel = m_input_dims.at(1);
        m_input_height = m_input_dims.at(2);
        m_input_width = m_input_dims.at(3);

        m_output_seq_len = m_output_dims.at(0);
        m_output_num_classes = m_output_dims.at(2);

        // std::cout << "m_input_channel:" << m_input_channel 
        //         << " m_input_height:" << m_input_height
        //         << " m_input_width:" << m_input_width
        //         << " m_output_seq_len:" << m_output_seq_len
        //         << " m_output_num_classes:" << m_output_num_classes
        //         << "\n";
    }
};