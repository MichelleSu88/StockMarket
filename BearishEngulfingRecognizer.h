#include "PatternRecognizer.h"
using namespace System;
using namespace System::Collections::Generic;

// Bearish Engulfing Pattern Recognizer class
public ref class BearishEngulfingRecognizer : PatternRecognizer {
public:
    // Returns the name of the pattern
    virtual System::String^ PatternName() override {
        return "Bearish Engulfing";
    }
    // Checks if the Bearish Engulfing pattern is present at the specified position
    virtual bool IsPatternPresent(BindingList<SmartCandlestick^>^ candlesticks, int position) override {
        // Ensure the position is within valid range
        if (position < 1 || position >= candlesticks->Count) return false;

        // Get current and previous candles
        auto current = candlesticks[position];
        auto previous = candlesticks[position - 1];

        // Check conditions for Bearish Engulfing pattern
        return previous->IsBullish && current->IsBearish &&
            current->Open > previous->Close && current->Close < previous->Open;
    }

    // Returns the range of indices forming the Bearish Engulfing pattern
    virtual System::Tuple<int, int>^ GetPatternRange(BindingList<SmartCandlestick^>^ candlesticks, int position) override {
        if (IsPatternPresent(candlesticks, position)) {
            return gcnew System::Tuple<int, int>(position - 1, position);
        }
        return gcnew System::Tuple<int, int>(-1, -1);
    }

    // Returns the string representation of the pattern
    virtual System::String^ ToString() override {
        return PatternName();
    }
};
