#pragma once

class Application
{
public:
    Application(bool debugModeEnabled = false);
    ~Application() = default;

    void gameLoop();

private:
    bool debugModeEnabled;
};
