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
 * @file   mainwindow.cpp
 * @author Rafael Palomar
 * @date   Sun Apr 25 19:27:51 2010
 * 
 * @brief  This file contains the implementation
 * of the MainWindow widget which consist only of
 * a central widget.
 * 
 * 
 */

#include "mainwindow.h"

#include <QGridLayout>

#include "centralwidget.h"

/** 
 * @brief default constructor.
 * 
 * Creates and initializes the central widget and sets
 * the window title.
 */
MainWindow::MainWindow(){

	centralWidget = new CentralWidget();

	setCentralWidget(centralWidget);
	setWindowTitle("Basic GL");
	
}
