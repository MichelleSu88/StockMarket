#include "PatternRecognizer.h"
using namespace System;
using namespace System::Collections::Generic;

// Class for recognizing Marubozu pattern
public ref class MarubozuRecognizer : public PatternRecognizer {
public:
    // Override the method to get the pattern name
    virtual System::String^ PatternName() override {
        return "Marubozu";
    }
    // Override method to check if the Marubozu pattern is present at a specific position
    virtual bool IsPatternPresent(BindingList<SmartCandlestick^>^ candlesticks, int position) override {
        if (position < 0 || position >= candlesticks->Count) return false;
        auto candle = candlesticks[position];
        return (candle->Open == candle->Low && candle->Close == candle->High) ||
            (candle->Open == candle->High && candle->Close == candle->Low);
    }
    // Override method to get the range of the Marubozu pattern
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

