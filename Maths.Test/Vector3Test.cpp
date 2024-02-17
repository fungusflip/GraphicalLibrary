#include "pch.h"
#include"../Maths/Vector3.h"


TEST(Vector3_Constructor, AssignsAllCommponents) {
	Vector3 v(3, 4, 5);
	EXPECT_EQ(v.x, 3);
	EXPECT_EQ(v.y, 4);
	EXPECT_EQ(v.z, 5);
}

// UniTest 
// Test and implement equality comparison
TEST(Vector3_EqualityComparison, Returns_False_For_Inequal_Vectors) {
	EXPECT_FALSE(Vector3(3, 4, 5) == Vector3(2, 4, 5));
	EXPECT_FALSE(Vector3(3, 4, 5) == Vector3(3, 2, 5));
	EXPECT_FALSE(Vector3(3, 4, 5) == Vector3(3, 4, 2));
	EXPECT_FALSE(Vector3(3, 4, 5) == Vector3(2, 2, 2));
}

// Test and implement inequality comparison 
// UniTest
// Test-Driven Development (First write the test, then the function, then clean up your code)
TEST(Vector3_InequalityComparison, Returns_True_For_Inequal_Vectors) {
	EXPECT_TRUE(Vector3(3, 4, 5) != Vector3(3, 2, 5));
	EXPECT_TRUE(Vector3(3, 4, 5) != Vector3(5, 2, 5));
	EXPECT_TRUE(Vector3(3, 4, 5) != Vector3(3, 3, 2));
	EXPECT_TRUE(Vector3(3, 4, 5) != Vector3(5, 2, 2));
}

// Test and implement negate operator
TEST(Vector3_Negate, InvertsPositiveValues) {
	EXPECT_EQ(-Vector3(3, 4, 5), Vector3(-3, -4, -5));
}

// Test and implement adding operator 
TEST(Vector3_Addition, AddsUpAllValues) {
	EXPECT_EQ(Vector3(3, 4, 5) + Vector3(2, 3, 6), Vector3(5,7,11));
}

TEST(Vector3_Subtraction, SubtractsAllValues) {
	EXPECT_EQ(Vector3(3, 4, 5) - Vector3(2, 3, 6), Vector3(1, 1, -1));
}

TEST(Vector3_ScalarMultiplication, ScalesAllValues) {
	EXPECT_EQ(Vector3(3, 4, 5)*2, Vector3(6, 8, 10));
}

TEST(Vector3_ScalarDivision, dividesAllValues) {
	EXPECT_EQ(Vector3(6, 8, 10) / 2, Vector3(3, 4, 5));
}

TEST(Vector3_Magnitude, Returns_Correct_Magnitude_for_Non_Zero_Vectors) {
	EXPECT_FLOAT_EQ(Vector3(3, 4, 0).Magnitude(), 5);
	EXPECT_FLOAT_EQ(Vector3(3, 0, 0).Magnitude(), 3);
	EXPECT_FLOAT_EQ(Vector3(5, -3, 2).Magnitude(), sqrt(38));
}

