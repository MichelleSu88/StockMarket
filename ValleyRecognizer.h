#include "PatternRecognizer.h"
using namespace System;
using namespace System::Collections::Generic;

public ref class ValleyRecognizer : PatternRecognizer {
public:
    virtual System::String^ PatternName() override {
        return "Valley";
    }

    virtual bool IsPatternPresent(BindingList<SmartCandlestick^>^ candlesticks, int position) override {
        if (position < 1 || position >= candlesticks->Count - 1) return false;
        auto leftCandle = candlesticks[position - 1];
        auto middleCandle = candlesticks[position];
        auto rightCandle = candlesticks[position + 1];

        return middleCandle->Low < leftCandle->Low && middleCandle->Low < rightCandle->Low;
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


