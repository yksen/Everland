#include "Application.hpp"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <optional>
#include <string>

std::optional<std::string> getOption(char **begin, char **end, const std::string &option)
{
    char **itr = std::find(begin, end, option);
    if (itr != end && ++itr != end)
    {
        return *itr;
    }
    return std::nullopt;
}

bool optionExists(char **begin, char **end, const std::string &option)
{
    return std::find(begin, end, option) != end;
}

int main(int argc, char **argv)
{
    if (optionExists(argv, argv + argc, "-h") || optionExists(argv, argv + argc, "--help"))
    {
        static const int optionWidth = 16;
        std::cout << "Usage: Everland [options]\n\n";
        std::cout << "Arguments:\n";
        std::cout << std::left << std::setw(optionWidth) << "  -h, --help"
                  << " - Show this help message\n";
        std::cout << std::left << std::setw(optionWidth) << "  -d, --debug"
                  << " - Enable debug mode\n";
    }

    bool debugModeEnabled = (optionExists(argv, argv + argc, "-d") || optionExists(argv, argv + argc, "--debug"));

    Application app(debugModeEnabled);

    return 0;
}