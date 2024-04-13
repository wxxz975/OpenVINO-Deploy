#pragma once
#include "InferenceEngine.h"


namespace crnn
{
    class crnnInference: public Common::InferenceEngine
    {
    private:
        /* data */
    public:
        crnnInference(/* args */);
        ~crnnInference();
    };
    
    

};