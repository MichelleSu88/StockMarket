#pragma once

// Importing necessary namespaces for the functionality in the code.
#include "pch.h"
#include "CsvReader.h"
#include "SmartCandlestick.h"
#include "Candlestick.h"

using namespace System;
using namespace System::IO;
using namespace System::Collections::Generic;
using namespace System::Windows::Forms;
using namespace System::Globalization;
using namespace System::Text;
using namespace Microsoft::VisualBasic::FileIO;
using namespace System::ComponentModel;

// This function reads from a CSV files
BindingList<SmartCandlestick^>^ CsvReader::ReadCsvData(String^ filePath)
{
    // Initialize a BindingList to store the Candlestick objects.
    BindingList<SmartCandlestick^>^ data = gcnew BindingList<SmartCandlestick^>();

    //This initializes a parser to read the file 
    TextFieldParser^ parser = gcnew TextFieldParser(filePath);
    parser->TextFieldType = FieldType::Delimited;  // Indicate that the file is delimited.
    parser->SetDelimiters(",");  // Set the delimiter character as comma.
    parser->HasFieldsEnclosedInQuotes = true;  // Handle situations where fields are enclosed in quotes, 
    // which may contain commas.

    try
    {
        // Skip the header line if it exists to avoid trying to parse the header as data.
        if (!parser->EndOfData)
            parser->ReadFields();

        // Loop through the lines in the file until the end of the data is reached.
        while (!parser->EndOfData)
        {
            array<String^>^ line;
            try
            {
                // Read the fields in the line.
                line = parser->ReadFields();

                // Create a new Candlestick object and populate its properties with the parsed data
                SmartCandlestick^ sd = gcnew SmartCandlestick(
                    DateTime::Parse(line[2]),  // Date
                    Double::Parse(line[3]),   // Open
                    Double::Parse(line[4]),   // High
                    Double::Parse(line[5]),   // Low
                    Double::Parse(line[6]),   // Close
                    Double::Parse(line[7])    // Volume
                );


                // Add the newly created and populated Candlestick object to the data list.
                data->Add(sd);
            }
            // Handle potential issues with malformed lines, such as wrong number of fields, etc.
            catch (MalformedLineException^)
            {
                // Display an error message and skip the line.
                MessageBox::Show("Line " + parser->LineNumber + " is invalid. Skipping.");
            }
        }
    }
    // Catch general exceptions that might occur during file reading and parsing.
    catch (Exception^ ex)
    {
        // Display an error message.
        MessageBox::Show("Error reading CSV file: " + ex->Message);
    }
    finally
    {
        // Always ensure that the parser is closed, even if an error occurs.
        parser->Close();
    }

    // Returns the populated BindingList of Candlestick objects.
    return data;
}
