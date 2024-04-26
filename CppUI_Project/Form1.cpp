#include "Form1.h"
#include "TimeoutTimer.h"

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

	delegateTotal = gcnew UpdateTotal(this, &Form1::UpdateTotalFunction);
}

Void Form1::UpdateTotalFunction(Int32 newTotal) {
	// Set new variables.
	this->textBox1->Text = newTotal.ToString();
	currentState = State::TOTAL;
	previousTotal = newTotal;
}

Void Form1::AppendNumber(String^ c) {
	// Check if we're currently showing a total.
	// Clear total if so.
	if (currentState != State::NONE) this->ClearText();
	this->textBox1->Text += c;
	this->currentEntry->Value += c;
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
	if (success) this->AppendNumber(buttonText);

	// Handle operators
	else {
		// Check if values are symbols or text for clear buttons.
		if (buttonText == "=") {
			if (this->GetText()->Length > 0) {
				try {
					// Replace all instances of "Ans" with the actual previous answer.
					String^ calcString = this->GetText()->Replace("Ans", previousTotal.ToString());

					// Make a connection to the server for evaluation.
					// We're able to use these values because the server and client will be running on the same machine.
					// Usually this would be specified by the user, depending on the application.
					IPAddress^ ip = (IPAddress^)Dns::GetHostEntry(Dns::GetHostName())->AddressList[0];
					IPEndPoint^ endpoint = gcnew IPEndPoint(ip, 1234);
					Socket^ socket = gcnew Socket(ip->AddressFamily, SocketType::Stream, ProtocolType::Tcp);
					socket->Connect(endpoint);
					ServerConnection^ connection = gcnew ServerConnection(socket, calcString, this);

					// Ensure that the TCP handshake occurs.
					try {
						connection->ConnectionHandshake();
					}
					catch (Exception^ e) {
						Console::WriteLine("Connection failed: {0}", e->Message);
						socket->Close();
						return;
					}

					Thread^ childThread = gcnew Thread(gcnew ThreadStart(connection, &ServerConnection::EvaluateExpression));
					childThread->Start();
				}
				catch (OverflowException^) {
					// Calculated value is over the limit of a double variable.
					// Double objects tend to be pretty good about how they handle memory.
					this->ClearText();
					this->textBox1->Text = "OVERFLOW";
					this->currentState = State::ERROR;
				}
				catch (Exception^) {
					// The only reason the calc function will throw another error is due to a syntax
					// error present in the passed expression.
					this->ClearText();
					this->textBox1->Text = "SYNTAX";
					this->currentState = State::ERROR;
				}
			}
		}
		else if (buttonText == "CE") {
			// Clear last entry.
			// Requires the program to keep track of how long the current entry is.
			// Remove the length of the current entry off of the back of the calc string.
			if (this->currentState == State::ERROR ||
				this->currentState == State::TOTAL ||
				!this->currentEntry->IsPartial) {
				this->ClearText();
			}
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
		// Unfinished - do not plan on finishing.
		// else if (buttonText == "Ans") {
		//	// Only add "Ans" if the value is not partial.
		//	if (this->currentEntry->IsPartial) {
		//		this->textBox1->Text += "Ans";
		//		this->currentEntry->Value = "Ans";
		// 	}
		// }
		else if (buttonText == ".") {
			this->AppendNumber(buttonText);  // Treat the '.' as a part of a number.
		}
		else {  // Input is guaranteed to be an operator.
			// Append to calc string.
			this->AppendOperand(buttonText);
		}
	}
}
