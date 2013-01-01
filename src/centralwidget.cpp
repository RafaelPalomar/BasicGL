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
 * @file   centralwidget.cpp
 * @author Rafael Palomar
 * @date   Thu Apr  8 17:53:32 2010
 * 
 * @brief  CentralWidget definition file.
 * 
 * This file contains the definition for the
 * CentralWidget class.
 *
 */

#include "centralwidget.h"

#include <QGridLayout>
#include <QTabWidget>

#include "glwidget.h"
#include "colorwidget.h"
#include "lightingwidget.h"
#include "texturewidget.h"
#include "fxwidget.h"

/** 

 * @brief Constructor.
 *
 * This constructor initializes all the elements of CentralWidget,
 * performs the connections needed between signals and slots,
 * makes a distribution the child widgets within the CentralWidget and
 * shows all these child widgets inside.
 * 
 * @param parent the parent widget for CentralWidget
 */
CentralWidget::CentralWidget(QWidget *parent):QWidget(parent){

	glWidget = new GLWidget;
	tabWidget = new QTabWidget;
	colorWidget = new ColorWidget;
	lightingWidget = new LightingWidget;
	textureWidget = new TextureWidget;
	fxWidget = new FXWidget;
	
	connect(colorWidget,SIGNAL(redChanged(int)),
			glWidget,SLOT(setCubeRedComponent(int)));

	connect(colorWidget,SIGNAL(greenChanged(int)),
			glWidget,SLOT(setCubeGreenComponent(int)));

	connect(colorWidget,SIGNAL(blueChanged(int)),
			glWidget,SLOT(setCubeBlueComponent(int)));

	connect(lightingWidget,SIGNAL(ambientLightRedChanged(int)),
			glWidget,SLOT(setAmbientLightRedComponent(int)));

	connect(lightingWidget,SIGNAL(ambientLightGreenChanged(int)),
			glWidget,SLOT(setAmbientLightGreenComponent(int)));

	connect(lightingWidget,SIGNAL(ambientLightBlueChanged(int)),
			glWidget,SLOT(setAmbientLightBlueComponent(int)));

	connect(lightingWidget,SIGNAL(diffuseLightRedChanged(int)),
			glWidget,SLOT(setDiffuseLightRedComponent(int)));

	connect(lightingWidget,SIGNAL(diffuseLightGreenChanged(int)),
			glWidget,SLOT(setDiffuseLightGreenComponent(int)));

	connect(lightingWidget,SIGNAL(diffuseLightBlueChanged(int)),
			glWidget,SLOT(setDiffuseLightBlueComponent(int)));

	connect(lightingWidget,SIGNAL(setLighting(bool)),
			glWidget,SLOT(setLighting(bool)));

	connect(textureWidget,SIGNAL(enableCubeTexture(const QString&)),
			glWidget, SLOT(enableCubeTexture(const QString&)));

	connect(textureWidget,SIGNAL(disableCubeTexture()),
			glWidget, SLOT(disableCubeTexture()));

	connect(textureWidget,SIGNAL(enableFloorTexture(const QString&)),
			glWidget, SLOT(enableFloorTexture(const QString&)));

	connect(textureWidget,SIGNAL(disableFloorTexture()),
			glWidget, SLOT(disableFloorTexture()));

	connect(glWidget, SIGNAL(cubeTexturingFailed()),
			textureWidget, SLOT(uncheckCubeTexActivationCheckBox()));

	connect(glWidget, SIGNAL(floorTexturingFailed()),
			textureWidget, SLOT(uncheckFloorTexActivationCheckBox()));

	connect(fxWidget, SIGNAL(setReflection(bool)),
			glWidget, SLOT(setReflection(bool)));

	connect(fxWidget, SIGNAL(setFog(bool)),
			glWidget, SLOT(setFog(bool)));

	connect(fxWidget, SIGNAL(fogRedChanged(int)),
			glWidget, SLOT(setFogRedComponent(int)));

	connect(fxWidget, SIGNAL(fogGreenChanged(int)),
			glWidget, SLOT(setFogGreenComponent(int)));

	connect(fxWidget, SIGNAL(fogBlueChanged(int)),
			glWidget, SLOT(setFogBlueComponent(int)));

	connect(fxWidget, SIGNAL(fogStartChanged(int)),
			glWidget, SLOT(setFogStart(int)));

	connect(fxWidget, SIGNAL(fogEndChanged(int)),
			glWidget, SLOT(setFogEnd(int)));
		
	tabWidget->addTab(colorWidget, "Color");
	tabWidget->addTab(lightingWidget, "Lighting");
	tabWidget->addTab(fxWidget, "FX");

	tabWidget->setSizePolicy(QSizePolicy(QSizePolicy::Minimum,
										 QSizePolicy::Minimum));


	QGridLayout *layout = new QGridLayout;
	layout->addWidget(glWidget,0,0);
	layout->addWidget(tabWidget,0,1);
	layout->addWidget(textureWidget,1,0,1,2);
		
	setLayout(layout);
}

