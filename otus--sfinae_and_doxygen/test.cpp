#include <gtest/gtest.h>

#include <vector>
#include <list>
#include <string>
#include <unordered_set>


#include "ip_gen.h"
 
TEST(is_const_iterableTest, test) {
    EXPECT_EQ(is_const_iterable_v<int>, false);
    EXPECT_EQ(is_const_iterable_v<std::vector<int>>, true);
    EXPECT_EQ(is_const_iterable_v<std::list<int>>, true);
    EXPECT_EQ(is_const_iterable_v<std::string>, true);
    EXPECT_EQ(is_const_iterable_v<std::unordered_set<int>>, true);
}
TEST(is_one_type_tupleTest, test) {
    bool t = is_one_type_tuple_v<std::tuple<int, int, int, int>>;
    EXPECT_EQ(t, true);
    t = is_one_type_tuple<std::tuple<int, char, int, int>>::value;
    EXPECT_EQ(t, false);
    EXPECT_EQ(is_one_type_tuple_v<std::tuple<>>, true);
    EXPECT_EQ(is_one_type_tuple_v<int>, false);
    EXPECT_EQ(is_const_iterable_v<std::unordered_set<int>>, true);
}

TEST(ipPrintTest, integralTypeTest) {
    std::stringstream out;
    ip_print(out, int32_t(198));
    EXPECT_EQ(out.str(), "0.0.0.198\n");
    out.str("");

    ip_print(out, char(-1));
    EXPECT_EQ(out.str(), "255\n");
    out.str("");

    ip_print(out, short(0));
    EXPECT_EQ(out.str(), "0.0\n");
    out.str("");

    ip_print(out, int(2130706433));
    EXPECT_EQ(out.str(), "127.0.0.1\n");
    out.str("");

    ip_print(out, long long(8875824491850138409));
    EXPECT_EQ(out.str(), "123.45.67.89.101.112.131.41\n");
} 

TEST(ipPrintTest, stringTypeTest) {
    std::stringstream out;
    ip_print(out, "hello");
    EXPECT_EQ(out.str(), "hello\n");
    out.str("");

    ip_print(out, std::string("127.0.0.1"));
    EXPECT_EQ(out.str(), "127.0.0.1\n");
}

TEST(ipPrintTest, containerTypeTest) {
    std::stringstream out;

    std::vector<int> arr = { 127, 0, 0, 1 };
    ip_print(out, arr);
    EXPECT_EQ(out.str(), "127.0.0.1\n");
    out.str("");

    std::vector<int> arr2 = { 192, 168, 0, 1 };
    ip_print(out, arr2);
    EXPECT_EQ(out.str(), "192.168.0.1\n");
}    
 
TEST(ipPrintTest, tupleTypeTest) {
    std::stringstream out;

    const std::tuple<int, int, int, int> tpl = { 127, 0, 0, 1 };
    ip_print(out, tpl);
    EXPECT_EQ(out.str(), "127.0.0.1\n");
    out.str("");

}   

 