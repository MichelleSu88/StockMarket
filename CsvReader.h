#pragma once

using namespace System;
using namespace System::Collections::Generic;
using namespace System::ComponentModel;


ref class SmartCandlestick;  // Forward declaration of Candlestick class

ref class CsvReader
{
public:
    BindingList<SmartCandlestick^>^ ReadCsvData(String^ filePath);  // Declaration of member function
};
