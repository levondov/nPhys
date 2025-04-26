#include "Engine.hpp"
#include <iostream>

Engine::Engine() : window(nullptr) {}

Engine::~Engine() 
{
    shutdown();
}

bool Engine::initialize() 
{
    window = new Window(800, 600, "nPhys Engine");
    if (!window->initialize()) 
    {
        delete window;
        window = nullptr;
        return false;
    }

    std::cout << "Engine initialized\n";
    return true;
}

bool Engine::reset() 
{
    if (window) 
    {
        delete window;
        window = nullptr;
    }

    shapeCount = 0; // Reset the shape count
    std::cout << "Engine reset\n";
    return true;
}

bool Engine::run() 
{
    if (!window) return false;

    while (!window->shouldClose()) 
    {
        for(shape* s : shapes) 
        {
            if (s) 
            {
                window->drawCircle(s->st.x.x, s->st.y.x, s->dyn.size1, 10);
            }
        }

        window->swapBuffers();
        window->pollEvents();
    }

    return true;
}

bool Engine::shutdown() 
{
    if (window) 
    {
        delete window;
        window = nullptr;
    }

    std::cout << "Engine shutdown\n";
    return true;
}

bool Engine::addShape(shape* newShape) 
{
    if (shapeCount < MAX_SHAPES && newShape) 
    {
        newShape->dyn.mass = 1.0; // Initialize mass to 1.0
        shapes[shapeCount++] = newShape; // Add the shape and increment the count
        std::cout << "Shape added. Total shapes: " << shapeCount << "\n";
        std::cout << "Shape name: " << newShape->name << "\n";
        return true;
    }
    return false; // Return false if the array is full or newShape is null
}
