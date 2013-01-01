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
 * @file   texturewidget.h
 * @author Rafael Palomar
 * @date   Sun Apr 25 19:21:53 2010
 * 
 * @brief  TextureWidget header.
 * 
 * This file contains the declaration for the class TextureWidget.
 * 
 */

#ifndef TEXTUREWIDGET_H
#define TEXTUREWIDGET_H

#include <QWidget>

class QLineEdit;
class QPushButton;
class QCheckBox;

//!Class TextureWidget.
class TextureWidget: public QWidget{
	
	Q_OBJECT;
	
  private:
	QLineEdit *cubeTexFileLineEdit;
	QPushButton *cubeTexBrowseButton;
	QCheckBox *cubeTexActivationCheckBox;
	QLineEdit *floorTexFileLineEdit;
	QPushButton *floorTexBrowseButton;
	QCheckBox *floorTexActivationCheckBox;

  public:
	TextureWidget(QWidget *parent=0);

  private slots:
	void browseCubeTexture();
	void updateCubeTexture(int checkBoxStatus);
	void browseFloorTexture();	
	void updateFloorTexture(int checkBoxStatus);

  public slots:
	void uncheckCubeTexActivationCheckBox();
	void uncheckFloorTexActivationCheckBox();

  signals:
	//!Emmited on cube texture enabling.
	void enableCubeTexture(const QString &fileName);
	//!Emmited on cube texture disabling.
	void disableCubeTexture();
	//!Emmited on floor texture enabling.
	void enableFloorTexture(const QString &fileName);
	//!Emmited on floor texture disabling.
	void disableFloorTexture();

}; //END TextureWidget.

#endif
