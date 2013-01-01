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
 * @file   fxwidget.h
 * @author Rafael Palomar
 * @date   Sun Apr 25 20:12:56 2010
 * 
 * @brief  FXWidget class header.
 * 
 * This file contains the declaration of the class FXWidget.
 * 
 */


#ifndef FXWIDGET_H
#define FXWIDGET_H

#include <QWidget>

//Forward class declarations.
class QCheckBox;
class QSlider;
class QLabel;
class QComboBox;

//!Class FXWiget.
class FXWidget: public QWidget{

	Q_OBJECT;

  private:
	QCheckBox *reflectionActivationCheckBox;
	QCheckBox *fogActivationCheckBox;
	QLabel *fogRedValueLabel;
	QLabel *fogGreenValueLabel;
	QLabel *fogBlueValueLabel;
	QLabel *fogStartValueLabel;
	QLabel *fogEndValueLabel;
	QSlider *fogRedSlider;
	QSlider *fogGreenSlider;
	QSlider *fogBlueSlider;
	QSlider *fogStartSlider;
	QSlider *fogEndSlider;
	QComboBox *fogEquationsComboBox;

	QSlider *createColorSlider();

  public:
	FXWidget(QWidget *parent=0);

  public slots:
	void updateRed(int);
	void updateGreen(int);
	void updateBlue(int);
	void updateStart(int);
	void updateEnd(int);
	
  signals:
	void setReflection(bool enable); //!< Emmited on reflection switching.
	void setFog(bool enable); //!< Emmited on fog switching.
	void fogRedChanged(int value); //!< Emmited when red has changed on fog.
	void fogGreenChanged(int value); //!< Emmited when green has changed on fog.
	void fogBlueChanged(int value); //!< Emmited when blue has changed on fog.
	void fogStartChanged(int value); //!< Emmited when start plane has changed.
	void fogEndChanged(int value); //!< Emmited when end plane has changed.

}; //END class FXWidget.


#endif
