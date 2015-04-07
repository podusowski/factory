#include "factory.hpp"

#include <gtest/gtest.h>

struct trivial_object
{
};

TEST(factory_tests, create_trivial_object)
{
    auto f = factory<trivial_object>::bind<trivial_object>();
    std::shared_ptr<trivial_object> object = f.create();

    EXPECT_TRUE(bool(object));
}

struct base
{
    virtual ~base() {}
};

struct derived : public base
{
};

TEST(factory_tests, factory_is_convertible_base_object_factory)
{
    factory<base> f = factory<base>::bind<derived>();
    auto o = f.create();
    EXPECT_TRUE(bool(dynamic_cast<derived*>(o.get())));
}
