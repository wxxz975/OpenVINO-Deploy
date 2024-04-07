#include "ImageOperations.h"



namespace Common
{
    cv::Mat Letterbox(const cv::Mat& image, 
        const cv::Size& newShape, 
        const cv::Scalar& color, 
        bool scaleFill, bool scaleUp, 
        int stride)
    {
        cv::Mat outImage;
        cv::Size shape = image.size();
        float scale_factor = std::min(static_cast<float>(newShape.height) / static_cast<float>(shape.height),
            static_cast<float>(newShape.width) / static_cast<float>(shape.width));

        if (!scaleUp)
            scale_factor = std::min(scale_factor, 1.0f);

        float width_padding = (newShape.width - shape.width * scale_factor) / 2.f;
        float height_padding = (newShape.height - shape.height * scale_factor) / 2.f;

        if (scaleFill) {
            width_padding = 0.0f;
            height_padding = 0.0f;
            scale_factor = static_cast<float>(newShape.width) / shape.width;
        }

        // 调整图像大小
        //cv::Mat outImage;
        if (shape.width != static_cast<int>(shape.width * scale_factor) &&
            shape.height != static_cast<int>(shape.height * scale_factor)) {
            cv::resize(image, outImage, cv::Size(static_cast<int>(shape.width * scale_factor),
                static_cast<int>(shape.height * scale_factor)));
        }
        else {
            outImage = image;
        }

        // 计算边界
        int top = static_cast<int>(std::round(height_padding - 0.1f));
        int bottom = static_cast<int>(std::round(height_padding + 0.1f));
        int left = static_cast<int>(std::round(width_padding - 0.1f));
        int right = static_cast<int>(std::round(width_padding + 0.1f));

        // 添加边界
        cv::copyMakeBorder(outImage, outImage, top, bottom, left, right, cv::BORDER_CONSTANT, color);

        return outImage;
    }

    void CalcOriCoords(const cv::Size& currentShape, const cv::Size& originalShape, cv::Rect& in_out_Coords)
    {
        float gain = std::min(static_cast<float>(currentShape.height) / static_cast<float>(originalShape.height),
                                static_cast<float>(currentShape.width) / static_cast<float>(originalShape.width));

        int pad[2] = {
            static_cast<int>((static_cast<float>(currentShape.width) - static_cast<float>(originalShape.width) * gain) / 2.0f),
            static_cast<int>((static_cast<float>(currentShape.height) - static_cast<float>(originalShape.height) * gain) / 2.0f)
        };

        in_out_Coords.x = static_cast<int>(std::round((static_cast<float>(in_out_Coords.x - pad[0]) / gain)));
        in_out_Coords.y = static_cast<int>(std::round((static_cast<float>(in_out_Coords.y - pad[1]) / gain)));

        in_out_Coords.width = static_cast<int>(std::round((static_cast<float>(in_out_Coords.width) / gain)));
        in_out_Coords.height = static_cast<int>(std::round((static_cast<float>(in_out_Coords.height) / gain)));
    }

}