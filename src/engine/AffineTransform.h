#ifndef AFFINETRANSFORM_H
#define AFFINETRANSFORM_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

using namespace std;

class AffineTransform{

public:

	AffineTransform();
	~AffineTransform();
	SDL_Point transformPoint(int x, int y);
	void translate(int x, int y);
	void rotate(double r);
	void scale(double x, double y);

	void concatenate(AffineTransform &at);

	double getScaleX();
	double getScaleY();
	//used for testing only
	void printMatrix();

private:
	double** transform;

	double** identity();
	void setRotate(double r);
	void cleanMatrix(double** m);



};

#endif
