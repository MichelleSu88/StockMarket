#include "PatternRecognizer.h"
using namespace System;
using namespace System::Collections::Generic;

// Class for recognizing Inverted Hammer pattern
public ref class InvertedHammerRecognizer : public PatternRecognizer {
public:
    // Override the method to get the pattern name
    virtual System::String^ PatternName() override {
        return "Inverted Hammer";
    }

    // Override method to check if the Inverted Hammer pattern is present at a specific position
    virtual bool IsPatternPresent(BindingList<SmartCandlestick^>^ candlesticks, int position) override {
        if (position < 0 || position >= candlesticks->Count) return false;
        auto candle = candlesticks[position];
        return candle->IsBullish && // Bullish candle
            candle->BodyRange <= (candle->Range * 0.3) && // Small body
            candle->BottomWick <= (candle->BodyRange * 0.5) && // Small or no lower wick
            candle->TopWick >= (candle->Range * 0.5); // Long upper wick
    }
    // Override method to get the range of the Inverted Hammer pattern
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

