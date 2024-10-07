#pragma once

#ifndef ENUM_COLORS_HPP
#define ENUM_COLORS_HPP

namespace ConsoleExt
{
    enum ConsoleForegroundColor : int
    {
        ForeBlack = 30,
        ForeRed = 31,
        ForeGreen = 32,
        ForeYellow = 33,
        ForeBlue = 34,
        ForeMagenta = 35,
        ForeCyan = 36,
        ForeWhite = 37,
        ForeGray = 90,
        ForeBrightRed = 91,
        ForeBrightGreen = 92,
        ForeBrightYellow = 93,
        ForeBrightBlue = 94,
        ForeBrightMagenta = 95,
        ForeBrightCyan = 96,
        ForeBrightWhite = 97
    }
    typedef ConsoleForegroundColor;

    enum ConsoleBackgroundColor : int
    {
        BackBlack = 40,
        BackRed = 41,
        BackGreen = 42,
        BackYellow = 43,
        BackBlue = 44,
        BackMagenta = 45,
        BackCyan = 46,
        BackWhite = 47,
        BackGray = 100,
        BackBrightRed = 101,
        BackBrightGreen = 102,
        BackBrightYellow = 103,
        BackBrightBlue = 104,
        BackBrightMagenta = 105,
        BackBrightCyan = 106,
        BackBrightWhite = 107
    }
    typedef ConsoleBackgroundColor;
}

#endif // !ENUM_COLORS_HPP