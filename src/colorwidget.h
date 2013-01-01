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
 * @file   colorwidget.h
 * @author Rafael Palomar
 * @date   Sun Apr 25 20:01:13 2010
 * 
 * @brief  ColorWidget class header.
 * 
 * This file contains the declaration of the class ColorWidget. 
 *
 */


#ifndef COLORWIDGET_H
#define COLORWIDGET_H

#include <QWidget>

//Forward class declarations.
class QLabel;
class QSlider;

//!Class ColorWidget.
class ColorWidget: public QWidget{

	Q_OBJECT;

  private:
	QLabel *redValueLabel;
	QLabel *greenValueLabel;
	QLabel *blueValueLabel;
	QSlider *redSlider;
	QSlider *greenSlider;
	QSlider *blueSlider;

	QSlider *createSlider();

  public:
	ColorWidget(QWidget *parent=0);
	
  private slots:
	void updateRed(int newValue);
	void updateGreen(int newValue);
	void updateBlue(int newValue);	

  signals:
   	void redChanged(int newValue);   //!< Emmited when red value has changed.
	void greenChanged(int newValue); //!< Emmited when green value has changed.
	void blueChanged(int newValue);  //!< Emmited when blue value has changed.

}; //END class ColorWidget

#endif
