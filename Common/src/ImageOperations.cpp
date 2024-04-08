#include "ImageOperations.h"



namespace Common
{
    bool ConvertSize(cv::Mat& image, cv::Size targetShape)
    {
        float height = static_cast<float>(image.rows);
        float width = static_cast<float>(image.cols);
        float input_height = static_cast<float>(targetShape.height);
        float input_width = static_cast<float>(targetShape.width);

        float r = std::min(input_height / height, input_width / width);
        int padw = static_cast<int>(std::round(width * r));  // 需要放缩成为的值
        int padh = static_cast<int>(std::round(height * r));

        // 输入图像的宽高不一致的情况 
        if((int)width != padw || (int)height != padh) 
            cv::resize(image, image, cv::Size(padw, padh));
        

        // 把等比缩放得到的图像 计算需要填充padding值
        float _dw = (input_width - padw) / 2.f; 
        float _dh = (input_height - padh) / 2.f;
        // 除2是为了把添加的padding 平摊到左右两边, 是为了保证放缩后的图像在整个图像的正中央
        
        int top =  static_cast<int>(std::round(_dh - 0.1f));
        int bottom = static_cast<int>(std::round(_dh + 0.1f));
        int left = static_cast<int>(std::round(_dw - 0.1f));
        int right = static_cast<int>(std::round(_dw + 0.1f));
        cv::copyMakeBorder(image, image, top, bottom, left, right, cv::BORDER_CONSTANT,
                            cv::Scalar(114, 114, 114));

        return true;
    }

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

    cv::Mat RenderBoundingBoxes(const cv::Mat &image, const std::vector<BoundingBox> &boxes, const std::vector<std::string> &labels)
    {
        cv::Mat out = image.clone();
        for (const auto& box : boxes) {
            cv::rectangle(out, cv::Rect(box.left, box.top, box.width, box.height), cv::Scalar(0, 255, 0), 2); // 绘制绿色边界框，线宽为2

            cv::Point labelPosition(box.left, box.top - 10); 
            std::string label = labels.empty() ? std::to_string(box.classIndex) : labels[box.classIndex];
            cv::putText(out, label, labelPosition, cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 0, 255), 1);
        }
        return out;
    }
}