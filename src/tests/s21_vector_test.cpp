#include <gtest/gtest.h>
#include "../s21_vector/s21_vector.h"

using namespace s21;

TEST(VectorTest, ParametrizedConstructor){
    vector<char> vec(12);
    EXPECT_EQ(vec.size(), 12);
}

TEST(VectorTest, CopyConstructor){
    vector<char> vec = {1, 2, 3};
    vector<char> vec_c(vec);
    for (int i = 0; i < vec.size(); i++){
        EXPECT_EQ(vec[i], vec_c[i]);
    }
    EXPECT_EQ(vec.size(), vec_c.size());
}

TEST(VectorTest, MoveConstructor){
    vector<char> vec = {1, 2, 3};
    vector<char> vec_c(std::move(vec));
    for (int i = 0, c = 1; i < vec.size(); i++, c++){
        EXPECT_EQ(vec[i], c);
    }
    EXPECT_EQ(vec.size(), 0);
}

TEST(VectorTest, Size) {
    vector<int> vec;
    EXPECT_EQ(vec.size(), 0);

    vec.push_back(1);
    EXPECT_EQ(vec.size(), 1);

    vec.push_back(2);
    EXPECT_EQ(vec.size(), 2);
}

TEST(VectorTest, PushBack) {
    vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);

    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 2);
    EXPECT_EQ(vec[2], 3);

    EXPECT_EQ(vec.at(0), 1);
    EXPECT_EQ(vec.at(1), 2);
    EXPECT_EQ(vec.at(2), 3);
}


TEST(VectorTest, PopBack) {
    vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);

    vec.pop_back();
    EXPECT_EQ(vec.size(), 2);
    vec.pop_back();
    EXPECT_EQ(vec.size(), 1);
    vec.pop_back();
    EXPECT_EQ(vec.size(), 0);

    EXPECT_THROW(vec.pop_back(), std::out_of_range);
}

TEST(VectorTest, Clear) {
    vector<int> vec = {1, 2, 3};
    EXPECT_EQ(vec.size(), 3);

    vec.clear();
    EXPECT_EQ(vec.size(), 0);
}

TEST(VectorTest, OutOfRangeException) {
    vector<int> vec = {1, 2, 3};
    const vector<int> vec_c = {1, 2, 3};

    EXPECT_NO_THROW(vec.at(2));
    EXPECT_THROW(vec.at(3), std::out_of_range);
    EXPECT_NO_THROW(vec[3]);
    EXPECT_NO_THROW(vec_c[3]);
}

TEST(VectorTest, Iterator){
    vector<int> vec = {1, 2, 3};

    int c = 0;
    for (auto i = vec.begin(); i != vec.end(); i++, c++){
        *i = c + 12;
        EXPECT_EQ(vec[c], *i);
    }

    c = vec.size();
    for (auto i = vec.cend(); i != vec.cbegin(); i--, c--){
        EXPECT_EQ(vec[c], *i);
    }

    EXPECT_EQ(vec[0], 12);
    EXPECT_EQ(vec[1], 13);
    EXPECT_EQ(vec[2], 14);

    auto i = vec.begin(), e = vec.end() - 1;

    EXPECT_EQ(vec[0], *i);
    EXPECT_EQ(vec[1], *(i + 1));
    EXPECT_EQ(vec[2], *(i + 2));
    EXPECT_EQ(vec[2], *e);
    EXPECT_EQ(vec[1], *(e - 1));
    EXPECT_EQ(vec[0], *(e - 2));

    auto j = vec.cbegin(), k = vec.cend() - 1;
    
    EXPECT_EQ(vec[0], *j);
    EXPECT_EQ(vec[1], *(j + 1));
    EXPECT_EQ(vec[2], *(j + 2));
    EXPECT_EQ(vec[2], *k);
    EXPECT_EQ(vec[1], *(k - 1));
    EXPECT_EQ(vec[0], *(k - 2));
}

TEST(VectorTest, ConstIterator){
    const vector<int> vec = {1, 2, 3};

    auto j = vec.cbegin(), k = vec.cend() - 1;

    size_t c = 0;
    for (auto i = vec.cbegin(); i != vec.cend(); i++, c++){
        EXPECT_EQ(vec[c], *i);
    }

    c = vec.size();
    for (auto i = vec.cend(); i != vec.cbegin(); i--, c--){
        EXPECT_EQ(vec[c], *i);
    }
    
    EXPECT_EQ(vec[0], *j);
    EXPECT_EQ(vec[1], *(j + 1));
    EXPECT_EQ(vec[2], *(j + 2));
    EXPECT_EQ(vec[2], *k);
    EXPECT_EQ(vec[1], *(k - 1));
    EXPECT_EQ(vec[0], *(k - 2));
}

TEST(VectorTest, Empty){
    vector<int> vec;
    EXPECT_TRUE(vec.empty());
    vec.push_back(4);
    EXPECT_FALSE(vec.empty());
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}