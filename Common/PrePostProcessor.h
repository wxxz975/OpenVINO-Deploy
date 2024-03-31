#pragma once

#include <opencv2/opencv.hpp>
#include <openvino/openvino.hpp>

#include <vector>



namespace Common
{

    struct BoundingBox
    {
        std::int32_t left;
        std::int32_t top;		
        std::int32_t width;
        std::int32_t height;
        std::size_t	 classIndex;
        float confidence;
        BoundingBox(std::int32_t x, std::int32_t y, 
            std::int32_t w, std::int32_t h, 
            std::size_t idx, float conf)
            :left(x), top(y), width(w), height(h), classIndex(idx), confidence(conf)
        {};

    };
    typedef std::shared_ptr<BoundingBox> PBoundingBox;


    class PrePostProcessor
    {
    public:
        PrePostProcessor(ov::CompiledModel& ov_compiled_model);
        virtual ~PrePostProcessor();

    public:
        /// @brief 使用Ov自带的预处理以及后处理， 这个的预处理在Preprocessing之后， 这个的后处理在Postprocessing之前
        ///         如果不实现子类，则直接将Preprocessing处理后的传入进行推理。
        ///         注： 如果能使用这个OpenVINO处理尽量使用这个，而不是下面的自定义预处理，因为大多数来说这个比后者效率更高
        /// @param model 
        /// @return 
        virtual std::shared_ptr<ov::Model> OvPrePostprocessing(std::shared_ptr<ov::Model> ov_model);

        /// @brief 使用自定义的后处理
        /// @param output_tensor 
        /// @return 
        virtual std::vector<BoundingBox> Postprocessing(std::vector<ov::Tensor>& output_tensor) = 0;

        /// @brief 使用自定义的预处理
        /// @param image 
        /// @return 
        virtual std::vector<ov::Tensor> Preprocessing(const cv::Mat& image) = 0;

    protected:
        ov::CompiledModel& m_ov_compiled_model;
    };
}



