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

#ifndef MANDELBROTWIDGET_H
#define MANDELBROTWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QLineEdit;
QT_END_NAMESPACE

class MandelbrotCanvas;

class MandelbrotWidget : public QWidget {
    Q_OBJECT

public:
    MandelbrotWidget(QWidget* parent = nullptr);
    ~MandelbrotWidget();

public slots:
    void redraw();
    void revert();
    void quit();
    void save();
    void setValues(double, const QRectF&);
    void setTime(int);
    void iterationsEdited(const QString&);
    void iterationsChanged();

protected:
    void closeEvent(QCloseEvent*) override;

private:
    void setIterations(int);
    void readSettings();
    void writeSettings();
    QString aboutText();
    QLineEdit* iterationsField_;
    QLineEdit* scaleField_;
    QLineEdit* minXField_;
    QLineEdit* maxXField_;
    QLineEdit* minYField_;
    QLineEdit* maxYField_;
    QLineEdit* timeField_;
    MandelbrotCanvas* canvas_;
};

#endif // MANDELBROTWIDGET_H
