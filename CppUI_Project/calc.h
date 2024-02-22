#pragma once

using namespace System;

ref class Calc
{
private:
	static Double expression();
	static Double term();
	static Double factor();

	static String^ currentCalcString;

public:
	static Double EvaluateExpression(String^ calcString);
};

