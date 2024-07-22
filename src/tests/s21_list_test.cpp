#include "../s21_list/s21_list.h"

#include <gtest/gtest.h>

#include <list>

using namespace s21;

TEST(ListTest, ListConstructor) {
  list<int> s21_list{1, 4, 8, 9};

  EXPECT_EQ(s21_list.size(), 4);
  EXPECT_EQ(s21_list.front(), 1);
}

TEST(ListTest, CopyConstructor) {
  list<int> s21_list_ref_int{1, 4, 8, 9};
  list<int> s21_list_res_int(s21_list_ref_int);

  EXPECT_EQ(s21_list_res_int.size(), 4U);
  EXPECT_EQ(s21_list_res_int.front(), 1);
}

TEST(ListTest, AssignmentOperator) {
  list<int> s21_list_ref_int{1, 4, 8, 9};
  list<int> s21_list_res_int = s21_list_ref_int;

  EXPECT_EQ(s21_list_res_int.size(), 4U);
  EXPECT_EQ(s21_list_res_int.front(), 1);
}

TEST(ListTest, AsignmentMoveConstructor) {
  list<int> s21_list_ref_int{1, 4, 8, 9};
  list<int> s21_list_res_int = std::move(s21_list_ref_int);

  EXPECT_EQ(s21_list_ref_int.size(), 0);
  EXPECT_EQ(s21_list_res_int.size(), 4);
  EXPECT_EQ(s21_list_res_int.front(), 1);
}

TEST(ListTest, MoveConstructor) {
  list<int> s21_list_ref_int{1, 4, 8, 9};
  list<int> s21_list_res_int(std::move(s21_list_ref_int));

  EXPECT_EQ(s21_list_ref_int.size(), 0);
  EXPECT_EQ(s21_list_res_int.size(), 4);
  EXPECT_EQ(s21_list_res_int.front(), 1);
}

TEST(ListTest, PopBack) {
  size_t n = 1e4;
  list<int> lst(n);
  EXPECT_EQ(lst.size(), n);
  EXPECT_TRUE(lst.max_size() != 0);
  lst.pop_back();
  lst.pop_front();
  EXPECT_EQ(lst.size(), (n - 2));
  int back = lst.back();
  int front = lst.front();
  EXPECT_EQ(back, 0);
  EXPECT_EQ(front, 0);
}

TEST(ListTest, PopFront) {
  list<double> lst = {1.032, 2.320,    3.0,   4.0,   5.0,
                      6.0,   7.000043, 8.324, 9.343, 10.0};
  EXPECT_EQ(lst.size(), 10U);
  double front = lst.front();
  EXPECT_DOUBLE_EQ(front, 1.032);
  lst.pop_front();
  double new_front = lst.front();
  EXPECT_DOUBLE_EQ(new_front, 2.320);
  lst.pop_back();
  double back = lst.back();
  EXPECT_DOUBLE_EQ(back, 9.343);
  EXPECT_EQ(lst.size(), 8U);
  lst.clear();
  EXPECT_EQ(lst.size(), 0U);
}

TEST(ListTest, PushFront) {
  list<int> s21_list_int{1, 4, 8, 9};

  s21_list_int.push_front(33);

  EXPECT_EQ(s21_list_int.size(), 5U);
  EXPECT_EQ(s21_list_int.front(), 33);
}

TEST(ListTest, Iterator) {
  list<int> lol = {1, 2, 10, 3, 4, 6, 43};
  std::list<int> lol_orig = {1, 2, 10, 3, 4, 6, 43};
  lol.push_front(21);
  lol_orig.push_front(21);
  auto itr_orig = lol_orig.begin();
  for (auto itr = lol.begin(); itr != lol.end(); itr++) {
    EXPECT_EQ(*itr, *itr_orig);
    itr_orig++;
  }

  list<int> lol1;
  std::list<int> lol_orig1;
  lol1.push_front(21);
  lol_orig1.push_front(21);
  auto itr_orig1 = lol_orig1.begin();
  for (auto itr1 = lol1.begin(); itr1 != lol1.end(); itr1++) {
    EXPECT_EQ(*itr1, *itr_orig1);
    itr_orig1++;
  }
}

TEST(ListTest, PushBack) {
  list<int> s21_list_int{1};

  s21_list_int.push_back(33);

  EXPECT_EQ(s21_list_int.size(), 2U);
  EXPECT_EQ(s21_list_int.back(), 33);
}

TEST(ListTest, Swap) {
  list<int> s21_list_ref_int{1, 4, 8, 9};
  list<int> s21_list_res_int{12, 13};

  s21_list_ref_int.swap(s21_list_res_int);

  EXPECT_EQ(s21_list_ref_int.size(), 2U);
  EXPECT_EQ(s21_list_ref_int.front(), 12);
  EXPECT_EQ(s21_list_res_int.size(), 4U);
  EXPECT_EQ(s21_list_res_int.front(), 1);
}

TEST(ListTest, Sort) {
  list<int> s21_list_int{8, 1, 4, 9};

  s21_list_int.sort();

  EXPECT_EQ(s21_list_int.front(), 1);
}

TEST(ListTest, Merge) {
  list<int> s21_list_ref_int{1, 4, 8, 9};
  list<int> s21_list_res_int{12, 13};

  s21_list_res_int.merge(s21_list_ref_int);

  EXPECT_EQ(s21_list_ref_int.size(), 0U);
  EXPECT_EQ(s21_list_res_int.size(), 6U);
  EXPECT_EQ(s21_list_res_int.front(), 1);
}

TEST(ListTest, Reverse) {
  list<int> s21_list_int{1, 4, 8, 9};

  s21_list_int.reverse();

  EXPECT_EQ(s21_list_int.front(), 9);
}

TEST(ListTest, Unique) {
  list<int> s21_list_int{1, 1, 4, 4, 8, 8, 8, 9, 9, 9, 9, 9};

  s21_list_int.unique();

  EXPECT_EQ(s21_list_int.size(), 4U);
}

TEST(ListTest, Empty) {
  list<int> s21_list_int{1, 4, 8, 9};
  list<int> s21_list_int2;

  EXPECT_FALSE(s21_list_int.empty());
  EXPECT_TRUE(s21_list_int2.empty());
}

TEST(ListTest, Insert) {
  list<int> s21_list_int{1, 4, 8, 9};

  auto it_int = s21_list_int.begin();
  it_int = s21_list_int.insert(it_int, 13);
  EXPECT_EQ(s21_list_int.front(), 13);
}

TEST(ListTest, Splice) {
  list<int> s21_list_ref_int{3, 5};
  list<int> s21_list_res_int{1, 4, 8, 9};

  auto it_int = s21_list_res_int.begin();
  s21_list_res_int.splice(it_int, s21_list_ref_int);
  EXPECT_EQ(*(s21_list_res_int.begin()), 3);
  EXPECT_EQ(*(s21_list_res_int.begin() + 1), 5);
}

TEST(ListTest, EmplaceBack) {
  list<int> our = {1, 2, 7, 8, 9};
  our.emplace_back(4, 5, 6);
  EXPECT_EQ(our.back(), 6);
}

TEST(ListTest, EmplaceFront) {
  list<int> our{1, 2, 7, 8, 9};
  our.emplace_front(4, 5, 6);
  EXPECT_EQ(our.front(), 6);
}
