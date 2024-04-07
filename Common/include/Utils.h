#pragma once

#include <algorithm>
#include <vector>

namespace Common
{
    template<class T>
    std::pair<T, std::size_t> MaxEle(typename std::vector<T>::const_iterator start, typename std::vector<T>::const_iterator end)
    {
        auto maxIt = std::max_element(start, end);
        if (maxIt == end) {
            // 如果范围为空，抛出异常或返回一个无效值
            throw std::range_error("Cannot perform MaxEle on an empty range.");
        }

        T maxValue = *maxIt;
        std::size_t maxIndex = std::distance(start, maxIt);
        return {maxValue, maxIndex};
    }


};