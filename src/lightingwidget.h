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
 * @file   lightingwidget.h
 * @author Rafael Palomar
 * @date   Sun Apr 25 20:17:33 2010
 * 
 * @brief  LigthningWidget class header.
 * 
 *  This file contains the declaration of the class LightingWidget.
 * 
 */


#ifndef LIGHTING_H
#define LIGHTING_H

#include <QWidget>

class QLabel;
class QSlider;
class QCheckBox;

//!Class LightingWidget.
class LightingWidget: public QWidget{

	Q_OBJECT;
	
  private:
	QCheckBox *enableLightingCheckBox;
	QSlider *ambientRedSlider;
	QSlider *ambientGreenSlider;
	QSlider *ambientBlueSlider;
	QSlider *diffuseRedSlider;
	QSlider *diffuseGreenSlider;
	QSlider *diffuseBlueSlider;	
	QLabel *ambientRedValueLabel;
	QLabel *ambientGreenValueLabel;
	QLabel *ambientBlueValueLabel;
	QLabel *diffuseRedValueLabel;
	QLabel *diffuseGreenValueLabel;
	QLabel *diffuseBlueValueLabel;	
	
	QSlider *createSlider();
	
  public:
	LightingWidget(QWidget *parent=0);
	
  signals:
	void setLighting(bool enable); //!< Emmited on lighting activation switching.
	void ambientLightRedChanged(int newValue); //!< Emmited when ambient red has changed.
	void ambientLightGreenChanged(int newValue);//!< Emmited when ambient green has changed.
	void ambientLightBlueChanged(int newValue);//!< Emmited when ambient blue has changed.
	void diffuseLightRedChanged(int newValue);//!< Emmited when diffuse red has changed.
	void diffuseLightGreenChanged(int newValue);//!< Emmited when diffuse green has changed.
	void diffuseLightBlueChanged(int newValue);//!< Emmited when diffuse blue has changed.
								  
  private slots:
	void ambientLightUpdateRed(int newValue);
	void ambientLightUpdateGreen(int newValue);
	void ambientLightUpdateBlue(int newValue);	
	void diffuseLightUpdateRed(int newValue);
	void diffuseLightUpdateGreen(int newValue);
	void diffuseLightUpdateBlue(int newValue);	

}; //END class LightingWidget.

#endif
