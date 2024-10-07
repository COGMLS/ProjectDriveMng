#pragma once

#ifndef CONSOLE_EXT_SGR_OPTIONS_HPP
#define CONSOLE_EXT_SGR_OPTIONS_HPP

namespace ConsoleExt
{
    enum SgrOptions : unsigned short
    {
        ResetConsole = 0,
        FontBold = 1,
        FontLight = 2,
        FontItalic = 3,
        FontUnderline = 4,
        CursorSlowBlink = 5,
        CursorRapidBlink = 6,
        InvertColor = 7,
        PrimaryFont = 10,
        FontNormalIntensity = 22,
        NotItalic = 23,
        NotUnderlined = 24,
        NotBlinking = 25,
        StandardForegroundColor = 30,
        CustomForegroundColor = 38,
        DefaultForegroundColor = 39,
        StandardBackgroundColor = 40,
        CustomBackgroundColor = 48,
        DefaultBackgroundColor = 49,
        Overline = 53,
        NoOverline = 55,
        UseUnderlineColor = 58,
        DefaultUnderlineColor = 59,
        Superscript = 73,
        Subscript = 74,
        NoSuperOrSubScript = 75
    }
    typedef SgrOptions;
}

#endif // !CONSOLE_EXT_SGR_OPTIONS_HPP