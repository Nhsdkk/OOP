#include <gtest/gtest.h>

#include "../src/hex.h"

size_t get_size(const unsigned char * const val){
    auto i{0};
    while (val[i] != '\0'){
        i++;
    }
    return i;
}

bool validate_value(const std::string& expectedResult, const unsigned char * const result) {
    auto resultSize = get_size(result);

    if (expectedResult.length() != resultSize) return false;

    for (size_t i = 0; i < resultSize; ++i) {
        if (expectedResult[i] != result[i]) return false;
    }

    return true;
}

TEST(should_create_instance_when_number_is_valid_hex_value, string_tests) {
    const auto str = "101F10";
    const auto hex = new ::hex::Hex{str};
    ASSERT_TRUE(validate_value(str, hex->get_value()));
}



TEST(should_throw_exception_when_number_is_not_valid_hex_value, string_tests) {
    EXPECT_THROW([]{
        auto hex = new ::hex::Hex{"1010103g"};
        std::cout << hex->get_value();
    }(), exception::BinaryException);
}

//TEST(should_create_instance_when_char_is_valid_hex_value, fill_tests) {
//  const auto str = "11111";
//  const auto hex = new ::hex::Hex{static_cast<size_t>(5), static_cast<unsigned char >('1')};
//  ASSERT_TRUE(validate_value(str, hex->get_value()));
//}
//
//
//
//TEST(should_throw_exception_when_char_is_not_valid_hex_value, fill_tests) {
//  EXPECT_THROW({
//     auto hex = new ::hex::Hex{};
//   }, ::hex::BinaryException);
//}


TEST(should_create_instance_when_number_is_valid_hex_value, list_tests) {
  const auto str = "1C0A10";
  const auto hex = new ::hex::Hex{'1', 'C', '0', 'A', '1', '0'};
  ASSERT_TRUE(validate_value(str, hex->get_value()));
}



TEST(should_throw_exception_when_number_is_not_valid_hex_value, list_tests) {
    EXPECT_THROW(([]{
     auto hex = new ::hex::Hex{'1', '0', '3', 't', '3', '2'};
    }()), exception::BinaryException);
}

TEST(should_sum_two_numbers_correctly_1, sum_tests){
    const auto h1 = ::hex::Hex("A");
    const auto h2 = ::hex::Hex("6");
    ASSERT_TRUE(validate_value("10", (h2 + h1).get_value()));
}

TEST(should_sum_two_numbers_correctly_2, sum_tests){
    const auto h1 = ::hex::Hex("1F");
    const auto h2 = ::hex::Hex("2");
    ASSERT_TRUE(validate_value("21", (h2 + h1).get_value()));
}

TEST(should_sum_two_numbers_correctly_3, sum_tests){
    const auto h1 = ::hex::Hex("AB");
    const auto h2 = ::hex::Hex("CD");
    ASSERT_TRUE(validate_value("178", (h2 + h1).get_value()));
}

TEST(should_sum_two_numbers_correctly_if_one_is_zero_1, sum_tests){
    const auto h1 = ::hex::Hex("11010");
    const auto h2 = ::hex::Hex();
    ASSERT_TRUE(validate_value("11010", (h2 + h1).get_value()));
}

TEST(should_sum_two_numbers_correctly_if_one_is_zero_2, sum_tests){
    const auto h1 = ::hex::Hex();
    const auto h2 = ::hex::Hex("11010");
    ASSERT_TRUE(validate_value("11010", (h2 + h1).get_value()));
}

TEST(should_return_true_if_values_are_equal, eq_tests){
    const auto h1 = ::hex::Hex("11010");
    const auto h2 = ::hex::Hex("11010");
    ASSERT_TRUE(h2 == h1);
}

TEST(should_return_false_if_values_are_not_equal, eq_tests){
    const auto h1 = ::hex::Hex("11010");
    const auto h2 = ::hex::Hex("11011");
    ASSERT_FALSE(h2 == h1);
}

TEST(should_return_false_if_only_one_of_the_values_is_zero_1, eq_tests){
    const auto h1 = ::hex::Hex();
    const auto h2 = ::hex::Hex("11011");
    ASSERT_FALSE(h2 == h1);
}

TEST(should_return_false_if_only_one_of_the_values_is_zero_2, eq_tests){
    const auto h2 = ::hex::Hex();
    const auto h1 = ::hex::Hex("11011");
    ASSERT_FALSE(h2 == h1);
}

TEST(should_return_true_if_both_values_are_zero, eq_tests){
    const auto h1 = ::hex::Hex();
    const auto h2 = ::hex::Hex();
    ASSERT_TRUE(h2 == h1);
}

TEST(should_return_true_value_is_less, less_tests){
    const auto h1 = ::hex::Hex("11010");
    const auto h2 = ::hex::Hex("11011");
    ASSERT_TRUE(h1 < h2);
}

TEST(should_return_false_value_is_not_less, less_tests){
    const auto h1 = ::hex::Hex("11010");
    const auto h2 = ::hex::Hex();
    ASSERT_FALSE(h1 < h2);
}

TEST(should_return_true_value_is_greater, greater_tests){
    const auto h1 = ::hex::Hex("11011");
    const auto h2 = ::hex::Hex("11010");
    ASSERT_TRUE(h1 > h2);
}

TEST(should_return_false_value_is_not_greater, greater_tests){
    const auto h1 = ::hex::Hex();
    const auto h2 = ::hex::Hex("11010");
    ASSERT_FALSE(h1 > h2);
}


TEST(should_throw_exception_when_result_is_negative, subtraction_tests){
    EXPECT_THROW(
        []{
          const auto h1 = ::hex::Hex("5");
          const auto h2 = ::hex::Hex("A");
          const auto h3 = h1 - h2;
        }(), std::invalid_argument
    );
}

TEST(should_subtract_two_numbers_correctly_1, subtraction_tests){
    const auto h1 = ::hex::Hex("A");
    const auto h2 = ::hex::Hex("5");
    ASSERT_TRUE(validate_value("5", (h1 - h2).get_value()));
}

TEST(should_subtract_two_numbers_correctly_2, subtraction_tests){
    const auto h1 = ::hex::Hex("CD");
    const auto h2 = ::hex::Hex("AB");
    const auto result = h1 - h2;
    ASSERT_TRUE(validate_value("22", result.get_value()));
}

TEST(should_substract_two_numbers_correctly_3, subtraction_tests){
    const auto h1 = ::hex::Hex("FF");
    const auto h2 = ::hex::Hex();
    ASSERT_TRUE(validate_value("FF", (h1 - h2).get_value()));
}

TEST(should_subtract_two_numbers_correctly, isubtraction_tests){
    auto h1 = ::hex::Hex("CD");
    const auto h2 = ::hex::Hex("AB");
    h1 -= h2;
    ASSERT_TRUE(validate_value("22", h1.get_value()));
}

TEST(should_sum_two_numbers_correctly, isum_tests){
    auto h1 = ::hex::Hex("AB");
    const auto h2 = ::hex::Hex("CD");
    h1 += h2;
    ASSERT_TRUE(validate_value("178", h1.get_value()));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
