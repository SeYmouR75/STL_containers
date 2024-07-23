#include "../s21_map/s21_map.h"

#include <gtest/gtest.h>

#include <map>

TEST(MapTest, DefaultConstructor) {
  s21::map<int, int> s21_map_int;
  s21::map<double, double> s21_map_double;
  s21::map<std::string, std::string> s21_map_string;

  EXPECT_EQ(s21_map_int.size(), 0U);
  EXPECT_EQ(s21_map_double.size(), 0U);
  EXPECT_EQ(s21_map_string.size(), 0U);
}

TEST(MapTest, CopyConstructor) {
  std::pair<int, double> pair1{9, 1.4};
  std::pair<int, double> pair2{23, 2.77};
  std::pair<int, double> pair3{98, 3.9};

  s21::map<int, double> s21_map_ref = {pair1, pair2, pair3};
  s21::map<int, double> s21_map_res(s21_map_ref);

  EXPECT_EQ(s21_map_res.size(), s21_map_ref.size());
}

TEST(MapTest, MoveConstructor) {
  std::pair<int, double> pair1{9, 1.4};
  std::pair<int, double> pair2{23, 2.77};
  std::pair<int, double> pair3{98, 3.9};

  s21::map<int, double> s21_map_ref = {pair1, pair2, pair3};
  s21::map<int, double> s21_map_res = std::move(s21_map_ref);

  EXPECT_EQ(s21_map_ref.size(), 0U);
  EXPECT_EQ(s21_map_res.size(), 3U);
}

TEST(MapTest, AssignmentMoveConstructor) {
  std::pair<int, double> pair1{9, 1.4};
  std::pair<int, double> pair2{23, 2.77};
  std::pair<int, double> pair3{98, 3.9};

  s21::map<int, double> s21_map_ref = {pair1, pair2, pair3};
  s21::map<int, double> s21_map_res;
  s21_map_res = std::move(s21_map_ref);

  EXPECT_EQ(s21_map_ref.size(), 0U);
  EXPECT_EQ(s21_map_res.size(), 3U);
}

TEST(MapTest, Iterator) {
  std::pair<int, double> pair1{9, 1.4};
  std::pair<int, double> pair2{23, 2.77};
  std::pair<int, double> pair3{98, 3.9};

  s21::map<int, double> s21_map_ref_int{pair1, pair2, pair3};
  s21::map<int, double> s21_map_res_int{s21_map_ref_int};

  std::pair<double, std::string> pair4{1.4, "hello"};
  std::pair<double, std::string> pair5{2.77, "hi"};
  std::pair<double, std::string> pair6{3.9, "hola"};

  s21::map<double, std::string> s21_map_ref_double{pair4, pair5, pair6};
  s21::map<double, std::string> s21_map_res_double{s21_map_ref_double};

  std::pair<std::string, int> pair7{"hello", 1};
  std::pair<std::string, int> pair8{"hi", 2};
  std::pair<std::string, int> pair9{"hola", 3};

  s21::map<std::string, int> s21_map_ref_string{pair7, pair8, pair9};
  s21::map<std::string, int> s21_map_res_string{s21_map_ref_string};

  auto it_res_int = s21_map_res_int.begin();
  for (auto it_ref_int = s21_map_ref_int.begin();
       it_ref_int != s21_map_ref_int.end(); ++it_ref_int) {
    EXPECT_EQ(it_res_int->first, it_ref_int->first);
    it_res_int++;
  }

  auto it_res_double = s21_map_res_double.begin();
  for (auto it_ref_double = s21_map_ref_double.begin();
       it_ref_double != s21_map_ref_double.end(); ++it_ref_double) {
    EXPECT_EQ(it_res_double->first, it_ref_double->first);
    it_res_double++;
  }

  auto it_res_string = s21_map_res_string.begin();
  for (auto it_ref_string = s21_map_ref_string.begin();
       it_ref_string != s21_map_ref_string.end(); ++it_ref_string) {
    EXPECT_EQ(it_res_string->first, it_ref_string->first);
    it_res_string++;
  }
}

TEST(MapTest, Insert) {
  std::pair<int, double> pair1{9, 1.4};
  std::pair<int, double> pair2{9, 1.4};
  std::pair<int, double> pair3{9, 1.4};
  std::pair<int, double> pair4{23, 2.77};
  std::pair<int, double> pair5{98, 3.9};

  s21::map<int, double> s21_map;

  std::pair<s21::map<int, double>::iterator, bool> insert1 =
      s21_map.insert(pair1);
  EXPECT_EQ(insert1.first->first, 9);
  EXPECT_EQ(insert1.second, 1);

  std::pair<s21::map<int, double>::iterator, bool> insert2 =
      s21_map.insert(pair2);
  std::pair<s21::map<int, double>::iterator, bool> insert3 =
      s21_map.insert(pair3);
  EXPECT_EQ(insert2.second, 0);
  EXPECT_EQ(insert3.second, 0);

  std::pair<s21::map<int, double>::iterator, bool> insert4 =
      s21_map.insert(pair4);
  EXPECT_EQ(insert4.first->first, 23);
  EXPECT_EQ(insert4.second, 1);

  std::pair<s21::map<int, double>::iterator, bool> insert5 =
      s21_map.insert(pair5);
  EXPECT_EQ(insert5.first->first, 98);
  EXPECT_EQ(insert5.second, 1);

  EXPECT_EQ(s21_map.size(), 3U);
}

TEST(MapTest, Erase) {
  std::pair<int, int> pair1{10, 10};
  std::pair<int, int> pair2{5, 5};
  std::pair<int, int> pair3{15, 15};
  std::pair<int, int> pair4{4, 4};
  std::pair<int, int> pair5{18, 18};
  std::pair<int, int> pair6{13, 13};
  std::pair<int, int> pair7{16, 16};

  s21::map<int, int> s21_map = {pair1, pair2, pair3, pair4,
                                pair5, pair6, pair7};

  auto it = s21_map.begin();
  it++;
  it++;
  it++;
  it++;
  s21_map.erase(it);
  EXPECT_EQ(s21_map.begin()->first, 4);
  EXPECT_EQ(s21_map.end()->first, 18);
  EXPECT_EQ(s21_map.size(), 6U);

  it = s21_map.begin();
  s21_map.erase(it);
  EXPECT_EQ(s21_map.begin()->first, 5);
  EXPECT_EQ(s21_map.end()->first, 18);
  EXPECT_EQ(s21_map.size(), 5U);

  it = s21_map.begin();
  it++;
  s21_map.erase(it);
  EXPECT_EQ(s21_map.begin()->first, 5);
  EXPECT_EQ(s21_map.end()->first, 18);
  EXPECT_EQ(s21_map.size(), 4U);

  it = s21_map.end();
  s21_map.erase(it);
  EXPECT_EQ(s21_map.begin()->first, 5);
  EXPECT_EQ(s21_map.end()->first, 16);
  EXPECT_EQ(s21_map.size(), 3U);

  it = s21_map.begin();
  it++;
  s21_map.erase(it);

  it = s21_map.begin();
  it++;
  s21_map.erase(it);

  it = s21_map.begin();
  s21_map.erase(it);

  EXPECT_EQ(s21_map.size(), 0U);
}

TEST(MapTest, Empty) {
  s21::map<double, int> s21_map;

  EXPECT_EQ(s21_map.empty(), 1);
}

TEST(MapTest, Swap) {
  std::pair<double, int> pair1{22.2, 1};
  std::pair<double, int> pair2{44.48, 1};
  std::pair<double, int> pair3{12.4457, 2};
  std::pair<double, int> pair4{1.44, 3};
  std::pair<double, int> pair5{22.2, 15};

  s21::map<double, int> s21_map_ref = {pair1, pair2};
  s21::map<double, int> s21_map_res = {pair3, pair4, pair5};

  s21_map_ref.swap(s21_map_res);

  EXPECT_EQ(s21_map_ref.size(), 3U);
  EXPECT_EQ(s21_map_ref.begin()->first, 1.44);

  EXPECT_EQ(s21_map_res.size(), 2U);
  EXPECT_EQ(s21_map_res.begin()->first, 22.2);
}

TEST(MapTest, Contains) {
  std::pair<double, int> pair1{22.2, 1};
  std::pair<double, int> pair2{44.48, 1};

  s21::map<double, int> s21_map_ref = {pair1, pair2};
  s21::map<double, int> s21_map_res;

  s21_map_ref.swap(s21_map_res);

  EXPECT_EQ(s21_map_ref.size(), 0U);
  EXPECT_EQ(s21_map_ref.contains(22.2), false);
  EXPECT_EQ(s21_map_ref.contains(44.48), false);

  EXPECT_EQ(s21_map_res.size(), 2U);
  EXPECT_EQ(s21_map_res.contains(22.2), true);
  EXPECT_EQ(s21_map_res.contains(44.48), true);
}

TEST(MapTest, At) {
  std::pair<int, double> pair1{9, 1.4};
  std::pair<int, double> pair2{23, 2.77};
  std::pair<int, double> pair3{98, 3.9};
  std::pair<int, double> pair11{78, 3.9};
  std::pair<int, double> pair22{88, 3.9};
  std::pair<int, double> pair33{108, 3.9};

  s21::map<int, double> s21_map_int{pair1,  pair2,  pair3,
                                    pair11, pair22, pair33};
  EXPECT_EQ(s21_map_int.at(9), 1.4);
  EXPECT_EQ(s21_map_int.at(23), 2.77);
  EXPECT_EQ(s21_map_int.at(98), 3.9);
  EXPECT_EQ(s21_map_int.at(78), 3.9);
  EXPECT_EQ(s21_map_int.at(88), 3.9);
  EXPECT_EQ(s21_map_int.at(108), 3.9);

  std::pair<double, std::string> pair4{1.4, "hello"};
  std::pair<double, std::string> pair5{2.77, "hi"};
  std::pair<double, std::string> pair6{3.9, "hola"};

  s21::map<double, std::string> s21_map_double{pair4, pair5, pair6};
  EXPECT_EQ(s21_map_double.at(1.4), "hello");
  EXPECT_EQ(s21_map_double.at(2.77), "hi");
  EXPECT_EQ(s21_map_double.at(3.9), "hola");

  std::pair<std::string, int> pair7{"hello", 1};
  std::pair<std::string, int> pair8{"hi", 2};
  std::pair<std::string, int> pair9{"hola", 3};

  s21::map<std::string, int> s21_map_string{pair7, pair8, pair9};
  EXPECT_EQ(s21_map_string.at("hello"), 1);
  EXPECT_EQ(s21_map_string.at("hi"), 2);
  EXPECT_EQ(s21_map_string.at("hola"), 3);
}

TEST(MapTest, AcessOperator) {
  std::pair<int, double> pair1{9, 1.4};
  std::pair<int, double> pair2{23, 2.77};
  std::pair<int, double> pair3{98, 3.9};
  std::pair<int, double> pair11{78, 3.9};
  std::pair<int, double> pair22{88, 3.9};
  std::pair<int, double> pair33{108, 3.9};

  s21::map<int, double> s21_map_int{pair1,  pair2,  pair3,
                                    pair11, pair22, pair33};
  EXPECT_EQ(s21_map_int[9], 1.4);
  EXPECT_EQ(s21_map_int[23], 2.77);
  EXPECT_EQ(s21_map_int[98], 3.9);
  EXPECT_EQ(s21_map_int[78], 3.9);
  EXPECT_EQ(s21_map_int[88], 3.9);
  EXPECT_EQ(s21_map_int[108], 3.9);

  std::pair<double, std::string> pair4{1.4, "hello"};
  std::pair<double, std::string> pair5{2.77, "hi"};
  std::pair<double, std::string> pair6{3.9, "hola"};

  s21::map<double, std::string> s21_map_double{pair4, pair5, pair6};
  EXPECT_EQ(s21_map_double[1.4], "hello");
  EXPECT_EQ(s21_map_double[2.77], "hi");
  EXPECT_EQ(s21_map_double[3.9], "hola");

  std::pair<std::string, int> pair7{"hello", 1};
  std::pair<std::string, int> pair8{"hi", 2};
  std::pair<std::string, int> pair9{"hola", 3};

  s21::map<std::string, int> s21_map_string{pair7, pair8, pair9};
  EXPECT_EQ(s21_map_string["hello"], 1);
  EXPECT_EQ(s21_map_string["hi"], 2);
  EXPECT_EQ(s21_map_string["hola"], 3);
}

TEST(MapTest, Merge) {
  std::pair<int, double> pair1{9, 1.4};
  std::pair<int, double> pair2{23, 2.77};
  std::pair<int, double> pair3{98, 3.9};
  std::pair<int, double> pair11{78, 4.59};
  std::pair<int, double> pair22{88, 12.902};
  std::pair<int, double> pair33{108, 56.41};

  s21::map<int, double> s21_map_int_ref{pair1, pair2, pair3};
  s21::map<int, double> s21_map_int_res{pair11, pair22, pair33};

  s21_map_int_res.merge(s21_map_int_ref);

  EXPECT_EQ(s21_map_int_res.size(), 6U);
}

TEST(MapTest, Emplace) {
  std::pair<int, double> pair1{9, 1.4};
  std::pair<int, double> pair2{9, 1.4};
  std::pair<int, double> pair3{9, 1.4};
  std::pair<int, double> pair4{23, 2.77};
  std::pair<int, double> pair5{8, 3.9};

  s21::map<int, double> s21_map;

  std::vector<std::pair<s21::map<int, double>::iterator, bool>> emplace1 =
      s21_map.emplace(pair1, pair2, pair3, pair4, pair5);

  EXPECT_EQ(emplace1[0].first->first, 9);
  EXPECT_EQ(emplace1[0].second, true);
  EXPECT_EQ(s21_map.size(), 3U);
}