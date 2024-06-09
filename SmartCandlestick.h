//Author: Janpaul Paredero
#pragma once
#include "Candlestick.h"
#include <cmath>

/// Represents an enhanced version of a Candlestick, providing additional properties and methods
/// to analyze candlestick patterns commonly used in financial markets.
public ref class SmartCandlestick : public Candlestick
{
public:
    SmartCandlestick(System::DateTime date, double open, double high, double low, double close, double volume)
        : Candlestick(date, open, high, low, close, volume)
    {
    }

    property double Range {
        double get() { return High - Low; }
    }

    property double BodyRange {
        double get() { return System::Math::Abs(Open - Close); }
    }

    property double TopWick {
        double get() { return High - System::Math::Max(Open, Close); }
    }

    property double BottomWick {
        double get() { return System::Math::Min(Open, Close) - Low; }
    }

    property bool IsBullish {
        bool get() { return Close > Open; }
    }

    property bool IsBearish {
        bool get() { return Open > Close; }
    }

};
