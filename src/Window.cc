#include "Window.hpp"

Window::Window(int width, int height, const QString& title)
    : scene(new QGraphicsScene(this)),
      view(new QGraphicsView(scene, this)) 
{

    setWindowTitle(title);
    resize(width, height);

    // Set the view as the central widget
    setCentralWidget(view);

    // Optional: configure scene/view
    scene->setSceneRect(0, 0, width, height);  // Logical scene size
    view->setRenderHint(QPainter::Antialiasing);  // Smooth rendering
}

Window::~Window() 
{
    // Qt handles cleanup of scene and view automatically (parent-child relationship)
}
