#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "setting_types.hpp"
#include "object_types.hpp"
#include <vector>

class QApplication;
class Window;

class Engine 
{
    public:
        Engine();
        ~Engine();
        
        bool initialize(simulation_settings _settings);
        bool run();
        bool shutdown();
        bool reset();

        bool add_shape(double x, double y, double mass, shape_type type, double radius = 1.0, double e = 0.5);
        std::vector<std::pair<double, double>> get_positions() const;

    private:
        shape_pool shapes;

        simulation_settings settings;

        QApplication* app = nullptr;
        Window* window = nullptr;
};

#endif // ENGINE_HPP