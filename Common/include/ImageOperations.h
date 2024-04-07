#pragma once

#include <opencv2/opencv.hpp>

namespace Common
{
    
    /// @brief 这个主要是用于yolo系列的resize操作，主要操作是 1、按照原始比例等比放缩到目标尺寸，以大的一边为准 2、在小的一边进行padding
    /// @param image 原始图像
    /// @param newShape 目标形状
    /// @param color 填充空白的 padding 的颜色
    /// @param scaleFill 表示是否缩放填充区域以填满 newShape
    /// @param scaleUp 表示是否允许放大输入图像以适应 newShape
    /// @param stride 表示填充的步长
    /// @return 
    cv::Mat Letterbox(const cv::Mat& image, const cv::Size& newShape = {640, 640}, 
            const cv::Scalar& color = (114, 114, 114), bool scaleFill = false, bool scaleUp = true,
            int stride = 32
        );
    
    /// @brief 这个主要是用于计算经过推理后坐标换源(只有使用Letterbox才能需要这个还原)
    /// @param currentShape 目前推理的图像的形状
    /// @param originalShape 未经预处理的图像形状
    /// @param in_out_Coords 输入推理后的坐标，返回原始的坐标
    void CalcOriCoords(const cv::Size& currentShape, const cv::Size& originalShape, cv::Rect& in_out_Coords);



};