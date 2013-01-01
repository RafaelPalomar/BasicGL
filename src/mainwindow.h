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
 * @file   mainwindow.h
 * @author Rafael Palomar
 * @date   Thu March  8 17:50:09 2010
 * 
 * @brief  MainWindow Header File
 * 
 * This file contains the prototype for the MainWindow class,
 * which is derived from QMainWindow widget.
 * 
 */


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

//Forward class declaration
class CentralWidget;

//!Class MainWindow
class MainWindow: public QMainWindow
{
  private:
	CentralWidget *centralWidget;	
	
  public:
	MainWindow();

}; //END class MainWindow.

#endif
