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

#include "mandelbrotcanvas.h"
#include "mandelbrotworker.h"
#include <QtWidgets>

MandelbrotCanvas::MandelbrotCanvas(QWidget *parent) : QWidget(parent),
    iterations_(500), jobId_(std::make_shared<int>(0)), rect_(-2.0, -1.5, 3.0, 3.0),
    mouseDown_(false), redrawNeeded_(true)
{
    MandelbrotWorker* worker = new MandelbrotWorker(jobId_);
    worker->moveToThread(&workerThread_);
    connect(&workerThread_, &QThread::finished, worker, &QObject::deleteLater);
    connect(worker, &MandelbrotWorker::drawLine, this, &MandelbrotCanvas::drawLine);
    connect(worker, &MandelbrotWorker::done, this, &MandelbrotCanvas::jobDone);
    connect(this, &MandelbrotCanvas::startDrawing, worker, &MandelbrotWorker::draw);
    workerThread_.start();
}

MandelbrotCanvas::~MandelbrotCanvas()
{
    ++*jobId_; // tell worker to stop
    workerThread_.quit();
    workerThread_.wait();
}

void MandelbrotCanvas::recomputeScale()
{
    double xscale = width()/(rect_.width());
    double yscale = height()/(rect_.height());
    scale_ = std::min(xscale, yscale);
    rect_.setWidth(width()/scale_);
    rect_.setHeight(height()/scale_);
    redrawNeeded_ = true;
    emit setValues(scale_, rect_);
}

void MandelbrotCanvas::setIterations(int n)
{
    if (n != iterations_)
    {
        iterations_ = n;
        redrawNeeded_ = true;
    }
}

int MandelbrotCanvas::getIterations() const
{
    return iterations_;
}

void MandelbrotCanvas::paintEvent(QPaintEvent* event)
{
    if (image_.get() == 0)
        createPixmap(width(), height());
    QPainter painter(this);
    painter.drawImage(event->rect(), *image_.get(), event->rect());
}

void MandelbrotCanvas::resizeEvent(QResizeEvent* event)
{
    recomputeScale();
    const QSize& size = event->size();
    createPixmap(size.width(), size.height());
    redraw();
}

void MandelbrotCanvas::drawLine(int id, int x, const QVector<unsigned int>& pixels)
{
    if (id != *jobId_)
       return;
    int h = image_->height();
    for (int y = 0; y < h; ++y)
        image_->setPixel(x, y, pixels[y]);
    update(x, 0, 1, h);
}

void MandelbrotCanvas::jobDone(int id, int msec)
{
    if (id == *jobId_)
        emit setTime(msec);
}

void MandelbrotCanvas::createPixmap(int width, int height)
{
    image_.reset(new QImage(width, height, QImage::Format_RGB32));
    QPainter painter(image_.get());
    painter.fillRect(0, 0, image_->width(), image_->height(), QColor(0, 0, 0));
}

void MandelbrotCanvas::redraw()
{
    if (redrawNeeded_)
    {
        ++*jobId_;
        startDrawing(*jobId_, width(), height(), iterations_, scale_, rect_);
        redrawNeeded_ = false;
    }
}

void MandelbrotCanvas::mouseMoveEvent(QMouseEvent *event)
{
    if (mouseDown_)
    {
        if (endPoint_ != startPoint_)
            eraseRect();
        endPoint_ = event->pos();
        drawRect();
    }
}

void MandelbrotCanvas::mousePressEvent(QMouseEvent *event)
{
    if (!mouseDown_ && event->button() == Qt::LeftButton)
    {
        mouseDown_ = true;
        startPoint_ = event->pos();
        endPoint_ = startPoint_;
        tempPixmap_.reset(new QPixmap(100, 100));
    }
}

void MandelbrotCanvas::mouseReleaseEvent(QMouseEvent *event)
{
    if (mouseDown_ && event->button() == Qt::LeftButton)
    {
        mouseDown_ = false;
        if (endPoint_ != startPoint_)
            eraseRect();
        endPoint_ = event->pos();
        if (endPoint_ != startPoint_)
        {
            stack_.push(rect_);
            int x1 = std::min(startPoint_.x(), endPoint_.x());
            int y1 = std::min(startPoint_.y(), endPoint_.y());
            int x2 = std::max(startPoint_.x(), endPoint_.x());
            int y2 = std::max(startPoint_.y(), endPoint_.y());
            rect_.setRight(x2/scale_ + rect_.left());
            rect_.setLeft(x1/scale_ + rect_.left());
            rect_.setBottom((height() - y1)/scale_ + rect_.top());
            rect_.setTop((height() - y2)/scale_ + rect_.top());
            recomputeScale();
            redraw();
        }
    }
}

QRect MandelbrotCanvas::mouseRect() const
{
    int x1 = std::min(startPoint_.x(), endPoint_.x());
    int y1 = std::min(startPoint_.y(), endPoint_.y());
    int x2 = std::max(startPoint_.x(), endPoint_.x());
    int y2 = std::max(startPoint_.y(), endPoint_.y());
    QRect rect(x1, y1, x2 - x1, y2 - y1);
    return rect;
}

void MandelbrotCanvas::eraseRect()
{
    if (tempPixmap_.get() == nullptr)
        return;
    QRect target(mouseRect());
    target.adjust(-1, -1, 1, 1);
    QRect source(0, 0, target.width(), target.height());
    QPainter painter(image_.get());
    painter.drawPixmap(target, *tempPixmap_.get(), source);
    update(target);
}

void MandelbrotCanvas::drawRect()
{
    QRect rect(mouseRect());
    QRect outside(rect.adjusted(-1, -1, 1, 1));
    backup(outside);
    QPen pen(QColor(255, 255, 0));
    QPainter painter(image_.get());
    painter.setPen(pen);
    painter.drawRect(rect);
    update(outside);
}

void MandelbrotCanvas::backup(const QRect& rect)
{
    if (tempPixmap_.get() == nullptr
            || tempPixmap_->width() < rect.width()
            || tempPixmap_->height() < rect.height())
        tempPixmap_.reset(new QPixmap(rect.width() + 100, rect.height() + 100));
    QPainter painter(tempPixmap_.get());
    QRect target(0, 0, rect.width(), rect.height());
    painter.drawImage(target, *image_.get(), rect);
}

void MandelbrotCanvas::revert()
{
    if (stack_.empty())
        return;
    rect_ = stack_.top();
    stack_.pop();
    recomputeScale();
    redraw();
}

bool MandelbrotCanvas::save(const QString& fileName)
{
    return image_->save(fileName);
}
