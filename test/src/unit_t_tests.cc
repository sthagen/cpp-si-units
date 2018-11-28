#include <catch.hpp>

#include <SI/unit.h>
#include <ratio>

using namespace SI;

TEST_CASE(
    "given two values with exponent 1 WHEN multiplied THEN exponent is 2")
{
  constexpr unit_t<'X'> v1{0};
  constexpr unit_t<'X'> v2{0};

  constexpr auto result = v1 * v2;

  static_assert(decltype(v1)::exponent::value == 1, "Exponent value is 1");
  static_assert(decltype(v2)::exponent::value == 1, "Exponent value is 1");
  static_assert(decltype(result)::exponent::value == 2,
                "Exponent value is two");
}

TEST_CASE("given two units with different non-negative values but same ratio "
          "and unit WHEN "
          "multiplied THEN resulting value is correct")
{

  constexpr unit_t<'X'> v1{20};
  constexpr unit_t<'X'> v2{30};

  constexpr auto result = v1 * v2;

  static_assert(result.raw_value() == 600, "Raw value matches");
}

TEST_CASE(
    "given two units with different non-negative values and different ratio "
    "and unit WHEN "
    "multiplied THEN resulting value is correct")
{

  constexpr unit_t<'X', std::deci> v1{2};
  constexpr unit_t<'X'> v2{30};

  constexpr auto result = v1 * v2;

  static_assert(result.raw_value() == 600, "Raw value matches");
}

TEST_CASE(
    "given two units with different values and different ratio and unit WHEN "
    "multiplied THEN resulting value is correct")
{

  constexpr unit_t<'X', std::deci> v1{2};
  constexpr unit_t<'X'> v2{-30};

  constexpr auto result = v1 * v2;

  static_assert(result.raw_value() == -600, "Raw value matches");
  static_assert(
      std::ratio_equal<decltype(result)::ratio, decltype(v1)::ratio>::value,
      "left hand side binds unit");
}

TEST_CASE(
    "given two units with different values and ratio of rhs is small WHEN "
    "multiplied THEN resulting type is of left hand side and value is 0")
{

  constexpr unit_t<'X'> v1{2};
  constexpr unit_t<'X', std::milli> v2{30};

  constexpr auto result = v1 * v2;

  static_assert(result.raw_value() == 0, "Raw value matches");
  static_assert(
      std::ratio_equal<decltype(result)::ratio, decltype(v1)::ratio>::value,
      "left hand side binds unit");
}

TEST_CASE("GIVEN two units with different exponents WHEN divided THEN "
          "resulting exopnent is left exponent - right exponent")
{
  constexpr unit_t<'X', std::ratio<1>, long long int, 3> v1{1};
  constexpr unit_t<'X', std::ratio<1>, long long int, 2> v2{1};

  constexpr auto result = v1 / v2;

  static_assert(decltype(result)::exponent::value == 1,
                "Exponent is subtracted");
}

/*TEST_CASE("GIVEN two units with exponent 1 WHEN divided result in a raw
integer")
{
  constexpr unit_t<'X', std::ratio<1>> v1{1};
  constexpr auto result = v1 / v1;

  static_assert(decltype(result)::type == decltype(v1)::internal_type, "raw
internal type is returned");
}*/