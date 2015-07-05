#ifndef GL_WINDOW_H
#define GL_WINDOW_H 
#include <Fl/Fl_Gl_Window.H>
#include <Fl/Gl.H>
#include <GL/glu.h>
#include <Fl/Fl.H>
#include <iostream>
#include "camera.h"
#include "Map.h"
class GLWindow : public Fl_Gl_Window{
	private:
		int horiz,vert;
		bool click;
		Camera* c;					// a pointer to the camera
		void init();				// initialize the required OpenGL transforms
		void draw();				// draw the faces in the OpenGL window
		int handle(int event);		// handle keyboard events
		Map* map;
		bool mesh;
		bool solid;
		int x;
		int y;
	public:
		void drawVertex(float x,float y,float z,float snow,float r,float g,float b,int loop_x,int loop_y,bool mode);
		void setMap(Map* m);		//sets the map to gfx window.
		void setColor(int x, int y);
		GLWindow(int x, int y, int w, int h); 
		Camera* getCam();
		void setCam(Camera* c);
};

#endif