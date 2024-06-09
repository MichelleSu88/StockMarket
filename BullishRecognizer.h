#include "PatternRecognizer.h"
using namespace System;
using namespace System::Collections::Generic;

// Bullish Pattern Recognizer class
public ref class BullishRecognizer : public PatternRecognizer {
public:
    // Returns the name of the pattern
    virtual System::String^ PatternName() override {
        return "Bullish";
    }
    // Checks if a Bullish pattern is present at the specified position
    virtual bool IsPatternPresent(BindingList<SmartCandlestick^>^ candlesticks, int position) override {
        if (position < 0 || position >= candlesticks->Count) return false;
        auto candle = candlesticks[position];
        return candle->IsBullish;
    }

    // Returns the range of indices forming the Bullish pattern
    virtual System::Tuple<int, int>^ GetPatternRange(BindingList<SmartCandlestick^>^ candlesticks, int position) override {
        if (IsPatternPresent(candlesticks, position)) {
            return gcnew System::Tuple<int, int>(position, position);
        }
        return gcnew System::Tuple<int, int>(-1, -1);
    }

    // Returns the string representation of the pattern
    virtual System::String^ ToString() override {
        return PatternName();
    }
};
