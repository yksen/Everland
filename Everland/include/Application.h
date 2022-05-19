#ifndef APPLICATION_H
#define APPLICATION_H

#include <GLFW/glfw3.h>

namespace Everland
{
    namespace Application
    {
        void init();
    }
}

#endif

// g++ -I../include -c Camera.cpp World.cpp Window.cpp Application.cpp Block.cpp main.cpp glad.c stb_image.cpp -O3; if ($?) { g++ Camera.o World.o Window.o Application.o Block.o main.o glad.o stb_image.o -o Everland -lglfw3 -lgdi32 }; if ($?) { .\Everland.exe }