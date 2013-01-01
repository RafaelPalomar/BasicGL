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
 * @file   centralwidget.h
 * @author Rafael Palomar
 * @date   Tue Apr 13 16:27:56 2010
 * 
 * @brief  CentralWidget header
 *
 * This file contains the header for the
 * class CentralWidget.
 * 
 */


#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

#include <QWidget>

class GLWidget;
class QTabWidget;
class ColorWidget;
class LightingWidget;
class TextureWidget;
class FXWidget;

//!CentralWidget
class CentralWidget: public QWidget{
	
	Q_OBJECT;
	
private:
	GLWidget *glWidget;
	QTabWidget *tabWidget;
	ColorWidget *colorWidget;
	LightingWidget *lightingWidget;	
	TextureWidget *textureWidget;
	FXWidget *fxWidget;
	
public:
	CentralWidget(QWidget *parent=0);
	
	
}; //END class CentralWidget

#endif
