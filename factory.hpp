#pragma once

#include <memory>

namespace factory
{

template<class T>
struct factory
{
    auto create() -> std::shared_ptr<T>
    {
        return std::make_shared<T>();
    }
};

template<class T>
auto make_factory() -> factory<T>
{
    return factory<T>();
}

}
