#include "PatternRecognizer.h"
using namespace System;
using namespace System::Collections::Generic;

// Class for recognizing Gravestone Doji pattern
public ref class GravestoneDojiRecognizer : public PatternRecognizer {
public:
    // Override the method to get the pattern name
    virtual System::String^ PatternName() override {
        return "Gravestone Doji";
    }

    // Override method to check if the Gravestone Doji pattern is present at a specific position
    virtual bool IsPatternPresent(BindingList<SmartCandlestick^>^ candlesticks, int position) override {
        if (position < 0 || position >= candlesticks->Count) return false;
        auto candle = candlesticks[position];
        return std::abs(candle->Open - candle->Close) <= (candle->Range * 0.1) && // Small body
            candle->High == candle->Open && candle->Open == candle->Close; // No upper shadow
    }

    // Override method to get the range of the Gravestone Doji pattern
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

