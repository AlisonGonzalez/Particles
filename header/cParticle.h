#include <random>

#ifndef __C_PARTICLE_H__
#define __C_PARTICLE_H__

#include "vecs.h"
#ifdef __APPLE__
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
	#include <GLUT/glut.h>
#else
	#include "freeglut.h"
#endif

class Particle
{

public:
	Particle();
	~Particle();

	void draw();
	void stepSimulation(float dt);
	void addForce(float *force);
	bool inCollision(Particle* other);
	bool alive;
	float pos[3];
	float oDiffuse[3];
	float diffuse[3];

	float getAge() {return age; }
	void setAge(float time) {age = time;}
	void incrementAge(float time);
	void checkFloorCollisions();

private:	
	void clearForces();
	void integrateVerlet(float dt);

	float mass;
	
	float oldPos[3];
	float forces[3];
	float dragForce[3];
	
	float specular[3];
	float shininess;

	float radius;
	float age;
	float restitutionCoefficient;
	
};

#endif
