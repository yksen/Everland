#include "Application.hpp"

namespace Everland
{
    namespace Application
    {
        void init()
        {
            Window::init();

            // GLFW Termination
            glfwTerminate();
            return;
        }
    }
}