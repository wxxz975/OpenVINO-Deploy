#pragma once
#include "PrePostProcessor.h"

namespace yolov3
{
    
    struct Yolov3RawOutput
    {
        float cx;       // center x
        float cy;       // center y
        float w;        // width
        float h;        // height
        float box_conf; // box confidence
        // class confidence
    };
    typedef Yolov3RawOutput* pYolov3RawOutput;
    
    #define Yolov3RawOutputEleNum (sizeof(Yolov3RawOutput) / sizeof(float))


    class Yolov3PrePostProcessor: public Common::PrePostProcessor
    {
    private:
        /* data */
    public:
        Yolov3PrePostProcessor(/* args */);
        ~Yolov3PrePostProcessor();

        std::shared_ptr<ov::Model> OvPrePostprocessing(std::shared_ptr<ov::Model> ov_model) override;

        std::vector<Common::BoundingBox> Postprocessing(std::vector<ov::Tensor>& output_tensor) override;

        std::vector<ov::Tensor> Preprocessing(const cv::Mat& image) override;

    private:

        void ParseModelIO(std::shared_ptr<ov::Model> ov_model);

        std::vector<ov::Tensor> CreateTensor(const cv::Mat& image);

        std::vector<Common::BoundingBox> ParseRawOutput(ov::Tensor tensor, float conf_threshold);

        void NMS(std::vector<Common::BoundingBox>& boxes, float iou_threshold);

        void RestoreCoords(std::vector<Common::BoundingBox>& boxes, cv::Size original_shape, cv::Size current_shape);


    private:

        int m_input_height;
        int m_input_width;
        int m_input_channels;
        const int m_input_batch = 1;


        std::vector<int> m_input_dims;
        std::vector<int> m_output_dims;

        cv::Mat m_tmp;

        cv::Size m_original_shape;
        cv::Size m_current_shape;
        
        float m_iou_threshold = 0.55;
        float m_conf_threshold = 0.6;

        int m_output_bbox_ele_size;     
        int m_class_nums;
    };
    
    

};