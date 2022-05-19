#ifndef WINDOW_H
#define WINDOW_H

#include <GLFW/glfw3.h>

namespace Everland
{
    namespace Window
    {
        extern GLFWwindow *window;

        void processInput(GLFWwindow *window);
        void framebuffer_size_callback(GLFWwindow *window, int width, int height);
        void mouse_callback(GLFWwindow *window, double xpos, double ypos);
        void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
        void init();
    }
}

#endif