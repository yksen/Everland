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
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
            0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
            0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
            0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,

            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
            0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
            0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
            0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,

            -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f,
            -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f,
            -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f,

            0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,

            -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
            0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,

            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f};

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
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
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

            // Shader Program
            Shader ourShader("../../assets/shaders/vShader.glsl", "../../assets/shaders/fShader.glsl");

            unsigned int VBO, cubeVAO;
            glGenVertexArrays(1, &cubeVAO);
            glGenBuffers(1, &VBO);

            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

            glBindVertexArray(cubeVAO);

            // Position attribute
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
            glEnableVertexAttribArray(0);
            // Normal attribute
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
            glEnableVertexAttribArray(1);

            glm::vec3 lightPos(0.0f, 0.0f, 10.0f);

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

                // Shader activation
                ourShader.use();

                ourShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
                ourShader.setVec3("lightPos", lightPos);

                // Pass projection matrix to shader
                glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 400.0f);
                ourShader.setMat4("projection", projection);

                // Camera transformation
                glm::mat4 view = camera.GetViewMatrix();
                ourShader.setMat4("view", view);

                // Render cubes
                glBindVertexArray(cubeVAO);

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
                            ourShader.setVec3("objectColor", block.color);
                            ourShader.setMat4("model", model);

                            glBindVertexArray(cubeVAO);
                            glDrawArrays(GL_TRIANGLES, 0, 36);
                        }

                // GLFW swap buffers and poll IO events
                glfwSwapBuffers(window);
                glfwPollEvents();
            }

            glDeleteVertexArrays(1, &cubeVAO);
            glDeleteBuffers(1, &VBO);
        }
    }
}