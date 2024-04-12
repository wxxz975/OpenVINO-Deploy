#pragma once
#include "PrePostProcessor.h"


namespace rtdetr
{   

    struct rtdetrRawOutput
    {
        float cx;
        float cy;
        float w;
        float h;
        /// .... class socre
    };
    typedef rtdetrRawOutput* pRtdetrRawOutput;
    
    #define RtdetrRawOutputEleNum (sizeof(rtdetrRawOutput) / sizeof(float))

    class rtdetrPrePostProcessor: public Common::PrePostProcessor
    {
    private:
        /* data */
    public:
        rtdetrPrePostProcessor(/* args */);
        ~rtdetrPrePostProcessor();

        std::shared_ptr<ov::Model> OvPrePostprocessing(std::shared_ptr<ov::Model> ov_model) override;

        std::vector<Common::BoundingBox> Postprocessing(std::vector<ov::Tensor>& output_tensor) override;
    
        std::vector<ov::Tensor> Preprocessing(const cv::Mat& image) override;

    private:

        void ParseModelIO(std::shared_ptr<ov::Model> ov_model);


        std::vector<ov::Tensor> CreateTensor(const cv::Mat& image);


    private:

        const int m_input_batch = 1;
        int m_input_height;
        int m_input_width;
        int m_input_channels;


        std::vector<int> m_input_dims;
        std::vector<int> m_output_dims;

        int m_output_box_size;
        int m_anchor_size;
        int m_class_nums;


        cv::Size m_current_shape;
        cv::Size m_original_shape;

        cv::Mat m_tmp;

        float m_conf_threshold = 0.6;
    };
    
    
    

};