#include "Form1.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace CppUIProject;

[STAThread]
int main(array<System::String^> ^args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	Application::Run(gcnew Form1());
	return 0;
}

ref struct Form1::Entry {
private:
	String^ _value;

public:
	property String^ Value {
		String^ get() {
			return _value;
		}
		Void set(String^ value) {
			_value = value;
			IsPartial = true;
			if (value == "Ans") IsAns = true;
		}
	}
	property Boolean IsPartial;
	property Boolean IsAns;

	Entry() {  // Creates a default Entry.
		Value = "";
		IsPartial = false;
		IsAns = false;
	};

	Void ClearEntry() {
		Value = "";
		IsPartial = false;
		IsAns = false;
	}
};

Form1::Form1(void) {
	InitializeComponent();

	// Init fields
	currentEntry = gcnew Entry();
	currentState = State::NONE;
}

Void Form1::AppendNumber(Int32 c) {
	// Check if we're currently showing a total.
	// Clear total if so.
	if (currentState != State::NONE) this->ClearText();
	this->textBox1->Text += c.ToString();
	this->currentEntry->Value += c.ToString();
	this->currentState = State::NONE;
}

Void Form1::AppendOperand(String^ c) {
	// Append the operand.
	// It does not matter if we're showing a total, however if adding an operand
	// then make showingTotal false.
	if (this->currentState == State::ERROR) this->ClearText();
	if (c == "x") c = "*";
	this->textBox1->Text += c;
	this->currentEntry->ClearEntry();
	this->currentState = State::NONE;
}

Void Form1::ClearText() {
	this->textBox1->Text = "";
	this->currentEntry->ClearEntry();
	this->currentState = State::NONE;
}

String^ Form1::GetText() {
	return this->textBox1->Text;
}

Void Form1::HandleClick(Object^ sender, EventArgs^ e) {
	String^ buttonText = (static_cast<Button^>(sender))->Text;
	Int32 number = 0;
	
	// Handle numbers
	Boolean success = Int32::TryParse(buttonText, number);
	if (success) this->AppendNumber(number);

	// Handle operators
	else {
		// Check if values are symbols or text for clear buttons.
		if (buttonText == "=") {
			if (this->GetText()->Length > 0) {
				try {
					// Replace all instances of "Ans" with the actual previous answer.
					String^ calcString = this->GetText()->Replace("Ans", previousTotal.ToString());
					Double calcValue = Calc::EvaluateExpression(calcString);
					this->textBox1->Text = calcValue.ToString();
					this->currentState = State::TOTAL;
					this->previousTotal = calcValue;
				}
				catch (OverflowException^) {
					// Calculated value is over the limit of a double variable.
					// Double objects tend to be pretty good about how they handle memory.
					this->ClearText();
					this->textBox1->Text = "OVERFLOW";
					this->currentState = State::ERROR;
				}
			}
		}
		else if (buttonText == "CE") {
			// Clear last entry.
			// Requires the program to keep track of how long the current entry is.
			// Remove the length of the current entry off of the back of the calc string.
			if (this->currentEntry->Value == "") this->textBox1->Text = "";
			else {
				String^ text = this->GetText();
				this->textBox1->Text = text->Substring(0, text->Length - this->currentEntry->Value->Length);
				this->currentEntry->Value = "";
			}
			this->currentEntry->ClearEntry();
			this->currentState = State::NONE;
		}
		else if (buttonText == "CA") {
			// Clear entire calc string.
			this->ClearText();
		}
		else if (buttonText == "Ans") {
			// Only add "Ans" if the value is not partial.
			if (this->currentEntry->IsPartial) {
				this->textBox1->Text += "Ans";
				this->currentEntry->Value = "Ans";
			}
		}
		else {  // Input is guaranteed to be an operator.
			// Append to calc string.
			this->AppendOperand(buttonText);
		}
	}
}