#ifndef WINDOW_H
#define WINDOW_H

#include "Core.h"

#include "Camera.h"
#include "Player.h"
#include "Shader.h"
#include "World.h"

namespace Everland
{
    namespace Window
    {
        extern GLFWwindow *window;

        void init();

        void processInput(GLFWwindow *window);
        void framebuffer_size_callback(GLFWwindow *window, int width, int height);
        void mouse_callback(GLFWwindow *window, double xpos, double ypos);
        void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
    }
}

#endif