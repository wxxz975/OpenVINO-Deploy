#pragma once
#include "InferenceEngine.h"

#include "detrPrePostProcessor.h"


namespace detr
{
    class detrInference: public Common::InferenceEngine
    {
    private:
        /* data */
    public:
        detrInference();
        ~detrInference();

    };
    
    
    

};