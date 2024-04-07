#include "detrInference.h"


namespace detr
{
    detrInference::detrInference(/* args */)
        :Common::InferenceEngine(new detrPrePostProcessor())
    {
    }
    
    detrInference::~detrInference()
    {
    }


};