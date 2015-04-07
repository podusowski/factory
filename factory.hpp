#pragma once

#include <memory>

template<class Interface>
struct factory_impl_base
{
    virtual auto create() -> std::shared_ptr<Interface> = 0;
    //virtual auto clone() -> std::unique_ptr<factory_impl_base<Interface>> = 0;
    virtual ~factory_impl_base() {}
};

template<class Interface, class Implementation>
struct factory_impl : public factory_impl_base<Interface>
{
    auto create() -> std::shared_ptr<Interface> override
    {
        return std::make_shared<Implementation>();
    }
};

template<class Result>
struct factory
{
    typedef Result result_type;

    template<class Factory>
    factory(Factory && factory)
    {
        impl = std::make_unique<factory_impl<Result, typename Factory::result_type>>();
    }

    factory()
    {
        impl = std::make_unique<factory_impl<Result, Result>>();
    }

    factory(const factory & factory) = delete;

    auto create() -> std::shared_ptr<Result>
    {
        return impl->create();
    }

private:
    std::unique_ptr<factory_impl_base<Result>> impl;
};
