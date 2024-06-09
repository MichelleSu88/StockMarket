#pragma once

public ref class Candlestick
{
public:
    System::DateTime Date;
    double Open;
    double High;
    double Low;
    double Close;
    double Volume;

    // Constructor
    Candlestick(System::DateTime date, double open, double high, double low, double close, double volume)
    {
        Date = date;
        Open = open;
        High = high;
        Low = low;
        Close = close;
        Volume = volume;
    }
};

