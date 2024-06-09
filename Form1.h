//Michelle Su, U64567207
#pragma once
#include "CsvReader.h"
#include "Candlestick.h"
#include "SmartCandlestick.h"
#include "PatternRecognizer.h"
#include "BullishEngulfingRecognizer.h"
#include "BearishEngulfingRecognizer.h"
#include "BullishHaramiRecognizer.h"
#include "BearishHaramiRecognizer.h"
#include "PeakRecognizer.h"
#include "ValleyRecognizer.h"
#include "BearishRecognizer.h"
#include "BullishRecognizer.h"
#include "NeutralRecognizer.h"
#include "MarubozuRecognizer.h"
#include "DojiRecognizer.h"
#include "DragonflyDojiRecognizer.h"
#include "GravestoneDojiRecognizer.h"
#include "HammerRecognizer.h"
#include "InvertedHammerRecognizer.h"

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

	// This includes the design file for displaying the charts with candlesticks and volume as well as distinguising patterns
	public ref class Form1 : public System::Windows::Forms::Form
	{
	private:
		System::ComponentModel::BindingList<SmartCandlestick^>^ candlesticks;
		System::DateTime startDate;
		System::DateTime endDate;
		String^ filePath;

	public:
		Form1(BindingList<SmartCandlestick^>^ candlesticks, DateTime startDate, DateTime endDate, String^ filePath )
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			this->candlesticks = candlesticks;
			this->startDate = startDate;
			this->endDate = endDate;
			this->filePath = filePath;

			String^ fileNameWithoutExtension = Path::GetFileNameWithoutExtension(filePath);
			this->Text = fileNameWithoutExtension;  // Set the form's title bar text

			BindingList<SmartCandlestick^>^ chosenData = gcnew BindingList<SmartCandlestick^>();
			for each (SmartCandlestick ^ candle in candlesticks) {
				if (candle->Date >= startDate && candle->Date <= endDate) {
					chosenData->Add(candle);
				}
			}
			PopulatePatternComboBox();
			ConfigureCandlestickChart(chosenData);
			ConfigureVolumeChart(chosenData);

			dateTimePicker_start->Value = startDate;
			dateTimePicker_end->Value = endDate;
		}

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
	private: System::Windows::Forms::Button^ button_loadData;

	protected:
	private: System::Windows::Forms::ComboBox^ comboBox_patterns;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::DateTimePicker^ dateTimePicker_start;
	private: System::Windows::Forms::DateTimePicker^ dateTimePicker_end;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^ chart_candlesticks;

	private: System::Windows::Forms::Label^ label_start;
	private: System::Windows::Forms::Label^ label_end;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^ chart_volume;




	protected:

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
			System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^ legend1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^ series1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea2 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^ legend2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^ series2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			this->button_loadData = (gcnew System::Windows::Forms::Button());
			this->dateTimePicker_start = (gcnew System::Windows::Forms::DateTimePicker());
			this->dateTimePicker_end = (gcnew System::Windows::Forms::DateTimePicker());
			this->chart_candlesticks = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->label_start = (gcnew System::Windows::Forms::Label());
			this->label_end = (gcnew System::Windows::Forms::Label());
			this->chart_volume = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->comboBox_patterns = (gcnew System::Windows::Forms::ComboBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart_candlesticks))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart_volume))->BeginInit();
			this->SuspendLayout();
			// 
			// button_loadData
			// 
			this->button_loadData->BackColor = System::Drawing::SystemColors::GrayText;
			this->button_loadData->ForeColor = System::Drawing::SystemColors::Control;
			this->button_loadData->Location = System::Drawing::Point(749, 18);
			this->button_loadData->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->button_loadData->Name = L"button_loadData";
			this->button_loadData->Size = System::Drawing::Size(103, 42);
			this->button_loadData->TabIndex = 0;
			this->button_loadData->Text = L"Update";
			this->button_loadData->UseVisualStyleBackColor = false;
			this->button_loadData->Click += gcnew System::EventHandler(this, &Form1::button_loadData_Click);
			// 
			// dateTimePicker_start
			// 
			this->dateTimePicker_start->Location = System::Drawing::Point(103, 31);
			this->dateTimePicker_start->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->dateTimePicker_start->Name = L"dateTimePicker_start";
			this->dateTimePicker_start->Size = System::Drawing::Size(265, 22);
			this->dateTimePicker_start->TabIndex = 2;
			// 
			// dateTimePicker_end
			// 
			this->dateTimePicker_end->Location = System::Drawing::Point(476, 31);
			this->dateTimePicker_end->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->dateTimePicker_end->Name = L"dateTimePicker_end";
			this->dateTimePicker_end->Size = System::Drawing::Size(265, 22);
			this->dateTimePicker_end->TabIndex = 3;
			// 
			// chart_candlesticks
			// 
			chartArea1->Name = L"ChartArea1";
			this->chart_candlesticks->ChartAreas->Add(chartArea1);
			legend1->Name = L"Legend1";
			this->chart_candlesticks->Legends->Add(legend1);
			this->chart_candlesticks->Location = System::Drawing::Point(16, 75);
			this->chart_candlesticks->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->chart_candlesticks->Name = L"chart_candlesticks";
			series1->ChartArea = L"ChartArea1";
			series1->Legend = L"Legend1";
			series1->Name = L"Series1";
			this->chart_candlesticks->Series->Add(series1);
			this->chart_candlesticks->Size = System::Drawing::Size(1208, 199);
			this->chart_candlesticks->TabIndex = 4;
			this->chart_candlesticks->Text = L"chart1";
			// 
			// label_start
			// 
			this->label_start->AutoSize = true;
			this->label_start->Location = System::Drawing::Point(17, 37);
			this->label_start->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label_start->Name = L"label_start";
			this->label_start->Size = System::Drawing::Size(69, 16);
			this->label_start->TabIndex = 6;
			this->label_start->Text = L"Start Date:";
			// 
			// label_end
			// 
			this->label_end->AutoSize = true;
			this->label_end->Location = System::Drawing::Point(395, 37);
			this->label_end->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label_end->Name = L"label_end";
			this->label_end->Size = System::Drawing::Size(66, 16);
			this->label_end->TabIndex = 7;
			this->label_end->Text = L"End Date:";
			// 
			// chart_volume
			// 
			chartArea2->Name = L"ChartArea1";
			this->chart_volume->ChartAreas->Add(chartArea2);
			legend2->Name = L"Legend1";
			this->chart_volume->Legends->Add(legend2);
			this->chart_volume->Location = System::Drawing::Point(16, 306);
			this->chart_volume->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->chart_volume->Name = L"chart_volume";
			series2->ChartArea = L"ChartArea1";
			series2->Legend = L"Legend1";
			series2->Name = L"Series1";
			this->chart_volume->Series->Add(series2);
			this->chart_volume->Size = System::Drawing::Size(1208, 212);
			this->chart_volume->TabIndex = 8;
			this->chart_volume->Text = L"chart1";
			// 
			// comboBox_patterns
			// 
			this->comboBox_patterns->FormattingEnabled = true;
			this->comboBox_patterns->Location = System::Drawing::Point(927, 28);
			this->comboBox_patterns->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->comboBox_patterns->Name = L"comboBox_patterns";
			this->comboBox_patterns->Size = System::Drawing::Size(211, 24);
			this->comboBox_patterns->TabIndex = 9;
			this->comboBox_patterns->Text = L"None";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(867, 36);
			this->label1->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(52, 16);
			this->label1->TabIndex = 10;
			this->label1->Text = L"Pattern:";
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1239, 537);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->comboBox_patterns);
			this->Controls->Add(this->chart_volume);
			this->Controls->Add(this->chart_candlesticks);
			this->Controls->Add(this->label_end);
			this->Controls->Add(this->label_start);
			this->Controls->Add(this->dateTimePicker_end);
			this->Controls->Add(this->dateTimePicker_start);
			this->Controls->Add(this->button_loadData);
			this->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->Name = L"Form1";
			this->Text = L"Form1";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart_candlesticks))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart_volume))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}


#pragma endregion

	// Event handler to load the data given a range of date
	private: System::Void button_loadData_Click(System::Object^ sender, System::EventArgs^ e) {
		// Update startDate and endDate from the date pickers
		DateTime startDate = dateTimePicker_start->Value;
		DateTime endDate = dateTimePicker_end->Value;

		// Input validation where the start date must be before the end date
		if (startDate <= endDate) {
			// Filtering the candlesticks given the time frame
			BindingList<SmartCandlestick^>^ chosenData = gcnew BindingList<SmartCandlestick^>();
			for each (SmartCandlestick ^ candle in candlesticks) {
				if (candle->Date >= startDate && candle->Date <= endDate) {
					chosenData->Add(candle);
				}
			}

			// Calling the functions to update candlestick and volume charts
			ConfigureCandlestickChart(chosenData);
			ConfigureVolumeChart(chosenData);

			// Finding the correct pattern
			PatternRecognizer^ chosenToRecognize = dynamic_cast<PatternRecognizer^>(comboBox_patterns->SelectedItem);
			if (chosenToRecognize == nullptr) {
				return;
			}
			HighlightPattern(chosenToRecognize);	//calling the highlight function for chosen pattern
		}
		else {
			MessageBox::Show("This is an invalid range.", "ERROR");
		}
	}

	// This functions configures the candlestick chart with data
	private: void ConfigureCandlestickChart(BindingList<SmartCandlestick^>^ stockData) {
		// Clear existing chart areas to start with a clean slate
		chart_candlesticks->ChartAreas->Clear();

		// Create a new chart area for the candlestick chart and add it to the chart
		ChartArea^ chartArea = gcnew ChartArea("CandlestickArea");
		chart_candlesticks->ChartAreas->Add(chartArea);

		// Clear existing series from the chart
		chart_candlesticks->Series->Clear();

		// Create a new series for candlestick chart, configure its properties, and add it to the chart
		Series^ series = gcnew Series("CandlestickSeries");
		series->ChartArea = "CandlestickArea";
		series->ChartType = SeriesChartType::Candlestick;
		series->XValueType = ChartValueType::DateTime;
		series->CustomProperties = "PriceDownColor=Red, PriceUpColor=Green";

		// Clear legends to avoid unwanted display
		chart_candlesticks->Legends->Clear();
		chart_candlesticks->Series->Add(series);

		// Iterate through each SmartCandlestick data in the provided stock data
		for each (SmartCandlestick ^ data in stockData) {
			// Create a new data point for each candlestick and set its X and Y values
			DataPoint^ point = gcnew DataPoint();
			point->XValue = data->Date.ToOADate();
			point->YValues = gcnew array<double> { data->High, data->Low, data->Open, data->Close };
			point->Tag = data;
			series->Points->Add(point);
		}

		// Configure chart area axes and appearanc
		chartArea->AxisX->LabelStyle->Format = "MM dd yyyy";
		chartArea->AxisX->MajorGrid->Enabled = false;
		chartArea->AxisY->MajorGrid->Enabled = false;
	}

	// This function configures the volume chart with data
	private: void ConfigureVolumeChart(BindingList<SmartCandlestick^>^ stockData) {
		// Clear existing chart areas to start with a clean slate
		chart_volume->ChartAreas->Clear();

		// Create a new chart area for the volume chart and add it to the chart
		ChartArea^ chartArea = gcnew ChartArea("VolumeArea");
		chart_volume->ChartAreas->Add(chartArea);

		// Clear existing series from the chart
		chart_volume->Series->Clear();

		// Create a new series for volume chart, configure its properties, and add it to the chart
		Series^ series = gcnew Series("VolumeSeries");
		series->ChartArea = "VolumeArea";
		series->ChartType = SeriesChartType::Column;
		series->XValueType = ChartValueType::DateTime;
		series->CustomProperties = "PointWidth=0.6";
		chart_volume->Legends->Clear();
		chart_volume->Series->Add(series);

		// Iterate through each SmartCandlestick data in the provided stock data
		for each (SmartCandlestick ^ data in stockData) {
			// Add a data point to the series for each date and corresponding volume
			series->Points->AddXY(data->Date, data->Volume);
		}

		// Configure chart area axes and appearance for the volume chart
		chartArea->AxisX->LabelStyle->Format = "MMM dd yyyy";
		chartArea->AxisX->MajorGrid->Enabled = false;
		chartArea->AxisY->Title = "Volume";
		chartArea->AxisY->MajorGrid->Enabled = false;
	}

	// This function calculates the min interval between candlesticks of the x-axis values
	private: double CalculateMinInterval(Chart^ chart, String^ seriesName) {
		// Initialize the minimum interval to a large positive value
		double minimumInterval = Double::MaxValue;

		// Initialize a pointer to the previous data point (starting with null for the first iteration)
		DataPoint^ previousPoint = nullptr;

		// Iterate through each data point in the specified series of the chart
		for each (DataPoint ^ point in chart->Series[seriesName]->Points) {
			// Check if this is not the first data point in the series
			if (previousPoint != nullptr) {
				// Calculate the interval (difference) between the X-values of the current and previous data points
				double interval = point->XValue - previousPoint->XValue;
				// Check if the calculated interval is smaller than the current minimum interval
				if (interval < minimumInterval) {
					// Update the minimum interval with the smaller value
					minimumInterval = interval;
				}
			}
			// Update the pointer to the previous data point for the next iteration
			previousPoint = point;
		}

		return minimumInterval;
	}

	// This function highlights using a rectangle the specified candlestick pattern from the data
	private: void HighlightPattern(PatternRecognizer^ patternRecognizer) {
		// Clear the previous annotations
		chart_candlesticks->Annotations->Clear();

		// Calculate the minimum interval between candlesticks on the X-axis
		double minimumInterval = CalculateMinInterval(chart_candlesticks, "CandlestickSeries");
		double annotateWidth = minimumInterval * 0.8; 
		// Iterate through the candlesticks and check for the pattern
		for (int i = 0; i < candlesticks->Count; ++i) {
			auto patternRng = patternRecognizer->GetPatternRange(candlesticks, i);

			// Input validation for the dates
			if (patternRng->Item1 != -1 && patternRng->Item2 != -1) {
				int ptCount = chart_candlesticks->Series["CandlestickSeries"]->Points->Count;
				for (int j = patternRng->Item1; j <= patternRng->Item2; ++j) {
					if (j >= 0 && j < ptCount) {
						DataPoint^ dataPoint = chart_candlesticks->Series["CandlestickSeries"]->Points[j];;
						SmartCandlestick^ candle = dynamic_cast<SmartCandlestick^>(dataPoint->Tag);

						if (candle != nullptr) {
							RectangleAnnotation^ annote = gcnew RectangleAnnotation();
							annote->AxisX = chart_candlesticks->ChartAreas["CandlestickArea"]->AxisX;
							annote->AxisY = chart_candlesticks->ChartAreas["CandlestickArea"]->AxisY;
							annote->AnchorX = dataPoint->XValue;
							annote->AnchorY = candle->Low;
							annote->IsSizeAlwaysRelative = false;
							annote->Width = annotateWidth; // Use the dynamic width
							annote->Height = candle->Low - candle->High;
							annote->LineColor = Color::Blue;
							annote->LineWidth = 2;
							annote->BackColor = Color::FromArgb(50, Color::Blue); // Semi-transparent blue

							chart_candlesticks->Annotations->Add(annote);
						}
					}
				}
				// Skip to the end of the current pattern range to avoid overlapping annotations
				i = patternRng->Item2;
			}
		}
	}

	private: void PopulatePatternComboBox() {
		// Clear existing items
		comboBox_patterns->Items->Clear();

		// Manually add instances of each recognizer
		comboBox_patterns->Items->Add(gcnew BearishEngulfingRecognizer());
		comboBox_patterns->Items->Add(gcnew BullishEngulfingRecognizer());
		comboBox_patterns->Items->Add(gcnew BullishHaramiRecognizer());
		comboBox_patterns->Items->Add(gcnew BearishHaramiRecognizer());
		comboBox_patterns->Items->Add(gcnew PeakRecognizer());
		comboBox_patterns->Items->Add(gcnew ValleyRecognizer());
		comboBox_patterns->Items->Add(gcnew BullishRecognizer());
		comboBox_patterns->Items->Add(gcnew BearishRecognizer());
		comboBox_patterns->Items->Add(gcnew NeutralRecognizer());
		comboBox_patterns->Items->Add(gcnew MarubozuRecognizer());
		comboBox_patterns->Items->Add(gcnew DojiRecognizer());
		comboBox_patterns->Items->Add(gcnew DragonflyDojiRecognizer());
		comboBox_patterns->Items->Add(gcnew GravestoneDojiRecognizer());
		comboBox_patterns->Items->Add(gcnew HammerRecognizer());
		comboBox_patterns->Items->Add(gcnew InvertedHammerRecognizer());


		comboBox_patterns->DisplayMember = "PatternName";
	}
};
}
