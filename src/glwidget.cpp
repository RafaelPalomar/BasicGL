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
 * @file   glwidget.cpp
 * @author Rafael Palomar
 * @date   Sun Apr 25 20:53:40 2010
 * 
 * @brief  GLWidget class definition.
 * 
 * This file contains the defined functions for the class GLWidget.
 * 
 */

#include "glwidget.h"

#include <QMouseEvent>
#include <QMessageBox>

#include <GL/glu.h>

/** 
 * @brief Default constructor.
 *
 * This function initializes the variables involved with
 * the scene and the objects inside.
 * 
 * @param parent the parent widget for the GLWidget.
 */
GLWidget::GLWidget(QWidget *parent)
    :QGLWidget(QGLFormat(QGL::DoubleBuffer|QGL::SampleBuffers),parent){  
  
    setSizePolicy(QSizePolicy(QSizePolicy::MinimumExpanding,
							  QSizePolicy::MinimumExpanding));

    xRot = 0;
    yRot = 0;
    zRot = 0;
    cubeRedComponent = 0;
    cubeGreenComponent = 0;
    cubeBlueComponent = 0;
	cubeTexturing = false;
	floorTexturing = false;
	lighting = false;
	reflection = false;
	fog = false;
	ambientLight[0] = 0.0f;
	ambientLight[1] = 0.0f;
	ambientLight[2] = 0.0f;
	ambientLight[3] = 0.0f;
	diffuseLight[0] = 0.0f;
	diffuseLight[1] = 0.0f;
	diffuseLight[2] = 0.0f;
	diffuseLight[3] = 0.0f;
	lightPosition[0] = 0.0f;
	lightPosition[1] = 0.0f;
	lightPosition[2] = 1.0f;
	lightPosition[3] = 1.0f;	   
	lightPositionMirror[0] = 0.0f;
	lightPositionMirror[1] = -15.0f;
	lightPositionMirror[2] = 1.0f;
	lightPositionMirror[3] = 1.0f; 
	textures[0] = 0;
	textures[1] = 0;
	fogColor[0] = 0;
	fogColor[1] = 0;
	fogColor[2] = 0;
	fogColor[3] = 1.0f;
}

/** 
 * @brief Size hint
 * 
 * 
 * @return the preferred size for the widget.
 */
QSize GLWidget::sizeHint() const{
  
    return QSize(400,400);  
}

/** 
 * @brief Minimum size
 * 
 * 
 * @return the minimum size of the widget.
 */
QSize GLWidget::minimumSize() const{

    return QSize(50,50);
}


/** 
 * @brief Initialize GL.
 * 
 * OpenGL widget initialization. 
 *
 */
void GLWidget::initializeGL(){
  	
    qglClearColor(QColor::fromRgb(0,0,0));
  
    glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
    glShadeModel(GL_SMOOTH);

	glLightfv(GL_LIGHT1, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLight);
	
	glEnable(GL_LIGHT1);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT,GL_AMBIENT_AND_DIFFUSE);  

	glGenTextures(2,textures);
	
	glBindTexture(GL_TEXTURE_2D,textures[0]);  		
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	// Linear Filtering
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);	// Linear Filtering  
	glBindTexture(GL_TEXTURE_2D,textures[1]);  		
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	// Linear Filtering
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);	// Linear Filtering  
	
	glFogi(GL_FOG_MODE, GL_LINEAR);
	glFogf(GL_FOG_START, 0.0f);
	glFogf(GL_FOG_END, 0.0f);
}

/** 
 * @brief resize the widget and the scene
 * 
 * @param width the new width for the widget.
 * @param height the new height for the widget
 */
void GLWidget::resizeGL(int width, int height){

    int side = qMin(width,height);
	//    glViewport((width-side)/2,(height-side)/2,side,side);
	glViewport(0,0,width,height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,1.0f,200.0f);
    glMatrixMode(GL_MODELVIEW);
}

/** 
 * @brief Paint GL
 *
 * This function defines how to draw the scene. Note that here is where
 * the widget variables are involved.
 * 
 */
void GLWidget::paintGL(){

	
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  
	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	glTranslatef(0.0f, -25.0f, 0.0f);
	glRotatef(25, 1.0f, 0.0f, 0.0f);

	glColor3ub(1,1,1);

 	if(lighting){
		
		glEnable(GL_LIGHT1);
		glEnable(GL_LIGHTING);
		glEnable(GL_NORMALIZE);
	}
	
	if(reflection){

		glFrontFace(GL_CW);
		glLightfv(GL_LIGHT1, GL_POSITION, lightPositionMirror);

		glPushMatrix(); //PUSH

		glTranslatef(0.0f, -15.0f, -60.0f);	
		glRotatef(xRot/16,1.0f, 0.0f, 0.0f);
		glRotatef(yRot/16,0.0f, 1.0f, 0.0f);
		glRotatef(zRot/16,0.0f, 0.0f, 1.0f);
		glScalef(5.0f, -5.0f, 5.0f);
		if(cubeTexturing){

			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D,textures[0]);  	
			drawTexturizedCube();
			glDisable(GL_TEXTURE_2D);
		}
		else
			drawCube();			

		glPopMatrix(); //POP
		glFrontFace(GL_CCW);
	}

	glLightfv(GL_LIGHT1, GL_POSITION, lightPosition);

	glPushMatrix();

	glTranslatef(0.0f, 4.0f, -60.0f);	
	glRotatef(xRot/16,1.0f, 0.0f, 0.0f);
    glRotatef(yRot/16,0.0f, 1.0f, 0.0f);
    glRotatef(zRot/16,0.0f, 0.0f, 1.0f);
	glScalef(5.0f, 5.0f, 5.0f);

	if(cubeTexturing){
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,textures[0]);
		drawTexturizedCube();
		glDisable(GL_TEXTURE_2D);
	}
	else
		drawCube();			


	glPopMatrix();

	if(lighting){
		glDisable(GL_LIGHTING);
		glDisable(GL_LIGHT1);
		glDisable(GL_NORMALIZE);
	}


	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glPushMatrix();
	glTranslatef(0.0f, -6.0f, -30.0f);
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);


	if(floorTexturing){
		glScalef(50.0f, 50.0f, 50.0f);
		glBindTexture(GL_TEXTURE_2D,textures[1]);  	
		glEnable(GL_TEXTURE_2D);
		drawTexturizedFloor();
		glDisable(GL_TEXTURE_2D);
	}
	else{
		glScalef(10.0f, 10.0f, 10.0f);
		drawFloor();
	}

	glPopMatrix();

	glDisable(GL_BLEND);
}

/** 
 * @brief Mouse press event.
 *
 * Saves the position of the mouse when pressed. 
 *
 * @param event the QMouseEvent associated when the mouse is pressed.
 */
void GLWidget::mousePressEvent(QMouseEvent *event){

    lastPos = event->pos();
}


/** 
 * @brief Mouse move event.
 *
 * This function defines what to do when the mouse
 * is pressed and moved around the scene, that is,
 * makes rotations for the cube regarding the mouse movement and status.
 * 
 * @param event the mouse event recorded.
 */
void GLWidget::mouseMoveEvent(QMouseEvent *event){

    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    if(event->buttons() & Qt::LeftButton){
    
		setXRotation(xRot + dy*8);
		setYRotation(yRot + dx*8);  

    } else if(event->buttons() & Qt::RightButton){
    
		setXRotation(xRot + dy*8);
		setZRotation(zRot + dx*8);  
    }

    lastPos = event->pos();
}

/** 
 * @brief Set x angle rotation.
 * 
 * This function updates the x rotation angle by modifying
 * the inner variable that keeps this value.
 * 
 * @param angle new x angle
 */
void GLWidget::setXRotation(int angle){
  
    //Normalize Angle
    while(angle < 0)
		angle += 360*16;
    while(angle > 360*16)
		angle -= 360*16;

    if(angle != xRot){
		xRot = angle;
		updateGL();
    }
}


/** 
 * @brief Set y angle rotation.
 * 
 * This function updates the y rotation angle by modifying
 * the inner variable that keeps this value.
 * 
 * @param angle new y angle
 */
void GLWidget::setYRotation(int angle){
  
    //Normalize Angle
    while(angle < 0)
		angle += 360*16;
    while(angle > 360*16)
		angle -= 360*16;
  
    if(angle != yRot){
		yRot = angle;
		updateGL();
    }
}


/** 
 * @brief Set z angle rotation.
 * 
 * This function updates the z rotation angle by modifying
 * the inner variable that keeps this value.
 * 
 * @param angle new z angle
 */
void GLWidget::setZRotation(int angle){
  
    //Normalize Angle
    while(angle < 0)
		angle += 360*16;
    while(angle > 360*16)
		angle -= 360*16;

    if(angle != zRot){
		zRot = angle;
		updateGL();
    }
}

/** 
 * @brief Set the red component of the cube color.
 *
 * This function updates the red cube color component 
 * by modifying the variable that keeps this value.
 *
 * @param value new value for the red component of the cube.
 */
void GLWidget::setCubeRedComponent(int value){
  
    if(value<0 || value>255)
		cubeRedComponent = 0;
    else
		cubeRedComponent = value;
  
    updateGL();  
}

/** 
 * @brief Set the green component of the cube color.
 *
 * This function updates the green cube color component 
 * by modifying the variable that keeps this value.
 *
 * @param value new value for the green component of the cube.
 */
void GLWidget::setCubeGreenComponent(int value){
  
    if(value<0 || value>255)
		cubeGreenComponent = 0;
    else
		cubeGreenComponent = value;
  
    updateGL();  
}

/** 
 * @brief Set the blue component of the cube color.
 *
 * This function updates the blue cube color component 
 * by modifying the variable that keeps this value.
 *
 * @param value new value for the blue component of the cube.
 */
void GLWidget::setCubeBlueComponent(int value){
  
    if(value<0 || value>255)
		cubeBlueComponent = 0;
    else
		cubeBlueComponent = value;
  
    updateGL();  
}

/** 
 * @brief Set the red component of the ambient light.
 *
 * This function updates the red component of the ambient light.
 * by modifying the variable that keeps this value.
 *
 * @param value new value for the blue component of the cube.
 */
void GLWidget::setAmbientLightRedComponent(int value){
  
    if(value<0 || value>255)
		ambientLight[0] = 0;
    else
		ambientLight[0] = value/256.0f;

	glLightfv(GL_LIGHT1, GL_AMBIENT, ambientLight);
  
    updateGL();  
}

/** 
 * @brief Set the green component of the ambient light.
 *
 * This function updates the green component of the ambient light.
 * by modifying the variable that keeps this value.
 *
 * @param value new value for the blue component of the cube.
 */
void GLWidget::setAmbientLightGreenComponent(int value){
  
    if(value<0 || value>255)
		ambientLight[1] = 0;
    else
		ambientLight[1] = value/256.0f;

	glLightfv(GL_LIGHT1, GL_AMBIENT, ambientLight);
  
    updateGL();  
}

/** 
 * @brief Set the blue component of the ambient light.
 *
 * This function updates the blue component of the ambient light.
 * by modifying the variable that keeps this value.
 *
 * @param value new value for the blue component of the cube.
 */
void GLWidget::setAmbientLightBlueComponent(int value){
  
    if(value<0 || value>255)
		ambientLight[2] = 0;
    else
		ambientLight[2] = value/256.0f;

	glLightfv(GL_LIGHT1, GL_AMBIENT, ambientLight);
  
    updateGL();  
}
/** 
 * @brief Set the red component of the diffuse light.
 *
 * This function updates the red component of the diffuse light.
 * by modifying the variable that keeps this value.
 *
 * @param value new value for the blue component of the cube.
 */
void GLWidget::setDiffuseLightRedComponent(int value){
  
    if(value<0 || value>255)
		diffuseLight[0] = 0;
    else
		diffuseLight[0] = value/256.0f;

	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLight);

    updateGL();  
}

/** 
 * @brief Set the green component of the diffuse light.
 *
 * This function updates the green component of the diffuse light.
 * by modifying the variable that keeps this value.
 *
 * @param value new value for the blue component of the cube.
 */
void GLWidget::setDiffuseLightGreenComponent(int value){
  
    if(value<0 || value>255)
		diffuseLight[1] = 0;
    else
		diffuseLight[1] = value/256.0f;

	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLight);
  
    updateGL();  
}

/** 
 * @brief Set the blue component of the diffuse light.
 *
 * This function updates the blue component of the diffuse light.
 * by modifying the variable that keeps this value.
 *
 * @param value new value for the blue component of the cube.
 */
void GLWidget::setDiffuseLightBlueComponent(int value){
  
    if(value<0 || value>255)
		diffuseLight[2] = 0;
    else
		diffuseLight[2] = value/256.0f;

	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLight);
  
    updateGL();  
}

/** 
 * @brief Enable the cube texture
 *
 * This function activates the texturing for the cube by loading the image texture
 * and setting the appropiates variables to enable the texturing mode on the cube. 
 *
 * @param imageFileName the name of the image file that contains the texture data.
 */
void GLWidget::enableCubeTexture(const QString &imageFileName){

	QImage image;

	if(!image.load(imageFileName)){
		QMessageBox::warning(this,
							 "Load Image Error", 
							 "Loading image for cube texturing was impossible");
		emit(cubeTexturingFailed());
		return;
	}

	if( (image.width()!= 256 && image.height() != 512)
		|| image.width() != image.height()){
		
		QMessageBox::warning(this,
							 "Image Size Error", 
							 "The image must be 256x256 or 512x512");
		emit(cubeTexturingFailed());
		return;
	}
		

	QImage glImage = QGLWidget::convertToGLFormat(image);
	
	glBindTexture(GL_TEXTURE_2D,textures[0]);  
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB, glImage.width(),glImage.height(),0, 
				 GL_RGBA,GL_UNSIGNED_BYTE, glImage.bits());


	cubeTexturing = true;
	updateGL();
}

/** 
 * @brief Enable the floor texture
 *
 * This function activates the texturing for the floor by loading the image texture
 * and setting the appropiates variables to enable the texturing mode on the floor. 
 *
 * @param imageFileName the name of the image file that contains the texture data.
 */
void GLWidget::enableFloorTexture(const QString &imageFileName){

	QImage image;

	if(!image.load(imageFileName)){
		QMessageBox::warning(this,
							 "Load Image Error", 
							 "Loading image for floor texturing was impossible");
		emit(floorTexturingFailed());
		return;
	}

	if( (image.width()!= 256 && image.height() != 512)
		|| image.width() != image.height()){
		
		QMessageBox::warning(this,
							 "Image Size Error", 
							 "The image must be 256x256 or 512x512");
		emit(floorTexturingFailed());
		return;
	}
		

	QImage glImage = QGLWidget::convertToGLFormat(image);

	
	glBindTexture(GL_TEXTURE_2D,textures[1]);  	
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB, glImage.width(),glImage.height(),0, 
				 GL_RGBA,GL_UNSIGNED_BYTE, glImage.bits());

	floorTexturing = true;
	updateGL();
}

/** 
 * @brief Disable cube texturing.
 *
 * This function sets the cube texturing variable off and updates the scene.
 * 
 */
void GLWidget::disableCubeTexture(){

	cubeTexturing = false;
	updateGL();
}

/** 
 * @brief Disable floor texturing.
 *
 * This function sets the floor texturing variable off and updates the scene.
 * 
 */
void GLWidget::disableFloorTexture(){

	floorTexturing = false;
	updateGL();
}

/** 
 * @brief Enable lighting.
 *
 * This function sets the lighting variable on and updates the scene.
 * 
 */
void GLWidget::enableLighting(){

	lighting = true;
	
	updateGL();
}

/** 
 * @brief Disable lighting.
 *
 * This function sets the lighting variable off and updates the scene.
 * 
 */
void GLWidget::disableLighting(){

	lighting = false;
	
	updateGL();	
}

/** 
 * @brief Set reflection.
 *
 * This function enables/disables the reflection effect depending on the
 * value specified as parameter.
 * 
 * @param activation indicates whether to enable/disable the reflection effect.
 */
void GLWidget::setReflection(bool activation){

	if(activation)
		reflection = true;
	else
		reflection = false;

	updateGL();
}

/** 
 * @brief Set ligthing.
 *
 * This function enables/disables the ligthing effect depending on the
 * value specified as parameter.
 * 
 * @param activation indicates whether to enable/disable the ligthing effect.
 */
void GLWidget::setLighting(bool activation){

	if(activation)
		enableLighting();
	else
		disableLighting();
}

/** 
 * @brief Disable fog.
 *
 * This function sets the fog variable off and updates the scene.
 * 
 */
void GLWidget::setFog(bool activation){

	if(activation){
		fog=true;
		glEnable(GL_FOG);
		qglClearColor(QColor::fromRgbF(fogColor[0],
									   fogColor[1],
									   fogColor[2]));
	}
	else{
		fog = false;
		glDisable(GL_FOG);
		qglClearColor(QColor::fromRgbF(0,0,0));
									   
	}

	
	glFogfv(GL_FOG_COLOR, fogColor);				  
	
	updateGL();
}

/** 
 * @brief Set the red component of the fog effect.
 *
 * This function updates the green component of the fog effect.
 * by modifying the variable that keeps this value.
 *
 * @param value new value for the red component of the fog effect.
 */
void GLWidget::setFogRedComponent(int value){
  
    if(value<0 || value>255)
		fogColor[0] = 0;
    else
		fogColor[0] = value/256.0f;

	if(fog){
	
		qglClearColor(QColor::fromRgbF(fogColor[0],
									   fogColor[1],
									   fogColor[2]));
		
		glFogfv(GL_FOG_COLOR, fogColor);				  
		updateGL();
	}
}

/** 
 * @brief Set the green component of the fog effect.
 *
 * This function updates the green component of the fog effect.
 * by modifying the variable that keeps this value.
 *
 * @param value new value for the green component of the fog effect.
 */
void GLWidget::setFogGreenComponent(int value){
	
	if(value<0 || value>255)
		fogColor[1] = 0;
	else
		fogColor[1] = value/256.0f;
	
	if(fog){
	
		qglClearColor(QColor::fromRgbF(fogColor[0],
									   fogColor[1],
									   fogColor[2]));
		glFogfv(GL_FOG_COLOR, fogColor);				  
		updateGL();  
	}
}

/** 
 * @brief Set the blue component of the fog effect.
 *
 * This function updates the green component of the fog effect.
 * by modifying the variable that keeps this value.
 *
 * @param value new value for the blue component of the fog effect.
 */
void GLWidget::setFogBlueComponent(int value){
  
	
	if(value<0 || value>255)
		fogColor[2] = 0;
	else
		fogColor[2] = value/256.0f;
	
	if(fog){	
		qglClearColor(QColor::fromRgbF(fogColor[0],
									   fogColor[1],
									   fogColor[2]));
		glFogfv(GL_FOG_COLOR, fogColor);
		updateGL();
	}
}

/** 
 * @brief Set the fog start.
 *
 * This function sets the distance of the start plane for the fog effect
 *
 * @param value new value for the red component of the fog effect.
 */
void GLWidget::setFogStart(int value){

	glFogf(GL_FOG_START, (float) value);

	updateGL();
}

/** 
 * @brief Set the fog end.
 *
 * This function sets the distance of the end plane for the fog effect
 *
 * @param value new value for the red component of the fog effect.
 */
void GLWidget::setFogEnd(int value){

	glFogf(GL_FOG_END, (float) value);

	updateGL();
}

/** 
 * @brief Draw a cube.
 *
 * This function draws a cube taking in account the configuration
 * for the cube given by the parameters represented through the internal
 * variables of the class.
 * 
 */
void GLWidget::drawCube(){

    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(1.0f, 1.0f);
    glColor3ub(cubeRedComponent, cubeGreenComponent, cubeBlueComponent);
	
	glBegin(GL_QUADS);
    //Front Face
    glNormal3f(0.0f,0.0f,1.0f);
	glVertex3f(1,-1,1);
    glVertex3f(1,1,1);
    glVertex3f(-1,1,1);
    glVertex3f(-1,-1,1);  
   
	 //Back Face
    glNormal3f(0.0f,0.0f,-1.0f);
    glVertex3f(-1,-1,-1);
    glVertex3f(-1,1,-1);
    glVertex3f(1,1,-1);
    glVertex3f(1,-1,-1);
  
	//Left Face
    glNormal3f(-1.0f,0.0f,0.0f);
    glVertex3f(-1,-1,1);
    glVertex3f(-1,1,1);
    glVertex3f(-1,1,-1); 
    glVertex3f(-1,-1,-1);  
   
    //Right Face
    glNormal3f(1.0f,0.0f,0.0f);
    glVertex3f(1,-1,-1);
    glVertex3f(1,1,-1);
    glVertex3f(1,1,1);
    glVertex3f(1,-1,1);
  
    //Top Face
	glNormal3f(0.0f,1.0f,0.0f);
    glVertex3f(1,1,1);
    glVertex3f(1,1,-1);
    glVertex3f(-1,1,-1);
    glVertex3f(-1,1,1);

    //Bottom Face
    glNormal3f(0.0f,-1.0f,0.0f);
    glVertex3f(-1,-1,1);
    glVertex3f(-1,-1,-1);
    glVertex3f(1,-1,-1);
    glVertex3f(1,-1,1);
    glEnd(); //GL_QUADS

    glDisable(GL_POLYGON_OFFSET_FILL);

    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glColor3ub(255-cubeRedComponent, 255-cubeGreenComponent, 255-cubeBlueComponent);
    glBegin(GL_QUADS);
    //Front Face
    glVertex3f(1,-1,1);
    glVertex3f(1,1,1);
    glVertex3f(-1,1,1);
    glVertex3f(-1,-1,1);
  
    //Back Face
    glVertex3f(-1,-1,1);
    glVertex3f(-1,1,1);
    glVertex3f(-1,1,-1); 
    glVertex3f(-1,-1,-1);
  
    //Left Face
    glVertex3f(-1,-1,-1);
    glVertex3f(-1,1,-1);
    glVertex3f(1,1,-1);
    glVertex3f(1,-1,-1);
  
    //Right Face
    glVertex3f(1,-1,-1);
    glVertex3f(1,1,-1);
    glVertex3f(1,1,1);
    glVertex3f(1,-1,1);
  
    //Top Face
    glVertex3f(1,1,1);
    glVertex3f(1,1,-1);
    glVertex3f(-1,1,-1);
    glVertex3f(-1,1,1);

    //Bottom Face
    glVertex3f(-1,-1,1);
    glVertex3f(-1,-1,-1);
    glVertex3f(1,-1,-1);
    glVertex3f(1,-1,1);
    glEnd(); //GL_QUADS

}

/** 
 * @brief Draw a texturized cube.
 *
 * This function draws a texturized cube taking in account the configuration
 * for the cube given by the parameters represented through the internal
 * variables of the class.
 * 
 */
void GLWidget::drawTexturizedCube(){

    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(1.0f, 1.0f);
    glColor3ub(cubeRedComponent, cubeGreenComponent, cubeBlueComponent);
	
	glBegin(GL_QUADS);
    //Front Face
    glNormal3f(0.0f,0.0f,1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1,-1,1);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1,1,1);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1,1,1);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1,-1,1);  
   
	 //Back Face
    glNormal3f(0.0f,0.0f,-1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1,-1,-1);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1,1,-1);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1,1,-1);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1,-1,-1);
  
	//Left Face
    glNormal3f(-1.0f,0.0f,0.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1,-1,1);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1,1,1);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1,1,-1); 
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1,-1,-1);  
   
    //Right Face
    glNormal3f(1.0f,0.0f,0.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1,-1,-1);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1,1,-1);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1,1,1);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1,-1,1);
  
    //Top Face
	glNormal3f(0.0f,1.0f,0.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1,1,1);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1,1,-1);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1,1,-1);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1,1,1);

    //Bottom Face
    glNormal3f(0.0f,-1.0f,0.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1,-1,1);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1,-1,-1);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1,-1,-1);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1,-1,1);
    glEnd(); //GL_QUADS

    glDisable(GL_POLYGON_OFFSET_FILL);

    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glColor3ub(255-cubeRedComponent, 255-cubeGreenComponent, 255-cubeBlueComponent);
    glBegin(GL_QUADS);
    //Front Face
    glVertex3f(1,-1,1);
    glVertex3f(1,1,1);
    glVertex3f(-1,1,1);
    glVertex3f(-1,-1,1);
  
    //Back Face
    glVertex3f(-1,-1,1);
    glVertex3f(-1,1,1);
    glVertex3f(-1,1,-1); 
    glVertex3f(-1,-1,-1);
  
    //Left Face
    glVertex3f(-1,-1,-1);
    glVertex3f(-1,1,-1);
    glVertex3f(1,1,-1);
    glVertex3f(1,-1,-1);
  
    //Right Face
    glVertex3f(1,-1,-1);
    glVertex3f(1,1,-1);
    glVertex3f(1,1,1);
    glVertex3f(1,-1,1);
  
    //Top Face
    glVertex3f(1,1,1);
    glVertex3f(1,1,-1);
    glVertex3f(-1,1,-1);
    glVertex3f(-1,1,1);

    //Bottom Face
    glVertex3f(-1,-1,1);
    glVertex3f(-1,-1,-1);
    glVertex3f(1,-1,-1);
    glVertex3f(1,-1,1);
    glEnd(); //GL_QUADS

}

/** 
 * @brief Draw the floor.
 *
 * This function draws a floor taking in account the configuration
 * for the cube given by the parameters represented through the internal
 * variables of the class.
 * 
 */
void GLWidget::drawFloor(){

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	
	for(int i=-50; i<50; i++){
 		for(int j=-50; j<50; j++){

			if((i+j)%2)
				glColor4f(1.0f, 1.0f, 1.0f, 0.8f);
			else
				glColor4f(0.0f, 0.0f, 0.0f, 0.8f);

			glBegin(GL_QUADS);
			glVertex3f(i+1, j, 0.0f);
			glVertex3f(i+1, j+1, 0.0f);
			glVertex3f(i, j+1, 0.0f);
			glVertex3f(i, j, 0.0f);
			glEnd();			
		}		
	}
}

/** 
 * @brief Draw a texturized floor.
 *
 * This function draws a cube taking in account the configuration
 * for the cube given by the parameters represented through the internal
 * variables of the class.
 * 
 */
void GLWidget::drawTexturizedFloor(){

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	
	glColor4f(1.0f, 1.0f, 1.0f, 0.8f);

	for(int i=-10; i<10; i++){
 		for(int j=-10; j<10; j++){

			glBegin(GL_QUADS);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(i+1, j, 0.0f);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(i+1, j+1, 0.0f);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(i, j+1, 0.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(i, j, 0.0f);
			glEnd();			
		}		
	}
}

