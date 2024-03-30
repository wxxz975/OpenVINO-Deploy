#pragma once


#include <memory>


namespace Common
{
    template <typename T> 
    class SingletonHolder {
    private:
    static std::unique_ptr<T> instance_;

    SingletonHolder() = default;

    public:
    ~SingletonHolder() = default;

    static std::unique_ptr<T>& instance() { return instance_; }

    static void instance(std::unique_ptr<T> ptr) { instance_ = std::move(ptr); }

    static void clear() { instance_.reset(); }
    };
}

