#include "camera.h"

Camera::Camera(float r, float phi, float theta){
	rot = identity3D();
	up = vec4(0, 1, 0, 1);
	eye = vec4(0, 0, r, 1);
	//increasePhi(5);
	//increaseTheta(15);
}

void Camera::increasePhi(float inc){
	rot = rot * rotation3D(vec3(0, 1, 0), inc);
}

void Camera::increaseTheta(float inc){
	rot = rot * rotation3D(vec3(1, 0, 0), inc);
}
mat4 Camera::getRot()
{
	return rot;
}
void Camera::increaseRad(float inc){
	eye[2] = eye[2] + inc;
}

vec4 Camera::getEye(){
	return rot * eye;
}

vec4 Camera::getUp(){
	return rot * up;
}

void Camera::setPhi(float inc)
{
	rot = rotation3D(vec3(0, 1, 0), inc);
}
void Camera::setTheta(float inc)
{
	rot = rotation3D(vec3(1, 0, 0), inc);
}