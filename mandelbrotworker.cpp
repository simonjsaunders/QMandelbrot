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

#include "mandelbrotworker.h"
#include "colours.h"
#include <QTime>
#include <QRectF>

MandelbrotWorker::MandelbrotWorker(const std::shared_ptr<int>& jobId) : currentJobId_(jobId)
{
}

MandelbrotWorker::~MandelbrotWorker()
{
}

void MandelbrotWorker::draw(int id, int width, int height, int iterations, double scale, const QRectF& rect)
{
    QTime t;
    t.start();
    drawMandelbrotSet(id, width, height, iterations, scale, rect);
    emit done(id, t.elapsed());
}

void MandelbrotWorker::drawMandelbrotSet(int id, int width, int height, int iterations, double scale, const QRectF& qrect)
{
    double minX = qrect.x();
    double minY = qrect.y();
    for (int x = 0; x < width; x++)
    {
        if (id != *currentJobId_)
            return;
        QVector<unsigned int> pixels(height);
        double re = x/scale + minX;
        for (int y = 0; y < height; y++)
        {
            if (id != *currentJobId_)
                return;
            double zx, zy, newzx, newzy, im, zx2, zy2;
            bool inSet = true;
            int i;
            im = (height - y)/scale + minY;
            zy = im;
            zx = re;

            for (i = 0; i < iterations; i++)
            {
                zx2 = zx * zx;
                zy2 = zy * zy;
                if (zx2 + zy2 > 4)
                {
                    inSet = false;
                    break;
                }
                newzx = zx2 - zy2 + re;
                newzy = 2 * zx * zy + im;
                zx = newzx;
                zy = newzy;
            }
            pixels[y] = inSet ? 0 : colours[i % NUM_COLOURS];
        }
        emit drawLine(id, x, pixels);
    }
}
