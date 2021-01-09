// Copyright 2021 Kavykin Andrey Kaviandr@yandex.ru
#include <gtest/gtest.h>

#include "shared_ptr.h"
TEST(shared_ptr, initialisation) {
    shared_ptr<int> sp1;
    EXPECT_EQ(sp1, false);

    shared_ptr<int> sp2(new int(567));

    EXPECT_EQ(sp2, true);
    EXPECT_EQ(*sp2, 567);
    EXPECT_EQ(sp2.use_count(), 1);

    shared_ptr<int> sp3(sp2);

    EXPECT_EQ(sp3, true);
    EXPECT_EQ(*sp2, *sp3);
    EXPECT_EQ(sp2.use_count(), 2);
    EXPECT_EQ(sp3.use_count(), 2);
    EXPECT_EQ(sp2.get(), sp3.get());
}

TEST(shared_ptr, assign) {
    shared_ptr<int> sp1(new int(2898));
    auto sp2 = sp1;

    EXPECT_EQ(*sp2, 2898);
    EXPECT_EQ(sp1.use_count(), 2);
    EXPECT_EQ(sp1.use_count(), sp2.use_count());

    shared_ptr<int> sp3(new int(0));

    EXPECT_EQ(sp3.use_count(), 1);

    sp1 = sp3;

    EXPECT_EQ(sp3.use_count(), 2);
    EXPECT_EQ(*sp1, 0);
}

TEST(shared_ptr, reset_swap) {
    shared_ptr<int> sp1(new int(2));

    EXPECT_EQ(sp1.use_count(), 1);

    sp1.reset();

    EXPECT_EQ(sp1, false);

    shared_ptr<int> sp2(new int(2));
    sp1 = sp2;

    EXPECT_EQ(sp2.use_count(), 2);
    EXPECT_EQ(*sp2, 2);

    sp2.reset(new int(2001));

    EXPECT_EQ(sp2.use_count(), 1);
    EXPECT_EQ(*sp2, 2001);
    EXPECT_EQ(sp1.use_count(), 1);
    EXPECT_EQ(*sp1, 2);

    shared_ptr<int> sp3(sp2);

    EXPECT_EQ(sp3.use_count(), 2);
    EXPECT_EQ(*sp3, 2001);
    EXPECT_EQ(sp1.use_count(), 1);
    EXPECT_EQ(*sp1, 2);

    sp3.swap(sp1);

    EXPECT_EQ(sp3.use_count(), 1);
    EXPECT_EQ(*sp3, 2);
    EXPECT_EQ(sp1.use_count(), 2);
    EXPECT_EQ(*sp1, 2001);
}
