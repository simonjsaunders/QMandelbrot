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

#include "mandelbrotwidget.h"
#include "mandelbrotcanvas.h"
#include "version.h"
#include <QtWidgets>

MandelbrotWidget::MandelbrotWidget(QWidget *parent)
    : QWidget(parent)
{
    iterationsField_ = new QLineEdit();

    scaleField_ = new QLineEdit();
    scaleField_->setReadOnly(true);

    minXField_ = new QLineEdit();
    minXField_->setReadOnly(true);

    maxXField_ = new QLineEdit();
    maxXField_->setReadOnly(true);

    minYField_ = new QLineEdit();
    minYField_->setReadOnly(true);

    maxYField_ = new QLineEdit();
    maxYField_->setReadOnly(true);

    timeField_ = new QLineEdit();
    timeField_->setReadOnly(true);

    QFormLayout* formLayout = new QFormLayout();
    formLayout->addRow(tr("Iterations:"), iterationsField_);
    formLayout->addRow(tr("Scale:"), scaleField_);
    formLayout->addRow(tr("Min X:"), minXField_);
    formLayout->addRow(tr("Max X:"), maxXField_);
    formLayout->addRow(tr("Min Y:"), minYField_);
    formLayout->addRow(tr("Max Y:"), maxYField_);
    formLayout->addRow(tr("Time:"), timeField_);

    QPushButton* redrawButton = new QPushButton(tr("Redraw"));
    connect(redrawButton, SIGNAL(clicked()), this, SLOT(redraw()));

    QPushButton* revertButton = new QPushButton(tr("Revert"));
    connect(revertButton, SIGNAL(clicked()), this, SLOT(revert()));

    QPushButton* quitButton = new QPushButton(tr("Quit"));
    connect(quitButton, SIGNAL(clicked()), this, SLOT(quit()));

    QPushButton* saveButton = new QPushButton(tr("Save Image..."));
    connect(saveButton, SIGNAL(clicked()), this, SLOT(save()));

    QVBoxLayout* controlPanelLayout = new QVBoxLayout();
    controlPanelLayout->addLayout(formLayout);
    controlPanelLayout->addWidget(redrawButton);
    controlPanelLayout->addWidget(revertButton);
    controlPanelLayout->addWidget(saveButton);
    controlPanelLayout->addWidget(quitButton);
    controlPanelLayout->addStretch();
    controlPanelLayout->addWidget(new QLabel(aboutText()));

    QHBoxLayout* mainLayout = new QHBoxLayout();
    mainLayout->setContentsMargins(12, 12, 12, 12);
    mainLayout->addLayout(controlPanelLayout);

    QFrame* canvasFrame = new QFrame();
    canvas_ = new MandelbrotCanvas(canvasFrame);
    QHBoxLayout* frameLayout = new QHBoxLayout();
    canvasFrame->setFrameStyle(QFrame::Panel|QFrame::Sunken);
    frameLayout->setContentsMargins(0, 0, 0, 0);
    frameLayout->addWidget(canvas_, 1);
    canvasFrame->setLayout(frameLayout);
    mainLayout->addWidget(canvasFrame, 1);

    setIterations(canvas_->getIterations());
    connect(canvas_, &MandelbrotCanvas::setValues, this, &MandelbrotWidget::setValues);
    connect(canvas_, &MandelbrotCanvas::setTime, this, &MandelbrotWidget::setTime);
    connect(iterationsField_, SIGNAL(textEdited(const QString&)), this, SLOT(iterationsEdited(const QString&)));

    setLayout(mainLayout);
    setWindowTitle(tr("QMandelbrot"));
    readSettings();
}

MandelbrotWidget::~MandelbrotWidget()
{
}

QString MandelbrotWidget::aboutText()
{
    return tr("<p>QMandelbrot Version %1<br>Copyright &copy; %2<br>Simon J. Saunders</p>")
            .arg(QStringLiteral(VERSION_NUMBER), QStringLiteral(COPYRIGHT_YEAR));
}

void MandelbrotWidget::readSettings()
{
    QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());
    const QByteArray geometry = settings.value("geometry", QByteArray()).toByteArray();
    if (!geometry.isEmpty())
        restoreGeometry(geometry);
    else
        resize(1000, 800);
}

void MandelbrotWidget::writeSettings()
{
    QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());
    settings.setValue("geometry", saveGeometry());
}

void MandelbrotWidget::closeEvent(QCloseEvent* event)
{
    writeSettings();
}

void MandelbrotWidget::redraw()
{
    canvas_->redraw();
}

void MandelbrotWidget::revert()
{
    canvas_->revert();
}

void MandelbrotWidget::quit()
{
    QCoreApplication::quit();
}

void MandelbrotWidget::save()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Image"), "", tr("PNG Files (*.png)"));
    if (fileName.isEmpty())
        return;
    if (!canvas_->save(fileName))
        QMessageBox::critical(this, tr("Error"), tr("Save Image failed."));
}

void MandelbrotWidget::setTime(int mseconds)
{
    QString str;
    str.setNum(mseconds/1000.0, 'f', 3);
    timeField_->setText(str);
}

void MandelbrotWidget::setIterations(int n)
{
    QString str;
    str.setNum(n);
    iterationsField_->setText(str);
}

void MandelbrotWidget::iterationsEdited(const QString& text)
{
    // TODO: display error message if text is not a positive integer
    canvas_->setIterations(text.toInt());
}

void MandelbrotWidget::setValues(double scale, const QRectF& rect)
{
    QString str;
    str.setNum(scale);
    scaleField_->setText(str);
    str.setNum(rect.left());
    minXField_->setText(str);
    str.setNum(rect.top());
    minYField_->setText(str);
    str.setNum(rect.right());
    maxXField_->setText(str);
    str.setNum(rect.bottom());
    maxYField_->setText(str);
}
