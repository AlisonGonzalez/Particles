
#include "cParticle.h"

Particle::Particle(){
	restitutionCoefficient = 0.8f;
	radius = 20.0f + 15.0f*((float)rand()) / (float)RAND_MAX;
	mass = radius;
	pos[0] = 1000.0f*((float) rand())/(float) RAND_MAX;
	pos[1] = 200.0f+100.0f*((float) rand())/(float) RAND_MAX;
	pos[2] = 1000.0f*((float) rand())/(float) RAND_MAX;
	
	oldPos[0] = pos[0];
	oldPos[1] = pos[1];
	oldPos[2] = pos[2];

	forces[0] = -10 + 20.0f * ((float)rand()) / (float)RAND_MAX;
	forces[1] = 0.0;
	forces[2] = -10 + 20.0f * ((float)rand()) / (float)RAND_MAX;

	dragForce[0] = forces[0];
	dragForce[1] = 0.0;
	dragForce[2] = forces[2];

	if (vecMagnitude(dragForce) > 1.0f){
		unitVector(dragForce);
	}
	alive = true;
	age = 0;
	
	diffuse[0] = 0.8f * ((float)rand()) / (float)RAND_MAX; // Save full red for collisions.
	diffuse[1] = ((float) rand())/(float) RAND_MAX;
	diffuse[2] = ((float) rand())/(float) RAND_MAX;

	oDiffuse[0] = diffuse[0];
	oDiffuse[1] = diffuse[1];
	oDiffuse[2] = diffuse[2];
	
	specular[0] = 0.8;
	specular[1] = 0.8;
	specular[2] = 0.8;
	shininess = 64;
}

Particle::~Particle(){
}

void Particle::draw(){
	glPushMatrix();{
		glEnable(GL_COLOR_MATERIAL);{
			glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
			glMaterialf(GL_FRONT, GL_SHININESS, shininess);
			glColor3fv(diffuse);
			glTranslatef(pos[0], pos[1], pos[2]);
            glutSolidCube(radius);
			//glutSolidSphere(radius, 20, 20);
		}
		glDisable(GL_COLOR_MATERIAL);
	}
	glPopMatrix();
}

void Particle::stepSimulation(float dt){
	integrateVerlet(dt);
}

void Particle::clearForces(){
	forces[0] = 0;
	forces[1] = 0;
	forces[2] = 0;	 

	dragForce[0] = 0;
	dragForce[1] = 0;
	dragForce[2] = 0;
}

void Particle::addForce(float *force){
	forces[0] += force[0];
	forces[1] += force[1];
	forces[2] += force[2];

	dragForce[0] = forces[0];
	dragForce[1] = forces[1];
	dragForce[2] = forces[2];


	if (vecMagnitude(dragForce) > 1.0f){
		unitVector(dragForce);
	}

}

void Particle::integrateVerlet(float dt){
	// ToDo: complete here.
    forces[0] -= dragForce[0];
    forces[1] -= dragForce[1];
    forces[2] -= dragForce[2];
    
    float accel[3];
    accel[0] = forces[0] / mass;
    accel[1] = forces[1] / mass;
    accel[2] = forces[2] / mass;
    
    float posTemp[3];
    posTemp[0] = pos[0];
    posTemp[1] = pos[1];
    posTemp[2] = pos[2];
    
    pos[0] = 2.0f * pos[0] - oldPos[0] + accel[0] * dt * dt;
    pos[1] = 2.0f * pos[1] - oldPos[1] + accel[1] * dt * dt;
    pos[2] = 2.0f * pos[2] - oldPos[2] + accel[2] * dt * dt;
    
    oldPos[0] = posTemp[0];
    oldPos[1] = posTemp[1];
    oldPos[2] = posTemp[2];
}

void Particle::incrementAge(float time){
	age+=time;
}

bool Particle::inCollision(Particle* other){
	float r1 = radius;
	float r2 = other->radius;
	float x1 = pos[0];
	float x2 = other->pos[0];
	float y1 = pos[1];
	float y2 = other->pos[1];
	float z1 = pos[2];
	float z2 = other->pos[2];
	// ToDo: complete here.
    
    //Spheres
    /*
    float dx2 = x2 - x1;
    dx2 *= dx2;
    float dy2 = y2 - y1;
    dy2 *= dy2;
    float dz2 = z2 - z1;
    dz2 *= dz2;
    float dist = dx2 + dy2 + dz2;
    float sumR2 = r1 + r2;
    sumR2 *= sumR2;
    if (sumR2 >= dist) {
        return true;
    }
    return false;
     */
    
    ///Cubes
    float cube1Radius = (r1*1.73205)/3;
    float cube2Radius = (r2*1.73205)/3;
    float dx2 = x2 - x1;
    dx2 *= dx2;
    float dy2 = y2 - y1;
    dy2 *= dy2;
    float dz2 = z2 - z1;
    dz2 *= dz2;
    float dist = dx2 + dy2 + dz2;
    float sumR2 = cube1Radius +  cube2Radius;
    sumR2 *= sumR2;
    if (dist <= sumR2) {
        return true;
    }
    return false;
}

void Particle::checkFloorCollisions(){
	if(pos[1] < radius){
		pos[1] = radius;
		forces[1] = -restitutionCoefficient * forces[1];

		float dirX = pos[0] - oldPos[0];
		float dirZ = pos[2] - oldPos[2];

		float dX2 = dirX * dirX;
		float dZ2 = dirZ * dirZ;
		float mag = sqrt(dX2 + dZ2);
		
		dirX /= mag;
		dirZ /= mag;

		dragForce[0] = dirX;
		dragForce[1] = forces[1];
		dragForce[2] = dirZ;
		unitVector(dragForce);
	}
}
