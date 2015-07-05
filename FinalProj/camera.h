#include <math.h>
#include "algebra3.h"
#include "algebra3.h"
#include <iostream>

// A class for storing camera transforms
class Camera{
	private:
		mat4 rot;			// Current rotation matrix 
		vec4 up;				// Current up vector
		vec4 eye;			// Current eye/camera position
	public:
		Camera(float r, float phi, float theta); 
		void increasePhi(float inc);		// increase the phi angle. Note a negative value will decrease it. 
		void increaseTheta(float inc);		// increase the theta angle
		void increaseRad(float inc);		// increase the radius
		vec4 getEye();		// get the current eye position
		vec4 getUp();		// get the current up vector
		mat4 getRot();		// returns the current rotation matrix.
		void setPhi(float inc);
		void setTheta(float inc);
};