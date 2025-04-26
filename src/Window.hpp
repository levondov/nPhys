#ifndef WINDOW_HPP
#define WINDOW_HPP

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

class Window 
{
public:
    Window(int width, int height, const char* title);
    ~Window();

    bool initialize();
    void swapBuffers();
    bool shouldClose() const;
    void pollEvents();

    void drawCircle(float x, float y, float radius, int segments = 36);
    void setupCircle(float radius, int segments = 36);

private:
    GLFWwindow* window;
    int width, height;
    const char* title;

    unsigned int circleVAO = 0;
    unsigned int circleVBO = 0;
    int circleSegments = 0;
};

#endif // WINDOW_HPP
