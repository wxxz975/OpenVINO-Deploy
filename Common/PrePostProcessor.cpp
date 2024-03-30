#include "PrePostProcessor.h"


namespace Common
{

    std::shared_ptr<ov::Model> PrePostProcessor::OvPrePostprocessing(std::shared_ptr<ov::Model> ov_model)
    {
        return ov_model;
    }
}

