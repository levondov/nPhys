#include "Window.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h> // Include GLFW for window management
#include <iostream>
#include <cmath> // For sin and cos

Window::Window(int width, int height, const char* title)
    : window(nullptr), width(width), height(height), title(title) {}

Window::~Window() 
{
    if (window) 
    {
        glfwDestroyWindow(window);
    }
    glfwTerminate();
}

bool Window::initialize() 
{
    if (!glfwInit()) 
    {
        std::cerr << "Failed to initialize GLFW\n";
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

    window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!window) 
    {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) 
    {
        std::cerr << "Failed to initialize GLAD\n";
        return false;
    }

    return true;
}

void Window::swapBuffers() 
{
    glfwSwapBuffers(window);
}

bool Window::shouldClose() const 
{
    return glfwWindowShouldClose(window);
}

void Window::pollEvents() 
{
    glfwPollEvents();
}

void Window::drawCircle(float x, float y, float radius, int segments) 
{
    setupCircle(radius, segments);

    glBindVertexArray(circleVAO);

    // Apply simple transform (x, y)
    glPushMatrix();
    glTranslatef(x, y, 0.0f);

    glDrawArrays(GL_TRIANGLE_FAN, 0, circleSegments + 2);

    glPopMatrix();
}

void Window::setupCircle(float radius, int segments) 
{
    if (circleVAO != 0 && circleSegments == segments) return;  // Already set up

    // Clean up previous buffers if needed
    if (circleVAO != 0) {
        glDeleteVertexArrays(1, &circleVAO);
        glDeleteBuffers(1, &circleVBO);
    }

    std::vector<float> vertices;
    vertices.push_back(0.0f); // center x
    vertices.push_back(0.0f); // center y

    for (int i = 0; i <= segments; ++i) {
        float angle = 2.0f * M_PI * i / segments;
        vertices.push_back(radius * cos(angle));
        vertices.push_back(radius * sin(angle));
    }

    circleSegments = segments;

    glGenVertexArrays(1, &circleVAO);
    glGenBuffers(1, &circleVBO);

    glBindVertexArray(circleVAO);
    glBindBuffer(GL_ARRAY_BUFFER, circleVBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}
