#pragma once

#include <memory>

template<class Interface>
struct factory_impl_base
{
    virtual auto create() -> std::shared_ptr<Interface> = 0;
    virtual auto clone() -> std::unique_ptr<factory_impl_base<Interface>> = 0;
    virtual ~factory_impl_base() {}
};

template<class Interface, class Implementation>
struct factory_impl : public factory_impl_base<Interface>
{
    auto create() -> std::shared_ptr<Interface> override
    {
        return std::make_shared<Implementation>();
    }

    auto clone() -> std::unique_ptr<factory_impl_base<Interface>> override
    {
        return std::make_unique<factory_impl<Interface, Implementation>>();
    }
};

template<class Interface>
struct factory
{
    explicit factory(std::unique_ptr<factory_impl_base<Interface>> impl) : impl(std::move(impl))
    {
    }

    auto create() -> std::shared_ptr<Interface>
    {
        return impl->create();
    }

    template<class U>
    operator factory<U> ()
    {
        return factory<U>(impl->clone());
    }

private:
    std::unique_ptr<factory_impl_base<Interface>> impl;
};

template<class T>
auto make_factory() -> factory<T>
{
    return factory<T>(std::make_unique<factory_impl<T, T>>());
}
