#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>

class Window : public QMainWindow 
{
    Q_OBJECT

    public:
        Window(int width, int height, const QString& title);
        ~Window();

    private:
        QGraphicsScene* scene;
        QGraphicsView* view;
};

#endif // WINDOW_HPP