#include "Application.h"
#include "Window.h"

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