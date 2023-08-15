#include "Application.hpp"
#include "Parser.hpp"

int main(int argc, char **argv)
{
    auto options = parseCommandLineInput(argc, argv);
    std::make_unique<Application>(std::move(options));

    return 0;
}