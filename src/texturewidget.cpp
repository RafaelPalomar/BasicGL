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
 * @file   texturewidget.cpp
 * @author Rafael Palomar
 * @date   Sun Apr 25 19:33:00 2010
 * 
 * @brief  TextureWidget class definition.
 * 
 * This file contains the definition for the class TextureWidget. 
 * 
 */


#include "texturewidget.h"

#include <QLineEdit>
#include <QPushButton>
#include <QCheckBox>
#include <QGroupBox>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QFileDialog>
#include <QMessageBox>


/** 
 * @brief Default constructor.
 *
 * This constructor creates and initializes the inner widgets for the 
 * texture widget, performs the needed connections between signals and
 * slots and makes the layout of the child widgets.
 * 
 * @param parent the parent widget for TextureWidget
 */
TextureWidget::TextureWidget(QWidget *parent): QWidget(parent){

	cubeTexFileLineEdit = new QLineEdit();
	cubeTexBrowseButton = new QPushButton("Browse...");
	cubeTexActivationCheckBox = new QCheckBox();
 	floorTexFileLineEdit = new QLineEdit();
	floorTexBrowseButton = new QPushButton("Browse...");
	floorTexActivationCheckBox = new QCheckBox();

	connect(cubeTexBrowseButton, SIGNAL(clicked(bool)),
			this,SLOT(browseCubeTexture()));
	connect(cubeTexActivationCheckBox,SIGNAL(stateChanged(int)),
			this,SLOT(updateCubeTexture(int)));
	connect(cubeTexFileLineEdit, SIGNAL(textChanged(const QString&)),
			this, SLOT(uncheckCubeTexActivationCheckBox()));
	connect(floorTexBrowseButton, SIGNAL(clicked(bool)),
			this,SLOT(browseFloorTexture()));
	connect(floorTexActivationCheckBox,SIGNAL(stateChanged(int)),
			this,SLOT(updateFloorTexture(int)));
	connect(floorTexFileLineEdit, SIGNAL(textChanged(const QString&)),
			this, SLOT(uncheckFloorTexActivationCheckBox()));

	QGridLayout *textureLayout = new QGridLayout();
	textureLayout->addWidget(new QLabel("Cube"));
	textureLayout->addWidget(cubeTexFileLineEdit,0,1);
	textureLayout->addWidget(cubeTexBrowseButton,0,2);
	textureLayout->addWidget(cubeTexActivationCheckBox,0,3);
	textureLayout->addWidget(new QLabel("Floor"));
	textureLayout->addWidget(floorTexFileLineEdit,1,1);
	textureLayout->addWidget(floorTexBrowseButton,1,2);
	textureLayout->addWidget(floorTexActivationCheckBox,1,3);

	QGroupBox *textureGroup = new QGroupBox("Textures");
	textureGroup->setLayout(textureLayout);

	QVBoxLayout *mainLayout = new QVBoxLayout();
	mainLayout->addWidget(textureGroup);	

	setLayout(mainLayout);
}


/** 
 * @brief Browse cube texture.
 *
 * Creates and initializes a dialog for browsing and selecting and image for
 * texturing the cube. 
 * 
 */
void TextureWidget::browseCubeTexture(){
  
	QString imageFileName =  QFileDialog::getOpenFileName(this,
														  "Open Image", 
														  "./", 
														  "Image Files (*.png *.jpg *.bmp)");
	cubeTexFileLineEdit->setText(imageFileName);
}

/** 
 * @brief Browse floor texture.
 *
 * Creates and initializes a dialog for browsing and selecting and image for
 * texturing the floor. 
 * 
 */
void TextureWidget::browseFloorTexture(){
  
	QString imageFileName =  QFileDialog::getOpenFileName(this,
														  "Open Image", 
														  "./", 
														  "Image Files (*.png *.jpg *.bmp)");
	
	floorTexFileLineEdit->setText(imageFileName);
}

/** 
 * This function controls whether texture or untexture the cube regarding
 * the status of the checkbox control.
 * 
 * @param checkBoxStatus boolean indicating the status of the checkbox 
 * cube texturing control.
 */
void TextureWidget::updateCubeTexture(int checkBoxStatus){

	if(checkBoxStatus == Qt::Unchecked)
		emit(disableCubeTexture());
   
	else if(checkBoxStatus == Qt::Checked){
   
		if(cubeTexFileLineEdit->text().isEmpty()){
			QMessageBox::warning(this,
								 "No File Selected",
								 "You must to select a file");

			cubeTexActivationCheckBox->setCheckState(Qt::Unchecked);
		}
		else{
			emit(enableCubeTexture(cubeTexFileLineEdit->text()));
		}
	}
}

/** 
 * This function controls whether texture or untexture the floor regarding
 * the status of the checkbox control.
 * 
 * @param checkBoxStatus boolean indicating the status of the floor texturing 
 * checkbox control.
 */
void TextureWidget::updateFloorTexture(int checkBoxStatus){

	if(checkBoxStatus == Qt::Unchecked)
		emit(disableFloorTexture());
   
	else if(checkBoxStatus == Qt::Checked){
   
		if(floorTexFileLineEdit->text().isEmpty()){
			QMessageBox::warning(this,
								 "No File Selected",
								 "You must to select a file");

			floorTexActivationCheckBox->setCheckState(Qt::Unchecked);
		}
		else{
			emit(enableFloorTexture(floorTexFileLineEdit->text()));

		}
	}
}

/** 
 * @brief Uncheck cube texture activation checkbox.
 *
 * This function sets the cube texture activation checkbox unchecked. 
 *
 */
void TextureWidget::uncheckCubeTexActivationCheckBox(){

	cubeTexActivationCheckBox->setCheckState(Qt::Unchecked);

}

/** 
 * @brief Uncheck cube texture activation checkbox.
 *
 * This function sets the cube texture activation checkbox unchecked. 
 *
 */
void TextureWidget::uncheckFloorTexActivationCheckBox(){

	floorTexActivationCheckBox->setCheckState(Qt::Unchecked);

}


