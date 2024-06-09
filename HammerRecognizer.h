#include "PatternRecognizer.h"
using namespace System;
using namespace System::Collections::Generic;

// Class for recognizing Hammer pattern
public ref class HammerRecognizer : public PatternRecognizer {
public:
    // Override the method to get the pattern name
    virtual System::String^ PatternName() override {
        return "Hammer";
    }
    // Override method to check if the Hammer pattern is present at a specific position
    virtual bool IsPatternPresent(BindingList<SmartCandlestick^>^ candlesticks, int position) override {
        if (position < 0 || position >= candlesticks->Count) return false;
        auto candle = candlesticks[position];
        return candle->IsBullish && // Bullish candle
            candle->BodyRange <= (candle->Range * 0.3) && // Small body
            candle->TopWick <= (candle->BodyRange * 0.5) && // Small or no upper wick
            candle->BottomWick >= (candle->Range * 0.5); // Long lower wick
    }

    // Override method to get the range of the Hammer pattern
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

