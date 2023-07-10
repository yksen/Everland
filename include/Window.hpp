#pragma once

#include "Core.hpp"
#include "Camera.hpp"
#include "Player.hpp"
#include "Shader.hpp"
#include "World.hpp"

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
