/*
 * Copyright (c) 2020 Simon J. Saunders
 *
 * This file is part of QMandelbrot.
 *
 * QMandelbrot is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * QMandelbrot is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with QMandelbrot.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef MANDELBROTCANVAS_H
#define MANDELBROTCANVAS_H

#include <QWidget>
#include <QThread>
#include <memory>
#include <stack>

class MandelbrotCanvas : public QWidget
{
    Q_OBJECT
public:
    explicit MandelbrotCanvas(QWidget *parent = nullptr);
    ~MandelbrotCanvas();
    void setIterations(int);
    int getIterations() const;
    void redraw();
    void revert();
    bool save(const QString&);
signals:
    void setValues(double, const QRectF&);
    void setTime(int);
    void startDrawing(int, int, int, int, double, const QRectF&);

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    void createPixmap(int, int);
    void drawLine(int, int, const QVector<unsigned int>&);
    void jobDone(int, int);
    void recomputeScale();
    void eraseRect();
    void drawRect();
    void backup(const QRect&);
    QRect mouseRect() const;

    int iterations_;
    double scale_;
    std::unique_ptr<QImage> image_;
    std::unique_ptr<QPixmap> tempPixmap_;
    std::shared_ptr<int> jobId_;
    std::stack<QRectF> stack_;
    QRectF rect_;
    bool mouseDown_;
    QPoint startPoint_;
    QPoint endPoint_;
    QThread workerThread_;
    bool redrawNeeded_;
};

#endif // MANDELBROTCANVAS_H
