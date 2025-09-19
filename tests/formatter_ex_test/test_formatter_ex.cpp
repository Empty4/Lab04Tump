#include <gtest/gtest.h>
#include <formatter_ex.hpp>

TEST(FormatterExTest, BasicFormatting) {
    EXPECT_EQ(formatter_ex::format("hello"), "[hello]");
}

TEST(FormatterExTest, EmptyString) {
    EXPECT_EQ(formatter_ex::format(""), "[]");
}

TEST(FormatterExTest, StringWithSpaces) {
    EXPECT_EQ(formatter_ex::format("hello world"), "[hello world]");
}
