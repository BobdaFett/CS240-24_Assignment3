#include "calc.h"

Double Calc::EvaluateExpression(String^ calcString) {
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
	String^ numberBuildString = "";

	Console::Write("Passed char:" + c + " ");

	if (c == '(') {
		// Comsume (
		currentCalcString = currentCalcString->Substring(1);
		result = expression();
		// Consume )
		currentCalcString = currentCalcString->Substring(1);
	}
	else {
		Double tempValue = 0;
		while (Double::TryParse(c.ToString(), tempValue) || c.ToString() == ".") {
			numberBuildString += c.ToString();
			currentCalcString = currentCalcString->Substring(1);
			if (currentCalcString->Length == 0) break;
			c = currentCalcString[0];
		}
		Console::Write(" String before parse: " + numberBuildString + " ");
		Double::TryParse(numberBuildString, result);
	}

	Console::WriteLine("Parsed number: " + result);
	return result;
}