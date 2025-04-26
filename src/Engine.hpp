#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "Window.hpp"
#include "models/model_types.hpp"

constexpr size_t MAX_SHAPES = 100; // Define a maximum number of shapes

class Engine 
{
    public:
        Engine();
        ~Engine();
    
        bool initialize();
        bool run();
        bool shutdown();
        bool reset();

        bool addShape(shape* newShape);

    private:
        Window* window;
        
        shape* shapes[MAX_SHAPES]; // Fixed-size array
        size_t shapeCount;         // Keep track of the number of shapes

};

#endif // MYCLASS_HPP