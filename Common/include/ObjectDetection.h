#pragma once

namespace Common
{
    struct BoundingBox
    {
        int left;
        int top;		
        int width;
        int height;
        int	classIndex;
        float confidence;
        BoundingBox(int x, int y, 
            int w, int h, 
            int idx, float conf)
            :left(x), top(y), width(w), height(h), classIndex(idx), confidence(conf)
        {};

    };
    //typedef std::shared_ptr<BoundingBox> PBoundingBox;

};