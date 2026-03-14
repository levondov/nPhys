#include "Engine.hpp"
#include <iostream>

#include "Window.hpp"
#include <QApplication>

#include "Integration.hpp"
#include "Dynamics.hpp"
#include "Collisions.hpp"
#include "EOMs.hpp"

Engine::Engine() : app(nullptr), window(nullptr)
{
}

Engine::~Engine() 
{
    shutdown();
}

bool Engine::initialize(simulation_settings _settings) 
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
    std::cout << "Engine reset\n";
    return true;
}

bool Engine::run() 
{
    Dynamics::calculate(shapes, settings);
    Collisions::walls(shapes, settings);
    EOMs::calculate(shapes);
    Integration::step(shapes, settings.dt);

    settings.t += settings.dt;
    settings.n_steps++;

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

bool Engine::add_shape(double x, double y, double mass, shape_type type, double radius, double e)
{
    return shapes.add(x, y, mass, type, radius, e);
}

std::vector<std::pair<double, double>> Engine::get_positions() const
{
    std::vector<std::pair<double, double>> positions;
    positions.reserve(shapes.count);
    for (size_t i = 0; i < shapes.count; i++)
    {
        positions.push_back({shapes.x[i], shapes.y[i]});
    }
    return positions;
}