#pragma once

#include <QWidget>
#include <QPointF>
#include <QImage>
#include <QColor>
#include <QVector>

class CanvasWidget : public QWidget
{
public:
    explicit CanvasWidget(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    QImage canvas;
    QVector<QPointF> currentStroke;
    QColor brushColor;
    qreal brushSize;
    bool drawing;
};
