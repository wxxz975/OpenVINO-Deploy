#include "crnnInference.h"
#include "crnnPrePostProcessor.h"

namespace crnn
{
    
    crnnInference::crnnInference()
        :Common::InferenceEngine(new crnnPrePostProcessor())
    {

    }
    
    crnnInference::~crnnInference()
    {

        
    }


};