
#include "cPlane.h"
#ifdef __APPLE__
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
	#include <GLUT/glut.h>
#else
	#include "freeglut.h"
#endif


cPlane::cPlane(int w, int h){

	m_h = h;
	m_w = w;

	specularMat0[0] = 0.8;
	specularMat0[1] = 0.8;
	specularMat0[2] = 0.8;
	shine = 64;	
}

cPlane::~cPlane()
{
}

void cPlane::display(int stepSize, float *color){
	int X, Z;
	float vec0[3], vec1[3], vec2[3], vec3[3];
	glPushMatrix();
		glMaterialfv(GL_FRONT, GL_SPECULAR, specularMat0);
		glMaterialf(GL_FRONT, GL_SHININESS, shine);
		glEnable(GL_COLOR_MATERIAL);
		glColor3fv(color);
	glPopMatrix();

	glBegin( GL_QUADS );

	for ( X = 0; X < (m_w-stepSize); X += stepSize )
		for ( Z = 0; Z < (m_h-stepSize); Z += stepSize )
		{
			// Get The (X, Y, Z) Value For The Bottom Left Vertex
			vec0[0] = X;							
			vec0[1] = 0;	
			vec0[2] = Z;							

			// Set The Color Value Of The Current Vertex
			//SetVertexColor(pHeightMap, x, z);

			glNormal3f(0,1,0);
			glVertex3fv(vec0);			// Send This Vertex To OpenGL To Be Rendered

			// Get The (X, Y, Z) Value For The Top Left Vertex
			vec1[0] = X;							
			vec1[1] = 0;	
			vec1[2] = Z + stepSize ;
						
			// Set The Color Value Of The Current Vertex
			//SetVertexColor(pHeightMap, x, z);
			glNormal3f(0,1,0);
			glVertex3fv(vec1);			// Send This Vertex To OpenGL To Be Rendered

			// Get The (X, Y, Z) Value For The Top Right Vertex
			vec2[0] = X + stepSize;
			vec2[1] = 0;
			vec2[2] = Z + stepSize;
			
			// Set The Color Value Of The Current Vertex
			//SetVertexColor(pHeightMap, x, z);
			glNormal3f(0,1,0);
			glVertex3fv(vec2);			// Send This Vertex To OpenGL To Be Rendered

			// Get The (X, Y, Z) Value For The Bottom Right Vertex
			vec3[0] = X + stepSize; 
			vec3[1] = 0; 
			vec3[2] = Z;

			// Set The Color Value Of The Current Vertex
			//SetVertexColor(pHeightMap, x, z);
			glNormal3f(0,1,0);
			glVertex3fv(vec3);			// Send This Vertex To OpenGL To Be Rendered
		}
	glEnd();

	glDisable(GL_COLOR_MATERIAL);

}
