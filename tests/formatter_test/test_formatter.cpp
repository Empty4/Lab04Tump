#include <gtest/gtest.h>
#include <formatter.hpp>

TEST(FormatterTest, BasicFormatting) {
    EXPECT_EQ(formatter::format("hello"), "hello");
}

TEST(FormatterTest, EmptyString) {
    EXPECT_EQ(formatter::format(""), "");
}

TEST(FormatterTest, StringWithSpaces) {
    EXPECT_EQ(formatter::format("hello world"), "hello world");
}
