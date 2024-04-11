#pragma once
#include "PrePostProcessor.h"


namespace yolov7
{

    
    struct Yolov7RawOutput
    {
        float cx;       // center x
        float cy;       // center y
        float w;        // width
        float h;        // height
        float box_conf; // box confidence
        // class confidence
    };
    typedef Yolov7RawOutput* pYolov7RawOutput;
    
    #define Yolov7RawOutputEleNum (sizeof(Yolov7RawOutput) / sizeof(float))


    class Yolov7PrePostProcessor: public Common::PrePostProcessor
    {
    private:
        /* data */
    public:
        Yolov7PrePostProcessor();
        ~Yolov7PrePostProcessor();

    public:

        std::shared_ptr<ov::Model> OvPrePostprocessing(std::shared_ptr<ov::Model> ov_model) override;

        std::vector<Common::BoundingBox> Postprocessing(std::vector<ov::Tensor>& output_tensor) override;

        std::vector<ov::Tensor> Preprocessing(const cv::Mat& image) override;

    private:
        void ParseModelIO(std::shared_ptr<ov::Model> ov_model);        

        std::vector<ov::Tensor> CreateTensor(const cv::Mat& image);

        std::vector<Common::BoundingBox> ParseRawOutput(ov::Tensor& output_tensor, float conf_threshold);

        void RestoreCoords(std::vector<Common::BoundingBox>& boxes, cv::Size original_shape, cv::Size current_shape);

        void NMS(std::vector<Common::BoundingBox>& boxes, float iou_threshold);
        
        std::size_t m_input_width;
        std::size_t m_input_height;
        std::size_t m_input_channels;
        
        std::vector<std::size_t> m_input_dims;
        std::vector<std::size_t> m_output_dims;

        std::size_t m_output_bbox_ele_size;        // 这个是输出bbox的element个数


        const std::size_t m_input_batch = 1;

        float m_conf_threshold = 0.5;
        float m_iou_threshold = 0.5;
        

        cv::Size m_current_shape;
        cv::Size m_original_shape;

        cv::Mat m_tmp;
    };

}


