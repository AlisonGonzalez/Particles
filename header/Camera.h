#ifndef __camera
#define __camera

//#include "glh_linear.h"

//using namespace glh;

#define		CAMERA_INSIDE			true
#define		CAMERA_OUTSIDE			false

#include "vecs.h"

//class VisibilityMap;

class Camera{
public:
	Camera();

	void init();
	//void initVisibility(int res);

	void setPos(float x, float y, float z);
	void setDirVec(float x, float y, float z);
	void setUpVec(float x, float y, float z);
	void setPivot(float x, float y, float z);

	void moveForward(float dist);
	void moveBackward(float dist);
	void moveRight(float dist);
	void moveLeft(float dist);
	void moveUp(float dist);
	void moveDown(float dist);

	void setView();
	//void updateVisibility();

	static Camera *getCurrentCamera();
	static Camera *getCameraAt(int index);
	static Camera *getNextCamera();
	static int getNumCameras();
	static void reset();


	void setAgentCamera(float *pos, float dir, float height);

	void move(float dir, float angle);
	void rotate(float angle, float x, float y, float z);
	void moveAround(float angle, float x, float y, float z);
	void getWorldFrustumCoords(float *coords);
	void calcUnitVectors();
	void draw();
	void readMatrices();

	void normalize(float *p);
	void updatePlanes (float *X, float *Y, float *Z, float &ratio_);
	bool pointInFrustum(float* p);
	float X[3], Y[3], Z[3];
	float ratio, tang;
	float dir[3];
	float up[3];
	//VisibilityMap *visMap;

	float pos[3];

	float pivot[3];
	float near_plane;
	float far_plane;
	float fov;
	float projectionMatrix[16];
	float modelviewMatrix[16];
//	float modelviewProjectionMatrix[16];
	char name[32];
};

#endif