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
 * @file   glwidget.h
 * @author Rafael Palomar 
 * @date   Sun Apr 25 20:14:33 2010
 * 
 * @brief  GLWidget class header.
 * 
 * This file contains the declaration of the class GLWidget.
 * 
 */

#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QtOpenGL>


//!Class GLWidget.
class GLWidget: public QGLWidget{
  
	Q_OBJECT;
  
  private:
    QPoint lastPos;
    int xRot;
    int yRot;
    int zRot;
    int cubeRedComponent;
    int cubeGreenComponent;
    int cubeBlueComponent;
	float ambientLight[4];
	float diffuseLight[4];
	float lightPosition[4];
	float lightPositionMirror[4];
	float fogColor[4];
	GLuint textures[2];
	bool cubeTexturing;
	bool floorTexturing;
	bool lighting;
	bool reflection;
	bool fog;
    
    inline void drawCube();
	inline void drawTexturizedCube();
	inline void drawFloor();
	inline void drawTexturizedFloor();
  
  public:
	GLWidget(QWidget *parent = 0);
	QSize sizeHint() const;
	QSize minimumSize() const;
    
  protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
	
  public slots:
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);  
    void setCubeRedComponent(int value);
    void setCubeGreenComponent(int value);
    void setCubeBlueComponent(int value);
	void enableLighting();
	void disableLighting();
	void setLighting(bool activation);
	void setAmbientLightRedComponent(int value);
	void setAmbientLightGreenComponent(int value);
	void setAmbientLightBlueComponent(int value);
	void setDiffuseLightRedComponent(int value);
	void setDiffuseLightGreenComponent(int value);
	void setDiffuseLightBlueComponent(int value);	
	void enableCubeTexture(const QString &imageFileName);
	void disableCubeTexture();
	void enableFloorTexture(const QString &imageFileName);
	void disableFloorTexture();
	void setReflection(bool enable);
	void setFog(bool enable);
	void setFogRedComponent(int);
	void setFogGreenComponent(int);
	void setFogBlueComponent(int);
	void setFogStart(int);
	void setFogEnd(int);

  signals:
	void cubeTexturingFailed(); //!< Emmited if cube texturing process failed.
	void floorTexturingFailed(); //!< Emmited if floor texuring process failed.


}; //END class GLWidget.

#endif
