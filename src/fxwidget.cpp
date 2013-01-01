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
 * @file   fxwidget.cpp
 * @author Rafael Palomar
 * @date   Thu Apr 8 18:10:07 2010
 * 
 * @brief  FXWidget Definition File
 * 
 * This file contains the definition of the FXWidget class
 * wich is composed of the constructor and the functions needed
 * to create sliders and notify possible changes of value of
 * these sliders.
 * 
 */

#include "fxwidget.h"

#include <QCheckBox>
#include <QGridLayout>
#include <QLabel>
#include <QSlider>
#include <QGroupBox>

/** 
 * @brief Constructor.
 *
 * This constructor creates and initializes the child widgets and 
 * makes the needed connections between signals and slots. Furthermore,
 * the constructor distributes the widgets through the interface.
 * 
 * @param parent the parent widget of the FXWidget.
 */
FXWidget::FXWidget(QWidget *parent):QWidget(parent){

	reflectionActivationCheckBox = new QCheckBox;
	fogActivationCheckBox = new QCheckBox;
	fogRedValueLabel = new QLabel("0");
	fogGreenValueLabel = new QLabel("0");
	fogBlueValueLabel = new QLabel("0");
	fogRedSlider = createColorSlider();
	fogGreenSlider = createColorSlider();
	fogBlueSlider = createColorSlider();
	fogStartValueLabel = new QLabel("0");
	fogEndValueLabel = new QLabel("0");
	fogStartSlider = new QSlider;
	fogEndSlider = new QSlider;
	fogStartSlider->setRange(0,500);
	fogStartSlider->setSingleStep(1);
	fogStartSlider->setValue(0);
	fogEndSlider->setRange(0,500);
	fogEndSlider->setSingleStep(1);
	fogEndSlider->setValue(0);	
	
	connect(reflectionActivationCheckBox, SIGNAL(clicked(bool)), 
			this, SIGNAL(setReflection(bool)));
	connect(fogActivationCheckBox, SIGNAL(clicked(bool)), 
			this, SIGNAL(setFog(bool)));
	connect(fogRedSlider, SIGNAL(valueChanged(int)),
			this, SLOT(updateRed(int)));
	connect(fogGreenSlider, SIGNAL(valueChanged(int)),
			this, SLOT(updateGreen(int)));
	connect(fogBlueSlider, SIGNAL(valueChanged(int)),
			this, SLOT(updateBlue(int)));
	connect(fogStartSlider, SIGNAL(valueChanged(int)),
			this, SLOT(updateStart(int)));
	connect(fogEndSlider, SIGNAL(valueChanged(int)),
			this, SLOT(updateEnd(int)));

	QGridLayout *fogLayout = new QGridLayout;
	fogLayout->addWidget(new QLabel("Enable"),0,0,1,2);
	fogLayout->addWidget(fogActivationCheckBox,0,2);
	fogLayout->addWidget(new QLabel("R"),1,0,Qt::AlignHCenter);
	fogLayout->addWidget(fogRedSlider,2,0,Qt::AlignHCenter);
	fogLayout->addWidget(fogRedValueLabel,3,0,Qt::AlignHCenter);
	fogLayout->addWidget(new QLabel("G"),1,1,Qt::AlignHCenter);
	fogLayout->addWidget(fogGreenSlider,2,1,Qt::AlignHCenter);
	fogLayout->addWidget(fogGreenValueLabel,3,1,Qt::AlignHCenter);
	fogLayout->addWidget(new QLabel("B"),1,2,Qt::AlignHCenter);
	fogLayout->addWidget(fogBlueSlider,2,2,Qt::AlignHCenter);
	fogLayout->addWidget(fogBlueValueLabel,3,2,Qt::AlignHCenter);
	fogLayout->addWidget(new QLabel("Start"),4,0,Qt::AlignCenter);
	fogLayout->addWidget(fogStartSlider,5,0,Qt::AlignCenter);
	fogLayout->addWidget(fogStartValueLabel,6,0,Qt::AlignCenter);
	fogLayout->addWidget(new QLabel("End"),4,2,Qt::AlignCenter);
	fogLayout->addWidget(fogEndSlider,5,2,Qt::AlignCenter);
	fogLayout->addWidget(fogEndValueLabel,6,2,Qt::AlignCenter);
	
	QGroupBox *fogGroupBox = new QGroupBox("Fog");
	fogGroupBox->setLayout(fogLayout);
	
	QGridLayout *mainLayout = new QGridLayout;
	mainLayout->addWidget(new QLabel("Reflection"),0,0);
	mainLayout->addWidget(reflectionActivationCheckBox,0,1);
	mainLayout->addWidget(fogGroupBox,1,0,1,2);

	setLayout(mainLayout);
}


/** 
 * @brief Create Color Slider.
 * 
 * This function creates a color slider with the following attributes:
 * <ul>
 * <li>Range: 0-255</li>
 * <li>Single step: 1</li>
 * <li>Initial value: 0</li>
 * </ul>
 * 
 * @return the new slider.
 */
QSlider *FXWidget::createColorSlider(){

	QSlider *slider = new QSlider;
	slider->setRange(0,255);
	slider->setSingleStep(1);
	slider->setValue(0);
	return slider;
}

/** 
 * @brief Update Red.
 *
 * This function updates the value of the red component of the fog. 
 *
 * @param value integer to update the value of the component.
 */
void FXWidget::updateRed(int value){

	fogRedValueLabel->setNum(value);
	emit fogRedChanged(value);
}

/** 
 * @brief Update Green.
 *
 * This function updates the value of the green component of the fog. 
 *
 * @param value integer to update the value of the component.
 */
void FXWidget::updateGreen(int value){

	fogGreenValueLabel->setNum(value);
	emit fogGreenChanged(value);
}

/** 
 * @brief Update Blue.
 *
 * This function updates the value of the blue component of the fog. 
 *
 * @param value integer to update the value of the component.
 */
void FXWidget::updateBlue(int value){

	fogBlueValueLabel->setNum(value);
	emit fogBlueChanged(value);
}

/** 
 * @brief Update Start.
 *
 * This function updates the value of the beginning of the fog. 
 *
 * @param value integer to update the value of the beginning.
 */
void FXWidget::updateStart(int value){
	
	fogStartValueLabel->setNum(value);
	emit fogStartChanged(value);
}

/** 
 * @brief Update end.
 *
 * This function updates the value of the end of the fog. 
 *
 * @param value integer to update the value of the end.
 */
void FXWidget::updateEnd(int value){
	
	fogEndValueLabel->setNum(value);
	emit fogEndChanged(value);
}
