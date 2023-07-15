#pragma once

struct ApplicationOptions
{
    bool debugModeEnabled = false;
};

class Application
{
public:
    Application(const ApplicationOptions &options);
    ~Application() = default;

    void gameLoop();

private:
    ApplicationOptions options;
};
