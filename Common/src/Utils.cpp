#include "Utils.h"


namespace Common
{
    float IoU(const BoundingBox& box1, const BoundingBox& box2)
    {
        float x1 = std::max(box1.left, box2.left);
        float y1 = std::max(box1.top, box2.top);
        float x2 = std::min(box1.left + box1.width, box2.left + box2.width);
        float y2 = std::min(box1.top + box1.height, box2.top + box2.height);

        float intersection_width = std::max(0.0f, x2 - x1);
        float intersection_height = std::max(0.0f, y2 - y1);
        float intersection_area = intersection_width * intersection_height;

        float box1_area = box1.width * box1.height;
        float box2_area = box2.width * box2.height;

        float union_area = box1_area + box2_area - intersection_area;

        return intersection_area / union_area;
    }


    std::vector<BoundingBox> NMS(const std::vector<BoundingBox> &boxes, float iou_threshold)
    {
        std::vector<BoundingBox> selected_boxes;
        std::vector<bool> is_selected(boxes.size(), false);

        for (size_t i = 0; i < boxes.size(); ++i) {
            if (is_selected[i])
                continue;

            selected_boxes.push_back(boxes[i]);
            is_selected[i] = true;

            for (size_t j = i + 1; j < boxes.size(); ++j) {
                if (!is_selected[j] && IoU(boxes[i], boxes[j]) > iou_threshold) {
                    is_selected[j] = true;
                }
            }
        }

        return selected_boxes;
    }

}