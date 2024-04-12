#pragma once


#include <algorithm>
#include <vector>
#include <limits>

#include "ObjectDetection.h"



namespace Common
{
    template<class T>
    std::pair<T, int> MaxEle(typename std::vector<T>::const_iterator start, typename std::vector<T>::const_iterator end)
    {
        auto maxIt = std::max_element(start, end);
        if (maxIt == end) {
            // 如果范围为空，抛出异常或返回一个无效值
            //throw std::runtime_error("Cannot perform MaxEle on an empty range.");
            return std::make_pair(std::numeric_limits<T>::min(), -1);
        }

        T maxValue = *maxIt;
        int maxIndex = std::distance(start, maxIt);
        return {maxValue, maxIndex};
    }

    template<class T>
    std::pair<T, int> MaxEle(T* start, T* end)
    {
        auto maxIt = std::max_element(start, end);
        if (maxIt == end) {
            // 如果范围为空，抛出异常或返回一个无效值
            //throw std::runtime_error("Cannot perform MaxEle on an empty range.");
            return std::make_pair(std::numeric_limits<T>::min(), -1);
        }

        T maxValue = *maxIt;
        int maxIndex = std::distance(start, maxIt);
        return {maxValue, maxIndex};

    }
    
    /// @brief 交并比
    /// @param box1 
    /// @param box2 
    /// @return 
    float IoU(const BoundingBox& box1, const BoundingBox& box2);

    /// @brief 执行非极大抑制
    /// @param boxes 
    /// @param iou_threshold 
    /// @return 
    std::vector<BoundingBox> NMS(const std::vector<BoundingBox>& boxes, float iou_threshold);

    
};