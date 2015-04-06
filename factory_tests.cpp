#include "factory.hpp"

#include <gtest/gtest.h>

struct trivial_object
{
};

TEST(factory_tests, create_trivial_object)
{
    auto factory = factory::make_factory<trivial_object>();
    std::shared_ptr<trivial_object> object = factory.create();

    EXPECT_TRUE(bool(object));
}
