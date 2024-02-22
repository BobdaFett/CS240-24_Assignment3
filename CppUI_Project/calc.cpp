#include "calc.h"

double Calc::EvaluateExpression(String^ calcString) {
	// Static function that handles running the recursive functions.
	currentCalcString = calcString;
	currentCalcString->Replace(" ", "");

	return expression();
}

Double Calc::expression() {
	// Processes an expression from the string.
	Double result = term();
	Boolean more = true;

	while (more) {
		if (currentCalcString->Length == 0) break;
		Char operand = currentCalcString[0];
		if (operand == '-' || operand == '+') {
			currentCalcString = currentCalcString->Substring(1);
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
		if (currentCalcString->Length == 0) break;
		Char operand = currentCalcString[0];
		if (operand == '*' || operand == '/') {
			currentCalcString = currentCalcString->Substring(1);
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
		currentCalcString = currentCalcString->Substring(1);
		Double result = expression();
		currentCalcString = currentCalcString->Substring(1);
	}
	else {
		Double tempValue = 0;
		while (Double::TryParse(c.ToString(), tempValue) || c.ToString() == ".") {
			// TODO Tweak this later to accept arguments from splits along ' '
			result = 10 * result + c - '0';
			currentCalcString = currentCalcString->Substring(1);
			if (currentCalcString->Length == 0) break;
			c = currentCalcString[0];
		}
	}
	return result;
}