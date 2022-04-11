#define CATCH_CONFIG_MAIN
#include "../../../../catch2/catch.hpp"
#include "../CCalculatorController.h"

TEST_CASE("Creating an empty calculator")
{
	GIVEN("Calculator")
	{
		CCalculator calculator;

		REQUIRE(calculator.GetVars().empty());
		REQUIRE(calculator.GetFunctions().empty());
	}
}

TEST_CASE("Creating variables with different identifiers")
{
	GIVEN("Calculator")
	{
		CCalculator calculator;

		WHEN("Creating a variable x")
		{
			REQUIRE_THROWS(calculator.CreateVar("x"));
			THEN("The variable x has been created, and has the value Nan")
			{
				REQUIRE(std::isnan(calculator.GetIdentifierValue("x")));
			}
		}

		WHEN("Creating a variable x12_")
		{
			REQUIRE_THROWS(calculator.CreateVar("x12_"));
			THEN("The variable x12_ has been created, and has the value Nan")
			{
				REQUIRE(std::isnan(calculator.GetIdentifierValue("x12_")));
			}
		}

		WHEN("Creating a variable _abc")
		{
			REQUIRE_THROWS(calculator.CreateVar("_abc"));
			THEN("The variable _abc has been created, and has the value Nan")
			{
				REQUIRE(std::isnan(calculator.GetIdentifierValue("_abc")));
			}
		}

		WHEN("Creating a variable with an empty name")
		{
			REQUIRE_THROWS_AS(calculator.CreateVar(""), std::invalid_argument);
			THEN("The variable \"\" was not created, a runtime_error exception was thrown")
			{
				REQUIRE_THROWS_AS(calculator.GetIdentifierValue(""), std::runtime_error);
			}
		}

		WHEN("Creating a variable 12")
		{
			REQUIRE_THROWS_AS(calculator.CreateVar("12"), std::invalid_argument);
			THEN("The variable 12 was not created, a runtime_error exception was thrown")
			{
				REQUIRE_THROWS_AS(calculator.GetIdentifierValue("12"), std::runtime_error);
			}
		}

		WHEN("Creating a variable a12?5")
		{
			REQUIRE_THROWS_AS(calculator.CreateVar("a12?5"), std::invalid_argument);
			THEN("The variable a12?5 was not created, a runtime_error exception was thrown")
			{
				REQUIRE_THROWS_AS(calculator.GetIdentifierValue("a12?5"), std::runtime_error);
			}
		}

		WHEN("Two identical identifiers are created")
		{
			REQUIRE_THROWS(calculator.CreateVar("x"));
			REQUIRE_THROWS_AS(calculator.CreateVar("x"), std::invalid_argument);
			THEN("One variable has been created")
			{
				 REQUIRE(calculator.GetVars().size() == 1);
			}
		}
	}
}

TEST_CASE("Creating variables via assignment")
{
	GIVEN("Calculator")
	{
		CCalculator calculator;

		WHEN("Creating a variable x")
		{
			REQUIRE_THROWS(calculator.AssignmentLet("x", 1.23));
			THEN("The variable x contains the value 1.23")
			{
				REQUIRE(calculator.GetIdentifierValue("x") == 1.23);
			}
		}

		WHEN("Create the variable x via var and assign the value 1.23")
		{
			REQUIRE_THROWS(calculator.CreateVar("x"));
			REQUIRE_THROWS(calculator.AssignmentLet("x", 1.23));
			THEN("The variable x contains the value 1.23")
			{
				REQUIRE(calculator.GetVars().size() == 1);
				REQUIRE(calculator.GetIdentifierValue("x") == 1.23);
			}
		}

		WHEN("Assign the value of NaN to the variable y")
		{
			REQUIRE_THROWS(calculator.CreateVar("x"));
			REQUIRE_THROWS(calculator.AssignmentLet("y", "x"));
			THEN("The variable y must contain the value NaN")
			{
				REQUIRE(calculator.GetVars().size() == 2);
				REQUIRE(std::isnan(calculator.GetIdentifierValue("y")));
			}
		}

		WHEN("Assign the value of 1.23 to the variable y")
		{
			REQUIRE_THROWS(calculator.AssignmentLet("x", 1.23));
			REQUIRE_THROWS(calculator.AssignmentLet("y", "x"));
			THEN("The variable y must contain the value 1.23")
			{
				REQUIRE(calculator.GetVars().size() == 2);
				REQUIRE(calculator.GetIdentifierValue("y") == 1.23);
			}
		}

		WHEN("Invalid identifiers")
		{
			REQUIRE_THROWS_AS(calculator.AssignmentLet("%1", 1.23), std::invalid_argument);
			REQUIRE_THROWS_AS(calculator.AssignmentLet("Hello_2?", 123), std::invalid_argument);
			REQUIRE_THROWS_AS(calculator.AssignmentLet("x", "12y"), std::invalid_argument);
			REQUIRE_THROWS_AS(calculator.AssignmentLet("x", "y"), std::invalid_argument);
			REQUIRE_THROWS_AS(calculator.AssignmentLet("x", "y%"), std::invalid_argument);
		}

		WHEN("Redistricting")
		{
			REQUIRE_THROWS(calculator.AssignmentLet("x", 1));
			REQUIRE(calculator.GetIdentifierValue("x") == 1);
			REQUIRE_THROWS(calculator.AssignmentLet("x", 1.2));
			REQUIRE(calculator.GetIdentifierValue("x") == 1.2);
			REQUIRE_THROWS(calculator.AssignmentLet("x", 0));
			REQUIRE(calculator.GetIdentifierValue("x") == 0);
		}
	}
}

TEST_CASE("Creating functions")
{
	GIVEN("Calculator, var x with NaN, var y with 1.5, var z with 4.5")
	{
		CCalculator calculator;
		REQUIRE_THROWS(calculator.CreateVar("x"));
		REQUIRE_THROWS(calculator.AssignmentLet("y", 1.5));
		REQUIRE_THROWS(calculator.AssignmentLet("z", 4.5));

		WHEN("The function is created with the value x")
		{
			REQUIRE_THROWS(calculator.CreateFunction("func", "x"));
			THEN("The func identifier with the NaN value is defined")
			{
				REQUIRE(std::isnan(calculator.GetIdentifierValue("func")));
			}
		}

		WHEN("The function is created with the value y")
		{
			REQUIRE_THROWS(calculator.CreateFunction("func", "y"));
			THEN("The func identifier with the 1.5 value is defined")
			{
				REQUIRE(calculator.GetIdentifierValue("func") == 1.5);
			}
		}

		WHEN("The function is created with with the expression y + z")
		{
			REQUIRE_THROWS(calculator.CreateFunction("func", {
																 .firstOperandId = "y",
																 .secondOperandId = "z",
																 .operation = CCalculator::Operation::ADDITION,
															 }));
			THEN("The func identifier with the 6 value is defined")
			{
				REQUIRE(calculator.GetIdentifierValue("func") == 6);
			}
		}

		WHEN("The function is created with with the expression z - y")
		{
			REQUIRE_THROWS(calculator.CreateFunction("func", {
																 .firstOperandId = "z",
																 .secondOperandId = "y",
																 .operation = CCalculator::Operation::DIVISION,
															 }));
			THEN("The func identifier with the 3 value is defined")
			{
				REQUIRE(calculator.GetIdentifierValue("func") == 3);
			}
		}

		WHEN("The function is created with with the expression y * z")
		{
			REQUIRE_THROWS(calculator.CreateFunction("func", {
																 .firstOperandId = "y",
																 .secondOperandId = "z",
																 .operation = CCalculator::Operation::MULTIPLICATION,
															 }));
			THEN("The func identifier with the 6.75 value is defined")
			{
				REQUIRE(calculator.GetIdentifierValue("func") == 6.75);
			}
		}

		WHEN("The function is created with with the expression z / y")
		{
			REQUIRE_THROWS(calculator.CreateFunction("func", {
																 .firstOperandId = "y",
																 .secondOperandId = "z",
																 .operation = CCalculator::Operation::DIVISION,
															 }));
			THEN("The func identifier with the 3 value is defined")
			{
				REQUIRE(calculator.GetIdentifierValue("func") == 3);
			}
		}

		WHEN("The function is created with with the expression x + y")
		{
			REQUIRE_THROWS(calculator.CreateFunction("func", {
																 .firstOperandId = "x",
																 .secondOperandId = "y",
																 .operation = CCalculator::Operation::DIVISION,
															 }));
			THEN("The func identifier with the NaN value is defined")
			{
				REQUIRE(std::isnan(calculator.GetIdentifierValue("func")));
			}
		}

		WHEN("Creating a function with an existing identifier")
		{
			REQUIRE_THROWS_AS(calculator.CreateFunction("x", "x"), std::runtime_error);
			THEN("There is no function with this identifier")
			{
				REQUIRE(calculator.GetFunctions().empty());
			}
		}
	}
}

TEST_CASE("Declaration, assignment and output of variable values")
{
	GIVEN("Calculator")
	{
		CCalculator calculator;

		REQUIRE_THROWS(calculator.CreateVar("x"));
		REQUIRE(std::isnan(calculator.GetIdentifierValue("x")));
		REQUIRE_THROWS(calculator.AssignmentLet("x", 42));
		REQUIRE(calculator.GetIdentifierValue("x") == 42);
		REQUIRE_THROWS(calculator.AssignmentLet("x", 1.23));
		REQUIRE(calculator.GetIdentifierValue("x") == 1.23);
		REQUIRE_THROWS(calculator.AssignmentLet("x", "y"));
		REQUIRE_THROWS(calculator.AssignmentLet("x", 99));

		CCalculator::Vars vars = { { "x", 99.00 }, { "y", 1.23 } };
		REQUIRE(calculator.GetVars() == vars);
	}
}
