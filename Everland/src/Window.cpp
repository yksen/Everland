#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Block.h"
#include "Camera.h"
#include "Shader.h"
#include "World.h"

#include <iostream>
#include <random>

namespace Everland
{
    namespace Window
    {
        GLFWwindow *window;

        std::mt19937 mt(time(NULL));

        float cubeVertices[] = {
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

            -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
            -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
            -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

            0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f};

        // Time
        float deltaTime = 0.0f;
        float lastFrame = 0.0f;

        // Settings
        const unsigned int SCR_WIDTH = 1280;
        const unsigned int SCR_HEIGHT = 720;

        // Camera
        Camera camera(glm::vec3(0.0f, 0.0f, 0.0f));
        float lastX = SCR_WIDTH / 2.0f;
        float lastY = SCR_HEIGHT / 2.0f;
        bool firstMouse = true;

        void processInput(GLFWwindow *window)
        {
            if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
                glfwSetWindowShouldClose(window, true);

            int sign = 1;
            if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
                sign = -1;

            if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
                World::generate();
            if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
                World::generateDecorations();

            if (glfwGetKey(window, GLFW_KEY_F1) == GLFW_PRESS)
            {
                World::scale += sign * 0.1f;
                World::generate();
            }
            if (glfwGetKey(window, GLFW_KEY_F2) == GLFW_PRESS)
            {
                World::persistance += sign * 0.1f;
                World::generate();
            }
            if (glfwGetKey(window, GLFW_KEY_F3) == GLFW_PRESS)
            {
                World::lacunarity += sign * 0.1f;
                World::generate();
            }

            if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS)
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            else
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

            if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
                camera.ProcessKeyboard(FORWARD, deltaTime);
            if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
                camera.ProcessKeyboard(BACKWARD, deltaTime);
            if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
                camera.ProcessKeyboard(LEFT, deltaTime);
            if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
                camera.ProcessKeyboard(RIGHT, deltaTime);
        }

        void framebuffer_size_callback(GLFWwindow *window, int width, int height)
        {
            glViewport(0, 0, width, height);
        }

        void mouse_callback(GLFWwindow *window, double xposIn, double yposIn)
        {
            float xpos = xposIn;
            float ypos = yposIn;

            if (firstMouse)
            {
                lastX = xpos;
                lastY = ypos;
                firstMouse = false;
            }

            float xoffset = xpos - lastX;
            float yoffset = lastY - ypos;

            lastX = xpos;
            lastY = ypos;

            camera.ProcessMouseMovement(xoffset, yoffset);
        }

        void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
        {
            camera.ProcessMouseScroll(yoffset);
        }

        void init()
        {
            float timeElapsed = 0;

            // GLFW Initialization
            glfwInit();
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

            // GLFW Window creation
            window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Everland", NULL, NULL);
            if (window == NULL)
            {
                std::cout << "Failed to create GLFW window" << std::endl;
                glfwTerminate();
                return;
            }
            glfwMakeContextCurrent(window);

            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
            glfwSetCursorPosCallback(window, mouse_callback);
            glfwSetScrollCallback(window, scroll_callback);

            // GLAD Load OpenGL Functions
            if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
            {
                std::cout << "Failed to initialize GLAD" << std::endl;
                return;
            }

            // Global OpenGL state
            glEnable(GL_DEPTH_TEST);

            // // Nanogui Initialization
            // nanogui::Screen *screen = new nanogui::Screen();
            // screen->initialize(window, true);

            // nanogui::FormHelper *gui = new nanogui::FormHelper(screen);
            // nanogui::ref<nanogui::Window> nanoguiWindow = gui->addWindow(nanogui::Vector2i(10, 10), "Settings");
            // gui->addGroup("Noise map parameters");
            // gui->addVariable("Scale", World::scale);
            // gui->addVariable("Octaves", World::octaves);
            // gui->addVariable("Persistance", World::persistance);
            // gui->addVariable("Lacunarity", World::lacunarity);

            // screen->setVisible(true);
            // screen->performLayout();
            // nanoguiWindow->center();

            // Shader Program
            Shader ourShader("../../assets/shaders/vShader.glsl", "../../assets/shaders/fShader.glsl");

            unsigned int VBO, VAO;
            glGenVertexArrays(1, &VAO);
            glGenBuffers(1, &VBO);
            glBindVertexArray(VAO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
            // Position attribute
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
            glEnableVertexAttribArray(0);
            // Texture coord attribute
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
            glEnableVertexAttribArray(1);

            /*
            // Create and load a texture
            unsigned int texture1;
            glGenTextures(1, &texture1);
            glBindTexture(GL_TEXTURE_2D, texture1);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            int width, height, nrChannels;
            stbi_set_flip_vertically_on_load(true);
            unsigned char *data = stbi_load("../../assets/images/grass.jpg", &width, &height, &nrChannels, 0);
            if (data)
            {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
                glGenerateMipmap(GL_TEXTURE_2D);
            }
            else
            {
                std::cout << "Failed to load texture" << std::endl;
            }
            stbi_image_free(data);

            ourShader.use();
            ourShader.setInt("texture1", 0);
            */

            // Render loop
            while (!glfwWindowShouldClose(Window::window))
            {
                // Time logic
                float currentFrame = glfwGetTime();
                deltaTime = currentFrame - lastFrame;
                lastFrame = currentFrame;
                timeElapsed += deltaTime;

                // Input
                processInput(window);

                // Clear the window
                glClearColor(0.57f, 0.77f, 0.84f, 1.0f);
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                /*
                // Bind texture to corresponding texture unit
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, texture1);
                */

                // Shader activation
                ourShader.use();

                // Pass projection matrix to shader
                glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 400.0f);
                ourShader.setMat4("projection", projection);

                // Camera transformation
                glm::mat4 view = camera.GetViewMatrix();
                ourShader.setMat4("view", view);

                // Render cubes
                glBindVertexArray(VAO);

                for (int x = 0; x < World::world.size(); ++x)
                    for (int z = 0; z < World::world[x].size(); ++z)
                        for (int y = 0; y < World::world[x][z].size(); ++y)
                        {
                            Block block = World::world[x][z][y];
                            if (block.type == BlockType::Air)
                                continue;

                            glm::vec3 position = {x, y, z};

                            glm::mat4 model = glm::mat4(1.0f);
                            model = glm::translate(model, glm::vec3(-World::worldSize / 2, 0, -World::worldSize / 2));
                            model = glm::translate(model, position);
                            ourShader.setMat4("model", model);
                            ourShader.setVec3("blockColor", block.color);

                            glDrawArrays(GL_TRIANGLES, 0, 36);
                        }

                // GLFW swap buffers and poll IO events
                glfwSwapBuffers(window);
                glfwPollEvents();
            }

            glDeleteVertexArrays(1, &VAO);
            glDeleteBuffers(1, &VBO);
        }
    }
}