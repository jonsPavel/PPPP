#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab2_source/Lab2_code.cpp"
#include <string>


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTest1 {
	TEST_CLASS(SolutionTests) {
	public:
		TEST_METHOD(any_pair) {
			string expected = "5";
			Assert::AreEqual(main_known_input(0, 0, 0, 0, 0, 0), expected);
		}

		TEST_METHOD(constY_anyX) {
			string expected = "4 1";
			Assert::AreEqual(main_known_input(0, 5, 5, 0, 7, 7), expected);
		}

		TEST_METHOD(constX_anyY) {
			string expected = "3 1";
			Assert::AreEqual(main_known_input(1, 0, 1, 5, 0, 5), expected);
		}
		TEST_METHOD(constX_anyY_2) {
			string expected = "3 0.2";
			Assert::AreEqual(main_known_input(5, 0, 1, 10, 0, 2), expected);
		}

		TEST_METHOD(one_solution) {
			string expected = "2 -1 2";
			Assert::AreEqual(main_known_input(1, 2, 3, 4, 5, 6), expected);
		}
		TEST_METHOD(one_solution_2) {
			string expected = "2 -12 11";
			Assert::AreEqual(main_known_input(7, 8, 4, 4, 5, 7), expected);
		}

		TEST_METHOD(linear_relationship) {
			string expected = "1 -1 1";
			Assert::AreEqual(main_known_input(1, 1, 1, 1, 1, 1), expected);
		}


		TEST_METHOD(none) {
			string expected = "0";
			Assert::AreEqual(main_known_input(0, 7, 8, 0, 5, 6), expected);
		}

	};
}

