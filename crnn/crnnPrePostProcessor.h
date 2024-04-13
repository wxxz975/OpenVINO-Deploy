#pragma once
#include <string>
#include <openvino/openvino.hpp>
#include <opencv2/opencv.hpp>

namespace crnn
{
    class crnnPrePostProcessor
    {
    public:
        crnnPrePostProcessor();
        ~crnnPrePostProcessor();

        std::shared_ptr<ov::Model> OvPrePostprocessing(std::shared_ptr<ov::Model> ov_model) ;

        std::string Postprocessing(std::vector<ov::Tensor>& output_tensor) ;

        std::vector<ov::Tensor> Preprocessing(const cv::Mat& image) ;

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
