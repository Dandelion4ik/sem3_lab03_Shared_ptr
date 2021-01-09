// Copyright 2021 Kavykin Andrey Kaviandr@yandex.ru
#include <gtest/gtest.h>

#include "shared_ptr.h"

TEST(shared_ptr, ContructorDefaultTest) {
  shared_ptr<int> SP1(new int{0});
  shared_ptr<int> SP2(SP1);
  ASSERT_EQ(SP1.operator bool(), true);
  ASSERT_EQ(SP2.operator bool(), true);
  ASSERT_EQ(SP1.get(), SP2.get());
  ASSERT_EQ(SP1.use_count(), 2);
}
TEST(shared_ptr, TestMainOperators) {
  int b = 50;
  shared_ptr<int> SH_TEST(new int{b});
  ASSERT_EQ(SH_TEST.use_count(), 1);
  ASSERT_EQ(*SH_TEST, b);
}
TEST(shared_ptr, RvalueOperatorTest) {
  shared_ptr<int> SP1(new int{10});
  shared_ptr<int> SP2(std::move(SP1));
  ASSERT_EQ(SP2.use_count(), 1);
}
TEST(shared_ptr, ResetTest) {
  shared_ptr<std::string> s1(new std::string{"hello"});
  std::string *s2 = new std::string("world");
  s1.reset(s2);
  ASSERT_EQ(*s1, "world");
}
TEST(shared_ptr, SwapTest) {
  shared_ptr<int> SP1(new int{10});
  shared_ptr<int> SP2(new int{20});
  SP2.swap(SP1);
  ASSERT_EQ(*SP2, 10);
  ASSERT_EQ(*SP1, 20);
  shared_ptr<char> ch1(new char{'a'});
  shared_ptr<char> ch2(new char{'b'});
  ASSERT_EQ(ch1.use_count(), 1);
  ASSERT_EQ(ch2.use_count(), 1);
  ASSERT_EQ(*ch1, 'a');
  ASSERT_EQ(*ch2, 'b');
  ch1.swap(ch2);
  ASSERT_EQ(ch1.use_count(), 1);
  ASSERT_EQ(ch2.use_count(), 1);
  ASSERT_EQ(*ch1, 'b');
  ASSERT_EQ(*ch2, 'a');
}
TEST(shared_ptr, CheckIsMoveConstructible) {
  ASSERT_EQ(std::is_move_constructible<int &>::value, true);
  EXPECT_TRUE(std::is_move_constructible<shared_ptr<int>>());
  EXPECT_TRUE(std::is_move_constructible<shared_ptr<char>>());
  EXPECT_TRUE(std::is_move_constructible<shared_ptr<size_t>>());
  EXPECT_TRUE(std::is_move_constructible<shared_ptr<std::string>>());
  EXPECT_TRUE(std::is_move_constructible<shared_ptr<uint16_t>>());
}
TEST(shared_ptr, CheckIsMoveAssignable) {
  EXPECT_TRUE(std::is_move_assignable<shared_ptr<int>>());
  EXPECT_TRUE(std::is_move_assignable<shared_ptr<char>>());
  EXPECT_TRUE(std::is_move_assignable<shared_ptr<std::string>>());
  EXPECT_TRUE(std::is_move_assignable<shared_ptr<size_t>>());
  EXPECT_TRUE(std::is_move_assignable<shared_ptr<uint16_t>>());
}
