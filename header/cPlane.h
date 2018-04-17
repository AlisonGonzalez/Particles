
#ifndef __PLANE_H__
#define __PLANE_H__


class cPlane 
{
public:
	cPlane(int w, int h);
	~cPlane ();
	void display (int stepSize, float *color);
private:
	int  m_w, m_h;
	float specularMat0[3],shine;
};

#endif __PLANE_H__