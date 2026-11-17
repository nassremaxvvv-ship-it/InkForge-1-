#include "inkforgewindow.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QMainWindow>

InkForgeWindow::InkForgeWindow(QWidget *parent)
    : QMainWindow(parent),
      canvasWidget(nullptr)
{
    setWindowTitle("InkForge");
    resize(900, 600);

    QWidget *central = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(central);

    QLabel *title = new QLabel("InkForge", central);
    title->setAlignment(Qt::AlignCenter);

    QLabel *message = new QLabel(
        "Drawing workspace",
        central
    );
    message->setAlignment(Qt::AlignCenter);

    central->setStyleSheet(
        "background-color: #181818;"
        "color: #ffffff;"
    );

    title->setStyleSheet(
        "font-size: 28px;"
        "font-weight: bold;"
    );

    message->setStyleSheet(
        "font-size: 16px;"
        "color: #aaaaaa;"
    );

    layout->addStretch();
    layout->addWidget(title);
    layout->addWidget(message);
    layout->addStretch();

    setCentralWidget(central);
}
