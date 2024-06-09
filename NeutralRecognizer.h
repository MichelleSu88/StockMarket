#include "PatternRecognizer.h"
using namespace System;
using namespace System::Collections::Generic;

// Class for recognizing the Neutral pattern
public ref class NeutralRecognizer : public PatternRecognizer {
public:
    // Override the method to get the pattern name
    virtual System::String^ PatternName() override {
        return "Neutral";
    }
    // Override method to check if the Neutral pattern is present at a specific position
    virtual bool IsPatternPresent(BindingList<SmartCandlestick^>^ candlesticks, int position) override {
        if (position < 0 || position >= candlesticks->Count) return false;
        auto candle = candlesticks[position];
        return candle->Open == candle->Close;
    }
    // Override method to get the range of the Neutral pattern
    virtual System::Tuple<int, int>^ GetPatternRange(BindingList<SmartCandlestick^>^ candlesticks, int position) override {
        if (IsPatternPresent(candlesticks, position)) {
            return gcnew System::Tuple<int, int>(position, position);
        }
        return gcnew System::Tuple<int, int>(-1, -1);
    }
    // Override method to get a string representation of the pattern
    virtual System::String^ ToString() override {
        return PatternName();
    }
};
