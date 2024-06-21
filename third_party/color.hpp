// color.hpp
#ifndef COLOR_HPP
#define COLOR_HPP

#ifdef _WIN32
#include <windows.h>
#else
#include <iostream>
#endif

namespace dye
{

#ifdef _WIN32
    inline bool getConsoleScreenBufferInfo(CONSOLE_SCREEN_BUFFER_INFO &info)
    {
        return GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
    }

    inline void setConsoleTextAttribute(WORD attribute)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), attribute);
    }

    inline std::string yellow_on_black(const std::string &text)
    {
        CONSOLE_SCREEN_BUFFER_INFO info;
        if (getConsoleScreenBufferInfo(info))
        {
            setConsoleTextAttribute(FOREGROUND_RED | FOREGROUND_GREEN | BACKGROUND_INTENSITY);
            std::cout << text;
            setConsoleTextAttribute(info.wAttributes);
        }
        return "";
    }

    inline std::string white_on_green(const std::string &text)
    {
        CONSOLE_SCREEN_BUFFER_INFO info;
        if (getConsoleScreenBufferInfo(info))
        {
            setConsoleTextAttribute(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | BACKGROUND_GREEN);
            std::cout << text;
            setConsoleTextAttribute(info.wAttributes);
        }
        return "";
    }

    inline std::string red_on_black(const std::string &text)
    {
        CONSOLE_SCREEN_BUFFER_INFO info;
        if (getConsoleScreenBufferInfo(info))
        {
            setConsoleTextAttribute(FOREGROUND_RED);
            std::cout << text;
            setConsoleTextAttribute(info.wAttributes);
        }
        return "";
    }

    inline std::string green_on_black(const std::string &text)
    {
        CONSOLE_SCREEN_BUFFER_INFO info;
        if (getConsoleScreenBufferInfo(info))
        {
            setConsoleTextAttribute(FOREGROUND_GREEN);
            std::cout << text;
            setConsoleTextAttribute(info.wAttributes);
        }
        return "";
    }

    inline std::string aqua_on_black(const std::string &text)
    {
        CONSOLE_SCREEN_BUFFER_INFO info;
        if (getConsoleScreenBufferInfo(info))
        {
            setConsoleTextAttribute(FOREGROUND_GREEN | FOREGROUND_BLUE);
            std::cout << text;
            setConsoleTextAttribute(info.wAttributes);
        }
        return "";
    }

    inline std::string purple_on_black(const std::string &text)
    {
        CONSOLE_SCREEN_BUFFER_INFO info;
        if (getConsoleScreenBufferInfo(info))
        {
            setConsoleTextAttribute(FOREGROUND_RED | FOREGROUND_BLUE);
            std::cout << text;
            setConsoleTextAttribute(info.wAttributes);
        }
        return "";
    }

#else
    // ANSI escape codes for non-Windows systems
    inline std::string yellow_on_black(const std::string &text)
    {
        return "\033[33;40m" + text + "\033[0m";
    }

    inline std::string white_on_green(const std::string &text)
    {
        return "\033[37;42m" + text + "\033[0m";
    }

    inline std::string red_on_black(const std::string &text)
    {
        return "\033[31;40m" + text + "\033[0m";
    }

    inline std::string green_on_black(const std::string &text)
    {
        return "\033[32;40m" + text + "\033[0m";
    }

    inline std::string aqua_on_black(const std::string &text)
    {
        return "\033[36;40m" + text + "\033[0m";
    }

    inline std::string purple_on_black(const std::string &text)
    {
        return "\033[35;40m" + text + "\033[0m";
    }

#endif

} // namespace dye

#endif // COLOR_HPP
