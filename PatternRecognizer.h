#ifndef PATTERN_RECOGNIZER_H
#define PATTERN_RECOGNIZER_H
#include <cliext/list>  // For C++/CLI generic collections
#include "SmartCandlestick.h"
using namespace System::Collections::Generic;  // Namespace for .NET generic collections
using namespace System::ComponentModel;        // Namespace for BindingList
using namespace cliext;                        // Namespace for C++/CLI extensions

public ref class PatternRecognizer abstract {
public:
    virtual ~PatternRecognizer() {}

    virtual System::String^ PatternName() = 0;
    virtual bool IsPatternPresent(BindingList<SmartCandlestick^>^ candlesticks, int position) = 0;
    virtual System::Tuple<int, int>^ GetPatternRange(BindingList<SmartCandlestick^>^ candlesticks, int position) = 0;
};
#endif // PATTERN_RECOGNIZER_H
