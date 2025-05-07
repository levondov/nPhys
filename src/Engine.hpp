#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "object_types.hpp"
#include "Constants.hpp"
#include "EOMs.hpp"

class QApplication;
class Window;

class Engine 
{
    public:
        Engine();
        ~Engine();
        
        bool initialize(simulation_settings* _sim);
        bool run();
        bool shutdown();
        bool reset();

        bool addShape(shape* newShape);

    private:
        shape* shapes[constants::MAX_SHAPES];
        size_t shapeCount;

        simulation_settings* settings = nullptr;

        QApplication* app = nullptr;
        Window* window = nullptr;
};

#endif // ENGINE_HPP
