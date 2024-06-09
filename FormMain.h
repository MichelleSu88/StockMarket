// Michelle Su, U64567207
#pragma once
#include "CsvReader.h"
#include "Candlestick.h"
#include "SmartCandlestick.h"
#include "Form1.h"

namespace C__StockProject {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;
	using namespace System::Windows::Forms::DataVisualization::Charting;
	using namespace System::ComponentModel;


   // This includes all the properties for FormMain which loads and displays the initial stock chosen
	public ref class FormMain : public System::Windows::Forms::Form
	{
	public:
		FormMain(void)
		{
			InitializeComponent();
			this->dateTimePicker_start->Value = DateTime(2022, 11, 10);
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~FormMain()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::DateTimePicker^ dateTimePicker_start;
	protected:
	private: System::Windows::Forms::DateTimePicker^ dateTimePicker_end;
	private: System::Windows::Forms::Button^ button_load;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;

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
			this->dateTimePicker_start = (gcnew System::Windows::Forms::DateTimePicker());
			this->dateTimePicker_end = (gcnew System::Windows::Forms::DateTimePicker());
			this->button_load = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// dateTimePicker_start
			// 
			this->dateTimePicker_start->Location = System::Drawing::Point(60, 25);
			this->dateTimePicker_start->Name = L"dateTimePicker_start";
			this->dateTimePicker_start->Size = System::Drawing::Size(200, 20);
			this->dateTimePicker_start->TabIndex = 0;
			// 
			// dateTimePicker_end
			// 
			this->dateTimePicker_end->Location = System::Drawing::Point(373, 25);
			this->dateTimePicker_end->Name = L"dateTimePicker_end";
			this->dateTimePicker_end->Size = System::Drawing::Size(200, 20);
			this->dateTimePicker_end->TabIndex = 1;
			// 
			// button_load
			// 
			this->button_load->Location = System::Drawing::Point(279, 25);
			this->button_load->Name = L"button_load";
			this->button_load->Size = System::Drawing::Size(75, 23);
			this->button_load->TabIndex = 2;
			this->button_load->Text = L"Load Data";
			this->button_load->UseVisualStyleBackColor = true;
			this->button_load->Click += gcnew System::EventHandler(this, &FormMain::button_load_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(142, 6);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(58, 13);
			this->label1->TabIndex = 3;
			this->label1->Text = L"Start Date:";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(439, 6);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(55, 13);
			this->label2->TabIndex = 4;
			this->label2->Text = L"End Date:";
			// 
			// FormMain
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(636, 57);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->button_load);
			this->Controls->Add(this->dateTimePicker_end);
			this->Controls->Add(this->dateTimePicker_start);
			this->Name = L"FormMain";
			this->Text = L"FormMain";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		// This is the event handler for the load button
	private: System::Void button_load_Click(System::Object^ sender, System::EventArgs^ e) {
		OpenFileDialog^ openFileDialog = gcnew OpenFileDialog();
		openFileDialog->InitialDirectory = Path::GetFullPath("..\\Stock Data");
		openFileDialog->Filter = "Daily Files|*-Day.csv|Weekly Files|*-Week.csv|Monthly Files|*-Month.csv|All Files (*.csv)|*.csv";
		openFileDialog->FilterIndex = 4;  // Set to 4 to show all files by default
		openFileDialog->Title = "Select a CSV File";
		openFileDialog->Multiselect = true; // Enable selection of multiple files

		// Show OpenFileDialog and check if a file was selected
		if (openFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			// Get the selected date range
			DateTime startDate = dateTimePicker_start->Value.Date;
			DateTime endDate = dateTimePicker_end->Value.Date;

			// Validating the date range to make sure the start date is before the end date
			if (startDate > endDate)
			{
				MessageBox::Show("Invalid date.", "ERROR",
					MessageBoxButtons::OK, MessageBoxIcon::Error);
				return;
			}

			// Loop through each file selected
			for each (String ^ filePath in openFileDialog->FileNames)
			{
				// Use CsvReader to read the data
				CsvReader^ csvReader = gcnew CsvReader();
				BindingList<SmartCandlestick^>^ stockData = csvReader->ReadCsvData(filePath);

				// Create and show a new form for each file
				Form1^ chartForm = gcnew Form1(stockData, startDate, endDate, filePath);
				chartForm->Show();
			}
		}
	}
	};
}
