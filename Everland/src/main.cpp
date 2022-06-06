#include "Application.h"

int main()
{
    Everland::Application::init();

    return 0;
}

// g++ -I../include -c Application.cpp Camera.cpp Player.cpp World.cpp Window.cpp main.cpp glad.c -O3; if ($?) { g++ Application.o Camera.o Player.o World.o Window.o main.o glad.o -o Everland -lglfw3 -lgdi32 }; if ($?) { .\Everland.exe }