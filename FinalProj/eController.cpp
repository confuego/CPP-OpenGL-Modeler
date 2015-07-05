#include "eController.h"
#include <iostream>

Controller::Controller(){	
	// Create a cube
	/*faces.push_back(new Face(vec3(-1, 1, -1), vec3(-1, -1, -1), vec3(1, -1, -1), vec3(1, 1, -1))); // order is important
	faces.push_back(new Face(vec3(-1, 1, 1), vec3(-1, 1, -1), vec3(1, 1, -1), vec3(1, 1, 1)));
	faces.push_back(new Face(vec3(1, 1, 1), vec3(1, 1, -1), vec3(1, -1, -1), vec3(1, -1, 1)));
	faces.push_back(new Face(vec3(-1, -1, 1), vec3(-1, 1, 1), vec3(1, 1, 1), vec3(1, -1, 1)));
	faces.push_back(new Face(vec3(-1, -1, -1), vec3(-1, -1, 1), vec3(1, -1, 1), vec3(1, -1, -1)));
	faces.push_back(new Face(vec3(-1, 1, -1), vec3(-1, 1, 1), vec3(-1, -1, 1), vec3(-1, -1, -1)));*/
	//parser("sampleInput.txt", &faces);		// Will load a model from a file
	selected = 0;								// Start with the zero-ith face selected
	d = new Display(10, 10, 800, 600, this);	// Create a new display window
	d->show();									// Show the window
}

Controller::~Controller(){};

void Controller::select(int i){								// Set the selected face
	selected = i;// d->updateDrawing();
}
