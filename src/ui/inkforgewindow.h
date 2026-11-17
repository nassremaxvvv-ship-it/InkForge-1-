#pragma once

#include <QMainWindow>

class CanvasWidget;

class InkForgeWindow : public QMainWindow
{
public:
    explicit InkForgeWindow(QWidget *parent = nullptr);

private:
    CanvasWidget *canvasWidget;
};
