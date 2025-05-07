#include "Engine.hpp"
#include <iostream>

#include "Window.hpp"
#include <QApplication>

Engine::Engine() : shapeCount(0), settings(nullptr), app(nullptr), window(nullptr) 
{
    for (size_t i = 0; i < constants::MAX_SHAPES; ++i) 
    {
        shapes[i] = nullptr; // Initialize all elements to nullptr
    }
}

Engine::~Engine() 
{
    shutdown();
}

bool Engine::initialize(simulation_settings* _settings) 
{
    settings = _settings;
    // int argc = 0;
    // app = new QApplication(argc, nullptr);

    // window = new Window(600, 400, "nPhys Qt View");
    // window->show();

    std::cout << "Engine initialized\n";
    return true;
}

bool Engine::reset() 
{
    shapeCount = 0; // Reset the shape count
    std::cout << "Engine reset\n";
    return true;
}

bool Engine::run() 
{  
    EOMs::calcDynamics(shapes, settings);
    EOMs::calcEOMs(shapes);

    settings->t += settings->dt;
    settings->n_steps++;

    // if (app && window) 
    // {
    //     return app->exec() == 0;
    // }
    return true;
}

bool Engine::shutdown() 
{
    // if (window) 
    // {
    //     delete window;
    //     window = nullptr;
    // }
    // if (app) 
    // {
    //     delete app;
    //     app = nullptr;
    // }
    std::cout << "Engine shutdown\n";
    return true;
}

bool Engine::addShape(shape* newShape) 
{
    if (shapeCount < constants::MAX_SHAPES && newShape) 
    {
        newShape->st.x.dt = settings->dt; // Set the time step for the new shape
        newShape->st.y.dt = settings->dt;
        newShape->st.theta.dt = settings->dt;
        shapes[shapeCount++] = newShape; // Add the shape and increment the count

        std::cout << "Shape (" << newShape->name << ") added. Total shapes: " << shapeCount << "\n";
        return true;
    }
    return false; // Return false if the array is full or newShape is null
}
