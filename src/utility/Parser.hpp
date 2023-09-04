#include <algorithm>
#include <iomanip>
#include <iostream>
#include <optional>
#include <string>

std::optional<std::string> getOption(char **begin, char **end, const std::string &option)
{
    char **itr = std::find(begin, end, option);
    if (itr != end && ++itr != end)
        return *itr;
    return std::nullopt;
}

bool optionExists(char **begin, char **end, const std::string &option)
{
    return std::find(begin, end, option) != end;
}

void printHelp()
{
    static constexpr int optionWidth = 16;
    std::cout << "Usage: Everland [options]\n"
              << "Options:\n"
              << std::left << std::setw(optionWidth)
              << "  -h, --help"
              << " - Show this help message\n"
              << std::left << std::setw(optionWidth)
              << "  -d, --debug"
              << " - Enable debug mode\n";
}

ApplicationOptions parseCommandLineInput(int argc, char **argv)
{
    ApplicationOptions options{};

    if (optionExists(argv, argv + argc, "-h") || optionExists(argv, argv + argc, "--help"))
    {
        printHelp();
        exit(0);
    }

    if (optionExists(argv, argv + argc, "-d") || optionExists(argv, argv + argc, "--debug"))
        options.debugModeEnabled = true;

    return options;
}