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
 * @file   lightingwidget.cpp
 * @author Rafael Palomar 
 * @date   Sun Apr 25 18:31:43 2010
 * 
 * @brief  LightingWidget.
 *
 * This file contains the implementation for the
 * class LightingWidget.
 * 
 */

#include "lightingwidget.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QGroupBox>
#include <QCheckBox>
#include <QSlider>


/** 
 * @brief Default constructor.
 *
 * Creates and initializates all the inner widgets for the
 * the ligthing widget, performs the needed connections between
 * signals and slots and finally makes the layout of the
 * child widgets.
 * 
 * @param parent the parent of the LigthingWidget.
 */
LightingWidget::LightingWidget(QWidget *parent):QWidget(parent){
	
	enableLightingCheckBox = new QCheckBox;
	ambientRedSlider = createSlider();
	ambientGreenSlider = createSlider();
	ambientBlueSlider = createSlider();
	diffuseRedSlider = createSlider();
	diffuseGreenSlider = createSlider();
	diffuseBlueSlider = createSlider();	
	ambientRedValueLabel = new QLabel("0");
	ambientGreenValueLabel = new QLabel("0");
	ambientBlueValueLabel = new QLabel("0");
	diffuseRedValueLabel = new QLabel("0");
	diffuseGreenValueLabel = new QLabel("0");
	diffuseBlueValueLabel = new QLabel("0");	

	connect(enableLightingCheckBox,SIGNAL(clicked(bool)),
			this,SIGNAL(setLighting(bool)));

	connect(ambientRedSlider,SIGNAL(valueChanged(int)),
			this,SLOT(ambientLightUpdateRed(int)));

	connect(ambientGreenSlider,SIGNAL(valueChanged(int)),
			this,SLOT(ambientLightUpdateGreen(int)));

	connect(ambientBlueSlider,SIGNAL(valueChanged(int)),
			this,SLOT(ambientLightUpdateBlue(int)));

	connect(diffuseRedSlider,SIGNAL(valueChanged(int)),
			this,SLOT(diffuseLightUpdateRed(int)));

	connect(diffuseGreenSlider,SIGNAL(valueChanged(int)),
			this,SLOT(diffuseLightUpdateGreen(int)));

	connect(diffuseBlueSlider,SIGNAL(valueChanged(int)),
			this,SLOT(diffuseLightUpdateBlue(int)));

	QHBoxLayout *enableLightingLayout = new QHBoxLayout;
	enableLightingLayout->addWidget(enableLightingCheckBox);
	enableLightingLayout->addWidget(new QLabel("Enable ligthing"));

	QGroupBox *enableLigthingGroupBox = new QGroupBox;
	enableLigthingGroupBox->setLayout(enableLightingLayout);

	QGridLayout *ambientLightLayout = new QGridLayout;
	ambientLightLayout->addWidget(new QLabel("R"),0,0,Qt::AlignHCenter);
	ambientLightLayout->addWidget(ambientRedSlider,1,0,Qt::AlignHCenter);
	ambientLightLayout->addWidget(ambientRedValueLabel,2,0,Qt::AlignHCenter);
	ambientLightLayout->addWidget(new QLabel("G"),0,1,Qt::AlignHCenter);
	ambientLightLayout->addWidget(ambientGreenSlider,1,1,Qt::AlignHCenter);
	ambientLightLayout->addWidget(ambientGreenValueLabel,2,1,Qt::AlignHCenter);
	ambientLightLayout->addWidget(new QLabel("B"),0,2,Qt::AlignHCenter);
	ambientLightLayout->addWidget(ambientBlueSlider,1,2,Qt::AlignHCenter);
	ambientLightLayout->addWidget(ambientBlueValueLabel,2,2,Qt::AlignHCenter);

	QGroupBox *ambientLightGroupBox = new QGroupBox("Ambient");
	ambientLightGroupBox->setLayout(ambientLightLayout);

	QGridLayout *diffuseLightLayout = new QGridLayout;
	diffuseLightLayout->addWidget(new QLabel("R"),0,0,Qt::AlignHCenter);
	diffuseLightLayout->addWidget(diffuseRedSlider,1,0,Qt::AlignHCenter);
	diffuseLightLayout->addWidget(diffuseRedValueLabel,2,0,Qt::AlignHCenter);
	diffuseLightLayout->addWidget(new QLabel("G"),0,1,Qt::AlignHCenter);
	diffuseLightLayout->addWidget(diffuseGreenSlider,1,1,Qt::AlignHCenter);
	diffuseLightLayout->addWidget(diffuseGreenValueLabel,2,1,Qt::AlignHCenter);
	diffuseLightLayout->addWidget(new QLabel("B"),0,2,Qt::AlignHCenter);
	diffuseLightLayout->addWidget(diffuseBlueSlider,1,2,Qt::AlignHCenter);
	diffuseLightLayout->addWidget(diffuseBlueValueLabel,2,2,Qt::AlignHCenter);

	QGroupBox *diffuseLightGroupBox = new QGroupBox("Diffuse");
	diffuseLightGroupBox->setLayout(diffuseLightLayout);


	QVBoxLayout *lightingLayout = new QVBoxLayout;
	lightingLayout->addWidget(enableLigthingGroupBox);
	lightingLayout->addWidget(ambientLightGroupBox);
	lightingLayout->addWidget(diffuseLightGroupBox);

	setLayout(lightingLayout);
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
QSlider *LightingWidget::createSlider(){

	QSlider *slider = new QSlider;
	slider->setRange(0,255);
	slider->setSingleStep(1);
	slider->setValue(0);
	return slider;
}

/** 
 * @brief Update red on ambient light.
 *
 * This function updates the value for the red component of the ambient light by
 * changin the value of the conrresponding tag and by emmiting a signal informing
 * about this update.
 * 
 * @param value integer for updating the value of ambient light.
 */
void LightingWidget::ambientLightUpdateRed(int value){

	ambientRedValueLabel->setNum(value);
	emit ambientLightRedChanged(value);
}

/** 
 * @brief Update green on ambient light.
 *
 * This function updates the value for the green component of the ambient light by
 * changin the value of the conrresponding tag and by emmiting a signal informing
 * about this update.
 * 
 * @param value integer for updating the value of ambient light.
 */
void LightingWidget::ambientLightUpdateGreen(int value){

	ambientGreenValueLabel->setNum(value);
	emit ambientLightGreenChanged(value);
}

/** 
 * @brief Update blue on ambient light.
 *
 * This function updates the value for the blue component of the ambient light by
 * changin the value of the conrresponding tag and by emmiting a signal informing
 * about this update.
 * 
 * @param value integer for updating the value of ambient light.
 */
void LightingWidget::ambientLightUpdateBlue(int value){

	ambientBlueValueLabel->setNum(value);
	emit ambientLightBlueChanged(value);
}

/** 
 * @brief Update red on ambient light.
 *
 * This function updates the value for the red component of the ambient light by
 * changin the value of the conrresponding tag and by emmiting a signal informing
 * about this update.
 * 
 * @param value integer for updating the value of diffuse light.
 */
void LightingWidget::diffuseLightUpdateRed(int value){

	diffuseRedValueLabel->setNum(value);
	emit diffuseLightRedChanged(value);
}

/** 
 * @brief Update green on diffuse light.
 *
 * This function updates the value for the green component of the diffuse light by
 * changin the value of the conrresponding tag and by emmiting a signal informing
 * about this update.
 * 
 * @param value integer for updating the value of diffuse light.
 */
void LightingWidget::diffuseLightUpdateGreen(int value){

	diffuseGreenValueLabel->setNum(value);
	emit diffuseLightGreenChanged(value);
}

/** 
 * @brief Update blue on diffuse light.
 *
 * This function updates the value for the blue component of the diffuse light by
 * changin the value of the conrresponding tag and by emmiting a signal informing
 * about this update.
 * 
 * @param value integer for updating the value of diffuse light.
 */
void LightingWidget::diffuseLightUpdateBlue(int value){

	diffuseBlueValueLabel->setNum(value);
	emit diffuseLightBlueChanged(value);
}
