#pragma once
#include "PrePostProcessor.h"


namespace crnn
{
    class crnnPrePostProcessor: public Common::PrePostProcessor
    {
    public:
        crnnPrePostProcessor();
        ~crnnPrePostProcessor();

        std::shared_ptr<ov::Model> OvPrePostprocessing(std::shared_ptr<ov::Model> ov_model) override;

        std::vector<Common::BoundingBox> Postprocessing(std::vector<ov::Tensor>& output_tensor) override;

        std::vector<ov::Tensor> Preprocessing(const cv::Mat& image) override;

    private:

        std::vector<ov::Tensor> CreateTensor(const cv::Mat& image);

        void ParseModelIO(std::shared_ptr<ov::Model> ov_model);

        

    private:

        cv::Mat m_tmp;
        cv::Size m_current_shape;
        cv::Size m_original_shape;

        std::vector<int> m_input_dims;
        std::vector<int> m_output_dims;



        int m_input_width;
        int m_input_height;
        int m_input_channel;  // grey
        const int m_input_batch = 1;


        int m_output_seq_len;
        int m_output_num_classes;
    };
    
    
    

};
