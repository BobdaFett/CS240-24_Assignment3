#include "calc.h"

double Calc::CalculateExpression(String^ calcString) {
	// Static function that handles running the recursive functions.
	currentCalcString = calcString;

	return expression();
}

Double Calc::expression() {
	// Processes an expression from the string.
	Double result = term();
	Boolean more = true;

	while (more) {
		Char operand = currentCalcString[0];
		if (operand == '-' || operand == '+') {
			currentCalcString = currentCalcString->Remove(0);
			Double value = term();

			// Do the calculation
			if (operand == '-') result -= value;
			else result += value;
		}
		else {
			more = false;
		}
	}

	return result;
}

Double Calc::term() {
	// Processes a term from the string.
	Double result = factor();
	Boolean more = true;

	while (more) {
		Char operand = currentCalcString[0];
		if (operand == '*' || operand == '/') {
			currentCalcString = currentCalcString->Remove(0);
			Double value = factor();

			// Do the calculation
			if (operand == '*') result *= value;
			else result /= value;
		}
		else {
			more = false;
		}
	}

	return result;
}

Double Calc::factor() {
	// Process a factor from the string.
	// This makes the looping call back to expression();
	Double result = 0;
	Char c = currentCalcString[0];
	if (c == '(') {
		currentCalcString = currentCalcString->Remove(0);
		Double result = expression();
		currentCalcString = currentCalcString->Remove(0);
	}
	else {
		Double tempValue = 0;
		while (Double::TryParse(c.ToString(), tempValue)) {
			// TODO Tweak this later to accept arguments from splits along ' '
			result = 10 * result + c - '0';
			currentCalcString = currentCalcString->Remove(0);
			c = currentCalcString[0];
		}
	}
}