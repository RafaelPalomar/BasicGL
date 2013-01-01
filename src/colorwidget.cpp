/*************************************************************************
  Copyright (c) 2010 Rafael Palomar
  
  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.
  
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY;
  without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  
  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.

*************************************************************************/

/**
 * @file   colorwidget.cpp
 * @author Rafael Palomar
 * @date   Thu Apr  8 18:02:10 2010
 * 
 * @brief  ColorWidget definition file.
 * 
 * This file contains the ColorWidget class definition which
 * is composed of the constructor, a function to create sliders and
 * functions to notify the change of values in the sliders.
 * 
 */

#include "colorwidget.h"

#include <QLabel>
#include <QSlider>
#include <QGridLayout>

/** 
 * @brief Constructor.
 *
 * This constructor initializes the child widgets of ColorWidget,
 * performs the connections needed between signals and slots and
 * makes the distribution of the child widgets in the interface.
 * 
 * @param parent 
 */
ColorWidget::ColorWidget(QWidget *parent):QWidget(parent){

	redValueLabel = new QLabel("0");
	greenValueLabel = new QLabel("0");
	blueValueLabel = new QLabel("0");
	redSlider = createSlider();
	greenSlider = createSlider();
	blueSlider = createSlider();
	
	connect(redSlider,SIGNAL(valueChanged(int)),this,SLOT(updateRed(int)));
	connect(greenSlider,SIGNAL(valueChanged(int)),this,SLOT(updateGreen(int)));
	connect(blueSlider,SIGNAL(valueChanged(int)),this,SLOT(updateBlue(int)));

	QGridLayout *layout = new QGridLayout;
	layout->addWidget(new QLabel("R"),0,0,Qt::AlignHCenter);
	layout->addWidget(redSlider,1,0,Qt::AlignHCenter);
	layout->addWidget(redValueLabel,2,0,Qt::AlignHCenter);
	layout->addWidget(new QLabel("G"),0,1,Qt::AlignHCenter);
	layout->addWidget(greenSlider,1,1,Qt::AlignHCenter);
	layout->addWidget(greenValueLabel,2,1,Qt::AlignHCenter);
	layout->addWidget(new QLabel("B"),0,2,Qt::AlignHCenter);
	layout->addWidget(blueSlider,1,2,1,1,Qt::AlignHCenter);
	layout->addWidget(blueValueLabel,2,2,Qt::AlignHCenter);

	setLayout(layout);
}

/** 
 * @brief Create Slider.
 * 
 * This function creates a new slider with the following attributes:
 * <ul>
 * <li>Range: 0-255</li>
 * <li>Single step: 1</li>
 * <li>Initial value: 0</li>
 * 
 * @return the new slider.
 */
QSlider *ColorWidget::createSlider(){

	QSlider *slider = new QSlider;
	slider->setRange(0,255);
	slider->setSingleStep(1);
	slider->setValue(0);
	return slider;
}

/** 
 * @brief Update Red Value
 * 
 * @param value integer of the new red value.
 */
void ColorWidget::updateRed(int value){

	redValueLabel->setNum(value);
	emit redChanged(value);
}

/** 
 * @brief Update Green Value
 * 
 * @param value integer of the new green value.
 */
void ColorWidget::updateGreen(int value){

	greenValueLabel->setNum(value);
	emit greenChanged(value);
}

/** 
 * @brief Update Blue Value
 * 
 * @param value integer of the new blue value.
 */
void ColorWidget::updateBlue(int value){

	blueValueLabel->setNum(value);
	emit blueChanged(value);
}
