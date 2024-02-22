#pragma once

#include "calc.h";

namespace CppUIProject {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// The main form, which handles all calculator operations.
	/// </summary>
	public ref class Form1 : public Form
	{
	private:

		ref struct Entry;

		enum class State {
			TOTAL,
			ERROR,
			NONE
		};

		String^ calcString;
		Entry^ currentEntry;
		Double previousTotal;
		State currentState;

	public:
		Form1(void);

		Void AppendNumber(Int32 c);

		Void AppendOperand(String^ c);
		
		Void ClearText();

		String^ GetText();

		Void HandleClick(Object^ sender, EventArgs^ e);

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ button1;
	protected:
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::Button^ button4;
	private: System::Windows::Forms::Button^ button5;
	private: System::Windows::Forms::Button^ button6;
	private: System::Windows::Forms::Button^ button7;
	private: System::Windows::Forms::Button^ button8;
	private: System::Windows::Forms::Button^ button9;
	private: System::Windows::Forms::Button^ button10;
	private: System::Windows::Forms::Button^ button11;
	private: System::Windows::Forms::Button^ button12;
	private: System::Windows::Forms::Button^ button13;
	private: System::Windows::Forms::Button^ button14;
	private: System::Windows::Forms::Button^ button15;
	private: System::Windows::Forms::Button^ button16;
	private: System::Windows::Forms::Button^ button17;
	private: System::Windows::Forms::Button^ button18;
	private: System::Windows::Forms::Button^ button19;
	private: System::Windows::Forms::TextBox^ textBox1;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->button6 = (gcnew System::Windows::Forms::Button());
			this->button7 = (gcnew System::Windows::Forms::Button());
			this->button8 = (gcnew System::Windows::Forms::Button());
			this->button9 = (gcnew System::Windows::Forms::Button());
			this->button10 = (gcnew System::Windows::Forms::Button());
			this->button11 = (gcnew System::Windows::Forms::Button());
			this->button12 = (gcnew System::Windows::Forms::Button());
			this->button13 = (gcnew System::Windows::Forms::Button());
			this->button14 = (gcnew System::Windows::Forms::Button());
			this->button15 = (gcnew System::Windows::Forms::Button());
			this->button16 = (gcnew System::Windows::Forms::Button());
			this->button17 = (gcnew System::Windows::Forms::Button());
			this->button18 = (gcnew System::Windows::Forms::Button());
			this->button19 = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(48, 69);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(42, 27);
			this->button1->TabIndex = 0;
			this->button1->Text = L"1";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::HandleClick);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(96, 69);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(42, 27);
			this->button2->TabIndex = 1;
			this->button2->Text = L"2";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Form1::HandleClick);
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(144, 69);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(42, 27);
			this->button3->TabIndex = 2;
			this->button3->Text = L"3";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &Form1::HandleClick);
			// 
			// button4
			// 
			this->button4->Location = System::Drawing::Point(48, 102);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(42, 27);
			this->button4->TabIndex = 3;
			this->button4->Text = L"4";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &Form1::HandleClick);
			// 
			// button5
			// 
			this->button5->Location = System::Drawing::Point(96, 102);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(42, 27);
			this->button5->TabIndex = 4;
			this->button5->Text = L"5";
			this->button5->UseVisualStyleBackColor = true;
			this->button5->Click += gcnew System::EventHandler(this, &Form1::HandleClick);
			// 
			// button6
			// 
			this->button6->Location = System::Drawing::Point(144, 102);
			this->button6->Name = L"button6";
			this->button6->Size = System::Drawing::Size(42, 27);
			this->button6->TabIndex = 5;
			this->button6->Text = L"6";
			this->button6->UseVisualStyleBackColor = true;
			this->button6->Click += gcnew System::EventHandler(this, &Form1::HandleClick);
			// 
			// button7
			// 
			this->button7->Location = System::Drawing::Point(48, 135);
			this->button7->Name = L"button7";
			this->button7->Size = System::Drawing::Size(42, 27);
			this->button7->TabIndex = 6;
			this->button7->Text = L"7";
			this->button7->UseVisualStyleBackColor = true;
			this->button7->Click += gcnew System::EventHandler(this, &Form1::HandleClick);
			// 
			// button8
			// 
			this->button8->Location = System::Drawing::Point(96, 135);
			this->button8->Name = L"button8";
			this->button8->Size = System::Drawing::Size(42, 27);
			this->button8->TabIndex = 7;
			this->button8->Text = L"8";
			this->button8->UseVisualStyleBackColor = true;
			this->button8->Click += gcnew System::EventHandler(this, &Form1::HandleClick);
			// 
			// button9
			// 
			this->button9->Location = System::Drawing::Point(144, 135);
			this->button9->Name = L"button9";
			this->button9->Size = System::Drawing::Size(42, 27);
			this->button9->TabIndex = 8;
			this->button9->Text = L"9";
			this->button9->UseVisualStyleBackColor = true;
			this->button9->Click += gcnew System::EventHandler(this, &Form1::HandleClick);
			// 
			// button10
			// 
			this->button10->Location = System::Drawing::Point(48, 168);
			this->button10->Name = L"button10";
			this->button10->Size = System::Drawing::Size(42, 27);
			this->button10->TabIndex = 11;
			this->button10->Text = L"0";
			this->button10->UseVisualStyleBackColor = true;
			this->button10->Click += gcnew System::EventHandler(this, &Form1::HandleClick);
			// 
			// button11
			// 
			this->button11->Location = System::Drawing::Point(96, 168);
			this->button11->Name = L"button11";
			this->button11->Size = System::Drawing::Size(42, 27);
			this->button11->TabIndex = 10;
			this->button11->Text = L".";
			this->button11->UseVisualStyleBackColor = true;
			this->button11->Click += gcnew System::EventHandler(this, &Form1::HandleClick);
			// 
			// button12
			// 
			this->button12->Location = System::Drawing::Point(144, 168);
			this->button12->Name = L"button12";
			this->button12->Size = System::Drawing::Size(42, 27);
			this->button12->TabIndex = 9;
			this->button12->Text = L"Ans";
			this->button12->UseVisualStyleBackColor = true;
			// 
			// button13
			// 
			this->button13->Location = System::Drawing::Point(192, 135);
			this->button13->Name = L"button13";
			this->button13->Size = System::Drawing::Size(42, 60);
			this->button13->TabIndex = 12;
			this->button13->Text = L"+";
			this->button13->UseVisualStyleBackColor = true;
			this->button13->Click += gcnew System::EventHandler(this, &Form1::HandleClick);
			// 
			// button14
			// 
			this->button14->Location = System::Drawing::Point(192, 102);
			this->button14->Name = L"button14";
			this->button14->Size = System::Drawing::Size(42, 27);
			this->button14->TabIndex = 13;
			this->button14->Text = L"x";
			this->button14->UseVisualStyleBackColor = true;
			this->button14->Click += gcnew System::EventHandler(this, &Form1::HandleClick);
			// 
			// button15
			// 
			this->button15->Location = System::Drawing::Point(238, 102);
			this->button15->Name = L"button15";
			this->button15->Size = System::Drawing::Size(42, 27);
			this->button15->TabIndex = 14;
			this->button15->Text = L"/";
			this->button15->UseVisualStyleBackColor = true;
			this->button15->Click += gcnew System::EventHandler(this, &Form1::HandleClick);
			// 
			// button16
			// 
			this->button16->Location = System::Drawing::Point(238, 135);
			this->button16->Name = L"button16";
			this->button16->Size = System::Drawing::Size(42, 27);
			this->button16->TabIndex = 15;
			this->button16->Text = L"-";
			this->button16->UseVisualStyleBackColor = true;
			this->button16->Click += gcnew System::EventHandler(this, &Form1::HandleClick);
			// 
			// button17
			// 
			this->button17->Location = System::Drawing::Point(238, 168);
			this->button17->Name = L"button17";
			this->button17->Size = System::Drawing::Size(42, 27);
			this->button17->TabIndex = 16;
			this->button17->Text = L"=";
			this->button17->UseVisualStyleBackColor = true;
			this->button17->Click += gcnew System::EventHandler(this, &Form1::HandleClick);
			// 
			// button18
			// 
			this->button18->Location = System::Drawing::Point(192, 69);
			this->button18->Name = L"button18";
			this->button18->Size = System::Drawing::Size(42, 27);
			this->button18->TabIndex = 17;
			this->button18->Text = L"CA";
			this->button18->UseVisualStyleBackColor = true;
			this->button18->Click += gcnew System::EventHandler(this, &Form1::HandleClick);
			// 
			// button19
			// 
			this->button19->Location = System::Drawing::Point(238, 69);
			this->button19->Name = L"button19";
			this->button19->Size = System::Drawing::Size(42, 27);
			this->button19->TabIndex = 18;
			this->button19->Text = L"CE";
			this->button19->UseVisualStyleBackColor = true;
			this->button19->Click += gcnew System::EventHandler(this, &Form1::HandleClick);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(48, 34);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(232, 20);
			this->textBox1->TabIndex = 19;
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(328, 218);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->button19);
			this->Controls->Add(this->button18);
			this->Controls->Add(this->button17);
			this->Controls->Add(this->button16);
			this->Controls->Add(this->button15);
			this->Controls->Add(this->button14);
			this->Controls->Add(this->button13);
			this->Controls->Add(this->button10);
			this->Controls->Add(this->button11);
			this->Controls->Add(this->button12);
			this->Controls->Add(this->button9);
			this->Controls->Add(this->button8);
			this->Controls->Add(this->button7);
			this->Controls->Add(this->button6);
			this->Controls->Add(this->button5);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Name = L"Form1";
			this->Text = L"Problem 1 - Calculator";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
};
}
