// Copyright 2021 Kavykin Andrey Kaviandr@yandex.ru
#include <gtest/gtest.h>

#include "shared_ptr.h"

TEST(shared_ptr, initialisation) {
    shared_ptr<int> sp1(new int{100});
    shared_ptr<int> sp2(sp1);
    ASSERT_EQ(sp1.operator bool(), true);
    ASSERT_EQ(sp2.operator bool(), true);
    ASSERT_EQ(sp1.get(), sp2.get());
    ASSERT_EQ(sp1.use_count(), 2);
    int a = 100;
    shared_ptr<int> SH_TEST(new int{a});
    ASSERT_EQ(SH_TEST.use_count(), 1);
    ASSERT_EQ(*SH_TEST, a);
}
TEST(shared_ptr, move) {
    shared_ptr<int> SP1(new int{100});
    shared_ptr<int> SP2(std::move(SP1));
    ASSERT_EQ(SP2.use_count(), 1);
}
TEST(shared_ptr, reset) {
    shared_ptr<std::string> s1(new std::string{"hello"});
    auto *s2 = new std::string("world");
    s1.reset(s2);
    ASSERT_EQ(*s1, "world");
}
TEST(shared_ptr, swap) {
    shared_ptr<int> sp1(new int{100});
    shared_ptr<int> sp2(new int{50});
    sp2.swap(sp1);
    ASSERT_EQ(*sp2, 100);
    ASSERT_EQ(*sp1, 50);
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