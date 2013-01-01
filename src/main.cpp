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
 * @file   main.cpp
 * @author Rafael Palomar
 * @date   Thu Apr  8 17:45:38 2010
 * 
 * @brief  Main
 * 
 * This file contains the entry point to the program.
 * 
 */


#include <QApplication>
#include <QDesktopWidget>

#include "mainwindow.h"


/** 
 * @brief Main
 *
 * This functions acts as entry point of the program. Its purpose
 * is to initialize, show and end the program.
 *
 * @param argc number of arguments.
 * @param argv arguments array.
 * 
 * @return code extracted from the application execution.
 */
int main(int argc, char *argv[]){

	QApplication app(argc, argv);

	//Create main window
	MainWindow mainWindow;
	mainWindow.resize(853,480);

	int desktopArea = QApplication::desktop()->width()* 
		QApplication::desktop()->height();
	
	int widgetArea = mainWindow.width()*mainWindow.height();
	
	/*How to show the window considering the size of the
	  window in relation to the desktop area*/
	if(((float)widgetArea / (float) desktopArea) < 0.75f)
		mainWindow.show();
	else
		mainWindow.showMaximized();
	
	//Execute the application.
	return app.exec();
}
