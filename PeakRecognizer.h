#include "PatternRecognizer.h"
using namespace System;
using namespace System::Collections::Generic;

// Class for recognizing the Peak pattern
public ref class PeakRecognizer : PatternRecognizer {
public:
    virtual System::String^ PatternName() override {
        return "Peak";
    }

    virtual bool IsPatternPresent(BindingList<SmartCandlestick^>^ candlesticks, int position) override {
        if (position < 1 || position >= candlesticks->Count - 1) return false;
        auto leftCandle = candlesticks[position - 1];
        auto middleCandle = candlesticks[position];
        auto rightCandle = candlesticks[position + 1];

        return middleCandle->High > leftCandle->High && middleCandle->High > rightCandle->High;
    }

    virtual System::Tuple<int, int>^ GetPatternRange(BindingList<SmartCandlestick^>^ candlesticks, int position) override {
        if (IsPatternPresent(candlesticks, position)) {
            return gcnew System::Tuple<int, int>(position - 1, position + 1);
        }
        return gcnew System::Tuple<int, int>(-1, -1);
    }

    virtual System::String^ ToString() override {
        return PatternName();
    }
};
