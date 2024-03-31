#include "PrePostProcessor.h"


namespace Common
{
    PrePostProcessor::PrePostProcessor(ov::CompiledModel &ov_compiled_model)
        :m_ov_compiled_model(ov_compiled_model)
    {
    }

    PrePostProcessor::~PrePostProcessor()
    {
    }

    std::shared_ptr<ov::Model> PrePostProcessor::OvPrePostprocessing(std::shared_ptr<ov::Model> ov_model)
    {
        return ov_model;
    }
}

