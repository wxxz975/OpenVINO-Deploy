#pragma once

#include "PrePostProcessor.h"

namespace yolov8
{
    struct Yolov8RawOutput
    {
        float cx;	// center x
        float cy;	// center y
        float w;	// width
        float h;	// height
        // class confidence
    };
    typedef Yolov8RawOutput* pYolov8RawOutput;
    
    #define Yolov8RawOutputEleNum (sizeof(Yolov8RawOutput) / sizeof(float))

    class Yolov8PrePostProcessor: public Common::PrePostProcessor
    {
    private:
        /* data */
    public:
        Yolov8PrePostProcessor();
        ~Yolov8PrePostProcessor();

        std::shared_ptr<ov::Model> OvPrePostprocessing(std::shared_ptr<ov::Model> ov_model) override;

        std::vector<Common::BoundingBox> Postprocessing(std::vector<ov::Tensor>& output_tensor) override;

        std::vector<ov::Tensor> Preprocessing(const cv::Mat& image) override;

    private:
        void ParseModelIO(std::shared_ptr<ov::Model> ov_model);


        std::vector<Common::BoundingBox> ParseRawOutput(const ov::Tensor& output_tensor, float conf_threshold);


        std::vector<ov::Tensor> CreateTensor(const cv::Mat& image);


        void NMS(std::vector<Common::BoundingBox>& boxes, float iou_threshold);

        void RestoreCoords(std::vector<Common::BoundingBox>& boxes, cv::Size original_shape, cv::Size current_shape);


    private:


        cv::Mat m_tmp;

        cv::Size m_original_shape;
        cv::Size m_current_shape;


        std::vector<std::size_t> m_input_dims;
        std::vector<std::size_t> m_output_dims;


        std::size_t m_input_width;
        std::size_t m_input_height;
        std::size_t m_input_channels;
        

        std::size_t m_output_bbox_ele_size;        // 这个是输出bbox的element个数

        const std::size_t m_input_batch = 1;

        float m_conf_threshold = 0.80;
        float m_iou_threshold = 0.5;
    };
    
    
    

}