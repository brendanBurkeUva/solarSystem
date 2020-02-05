#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cmath>
#include "AffineTransform.h"
#include <iostream>


/**
 * Affine Transforms
 *
 * */
AffineTransform::AffineTransform(){
	transform = identity();
	//printMatrix();
}

AffineTransform::~AffineTransform(){
	cleanMatrix(transform);
}

void AffineTransform::cleanMatrix(double** m){
	for(int i=0; i<3; i++)
		delete m[i];
	delete m;
}

/* Returns the identity matrix as an array */
double** AffineTransform::identity(){
	double** id = new double*[3];
	for(int i=0; i<3; i++){
		id[i] = new double[3];
		for(int j=0; j<3; j++){
			if(i == j) id[i][j] = 1.0;
			else id[i][j] = 0.0;
		}
	}
	return id;
}

/* Takes a point in the local coordinate system and transforms it to global space given this AffineTransform */
SDL_Point AffineTransform::transformPoint(int x, int y){
	//TODO in future assignment
	int xtmp = (int)(x*transform[0][0] + y*transform[0][1] + transform[0][2]);
	int ytmp = (int)(x*transform[1][0] + y*transform[1][1] + transform[1][2]);
	//if (ytmp != y)
	//	std::cout << "Y has changed by" << ytmp - y << std::endl;
	//printMatrix();
	SDL_Point temp = {xtmp, ytmp};
	return temp;
}

/* Add another transform to this one, is basically just matrix multiply */
void AffineTransform::concatenate(AffineTransform &at){
	//TODO in future assignment
	double ** a = new double*[3];
	for (int i = 0; i <3; i++){
		a[i] = new double[3];
		for (int j = 0; j <3; j++){
			a[i][j] = transform[i][j];
			transform[i][j] = 0;
		}
	}
	double ** b = at.transform;
	for (int i = 0; i <3; i++){
		for (int j = 0; j <3; j++){
			for (int k = 0; k <3; k++){
				transform[i][j] += a[i][k]*b[k][j];
			}
		}
	}
}

/* Move points in the x and y direction */
void AffineTransform::translate(int x, int y){
	AffineTransform temp;
	for (int i = 0; i <3; i++){
		for (int j = 0; j <3; j++){
			if (i == j){
				temp.transform[i][j] = 1;
			}
			else if (i == 0 && j == 2){
				temp.transform[i][j] = x;
			}
			else if (i == 1 && j == 2){
				temp.transform[i][j] = y;
			}
			else{
				temp.transform[i][j] = 0;
			}
		}
	}
	//temp.printMatrix();
	this->concatenate(temp);
}

/* rotate points by r radians */
void AffineTransform::rotate(double r){
	//TODO in future assignment
	//atan2(transform[1][1],transform[0][0]);
	AffineTransform temp;
	temp.setRotate(r);
	this->concatenate(temp);
}

/* scale in the x and y direction accordingly */
void AffineTransform::scale(double x, double y){
	AffineTransform temp;
	for (int i = 0; i <3; i++){
		for (int j = 0; j <3; j++){
			if (i == 0 && j == 0){
				temp.transform[i][j] = x;
			}
			else if (i == 1 && j == 1){
				temp.transform[i][j] = y;
			}
			else if (i == 2 && j == 2){
				temp.transform[i][j] = 1;
			}
			else{
				temp.transform[i][j] = 0;
			}
		}
	}
	this->concatenate(temp);
}

double AffineTransform::getScaleX(){
	//TODO in future assignment
	return sqrt(transform[0][0]*transform[0][0] + transform[0][1]*transform[0][1]);
}

double AffineTransform::getScaleY(){
	//TODO in future assignment
	return sqrt(transform[1][0]*transform[1][0] + transform[1][1]*transform[1][1]);
}

void AffineTransform::setRotate(double r){
	transform[0][0] = cos(r);
	transform[0][1] = -1*sin(r);
	transform[0][2] = 0;
	transform[1][0] = sin(r);
	transform[1][1] = cos(r);
	transform[1][2] = 0;
	transform[2][0] = 0;
	transform[2][1] = 0;
	transform[2][2] = 1;
}

void AffineTransform::printMatrix(){
	std::cout << "[";
	for (int i = 0; i <3; i++){
		for (int j = 0; j <3; j++){
			std::cout << " " << transform[i][j];
			if (j == 2 && i != 2)
				std::cout << std::endl;
		}
	}
	std::cout << "]" << std::endl;
}
