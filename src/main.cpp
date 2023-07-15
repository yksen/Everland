#include "Application.hpp"
#include "Parser.hpp"

int main(int argc, char **argv)
{
    auto options = parseCommandLineInput(argc, argv);
    Application app(options);

    return 0;
}