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

#ifndef MANDELBROTTHREAD_H
#define MANDELBROTTHREAD_H

#include <QObject>
#include <QVector>
#include <memory>

class MandelbrotWorker : public QObject {
    Q_OBJECT
public:
    MandelbrotWorker(const std::shared_ptr<int>&);
    ~MandelbrotWorker();
public slots:
    void draw(int, int, int, int, double, const QRectF&);
signals:
    void drawLine(int, int, const QVector<unsigned int>&);
    void done(int, int);

private:
    void drawMandelbrotSet(int id, int width, int height, int iterations,
                           double scale, const QRectF&);
    std::shared_ptr<int> currentJobId_;
};

#endif // MANDELBROTTHREAD_H
