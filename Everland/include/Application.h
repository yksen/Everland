#ifndef APPLICATION_H
#define APPLICATION_H

#include <GLFW/glfw3.h>

namespace Everland
{
    namespace Application
    {

        void framebuffer_size_callback(GLFWwindow *window, int width, int height);
        void mouse_callback(GLFWwindow *window, double xpos, double ypos);
        void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
        void processInput(GLFWwindow *window);
        void init();

    }
}

#endif

// g++ -I../include -c World.cpp Renderer.cpp Application.cpp main.cpp glad.c stb_image.cpp -O3; if ($?) { g++ World.o Renderer.o Application.o main.o glad.o stb_image.o -o Everland -lglfw3 -lgdi32 }; if ($?) { .\Everland.exe }