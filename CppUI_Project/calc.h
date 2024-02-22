#pragma once

using namespace System;

ref class Calc
{
private:
	Double expression();
	Double term();
	Double factor();

	static String^ currentCalcString;

public:
	Double CalculateExpression(String^ calcString);
};

