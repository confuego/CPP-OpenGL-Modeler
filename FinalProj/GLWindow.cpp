#include "GLWindow.h"
#include "Display.h"
#include "algebra3.h"

GLWindow::GLWindow(int x, int y, int w, int h) : Fl_Gl_Window(x, y, w, h){
	horiz = vert = 0;
	this->x = this->y = 0;
	click = false;
	c= new Camera(4, 0, 0);	// create a camera
	map = new Map();
}

void GLWindow::init(){	// initialize the required OpenGL transforms
	glViewport(0, 0, w(), h());
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90, 1, 0.1, 10);		// experiment with these settings to see their effects
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClearColor(0.2, 0.2, 0.2, 0.8);
	glEnable(GL_DEPTH_TEST);
}

Camera* GLWindow::getCam()
{
	return c;
}

void GLWindow::setMap(Map* m)
{
	this->map = m;
}
void GLWindow::setColor(int x, int y)
{
	this->x = x;
	this->y = y;
}

void GLWindow::setCam(Camera* c)
{
	this->c = c;
}

void GLWindow::draw()
{
	if (!valid()){
		init();				// make sure the OpenGL settings are completed once before drawing
		valid(1);
	}
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	gluLookAt(c->getEye()[0], c->getEye()[1], c->getEye()[2],	// set the camera
		0, 0, 0,
		c->getUp()[0], c->getUp()[1], c->getUp()[2]);

	int type = this->map->getType();
	if (type == 0)
	{
		mesh = true;
		solid = false;
	}
	else if (type == 1)
	{
		solid = true;
		mesh = false;
	}
	else if (type == 2)
	{
		mesh = true;
		solid = true;
	}
	std::vector<vec3> v = (*map->getMap());
	vec3 color = map->getColors();
	float snow = map->getSnow();
	for (int x = 0; (x + 1) < map->getCol(); x++)
	{
		for (int y = 0; (y + 1) < map->getRow(); y++)
		{
			vec3 top_left = map->getVertex(x, y);
			vec3 top_right = map->getVertex(x, y + 1);
			vec3 bottom_left = map->getVertex(x + 1, y);
			vec3 bottom_right = map->getVertex(x + 1, y + 1);
			//draw two triangles for each quad.
			if (solid)
			{
				glBegin(GL_TRIANGLES);
				drawVertex(top_left[0], top_left[1], top_left[2], snow, color[0], color[1], color[2],x,y,true);
				drawVertex(bottom_left[0], bottom_left[1], bottom_left[2], snow, color[0], color[1], color[2],x+1,y,true);
				drawVertex(top_right[0], top_right[1], top_right[2], snow, color[0], color[1], color[2],x,y+1,true);

				drawVertex(bottom_left[0], bottom_left[1], bottom_left[2], snow, color[0], color[1], color[2],x+1,y,true);
				drawVertex(bottom_right[0], bottom_right[1], bottom_right[2], snow, color[0], color[1], color[2],x+1,y+1,true);
				drawVertex(top_right[0], top_right[1], top_right[2], snow, color[0], color[1], color[2],x,y+1,true);
				glEnd();
			}
			if (mesh)
			{
				glBegin(GL_LINE_LOOP);
				drawVertex(top_left[0], top_left[1], top_left[2], snow, 0, 0, 0, x, y, false);
				drawVertex(bottom_left[0], bottom_left[1], bottom_left[2], snow, 0, 0, 0, x + 1, y, false);
				drawVertex(top_right[0], top_right[1], top_right[2], snow, 0, 0, 0, x, y + 1, false);

				drawVertex(bottom_left[0], bottom_left[1], bottom_left[2], snow,0, 0, 0, x + 1, y, false);
				drawVertex(bottom_right[0], bottom_right[1], bottom_right[2], snow, 0, 0, 0, x + 1, y + 1, false);
				drawVertex(top_right[0], top_right[1], top_right[2], snow, 0, 0, 0, x, y + 1, false);
				glEnd();
			}
		}
	}

}


void GLWindow::drawVertex(float x, float y, float z,float snow,float r,float g,float b,int loop_x,int loop_y,bool mode)
{
	if (this->x == loop_x&&this->y == loop_y)
	{
		glColor3f(1, 1, 0);
	}
	else
	{
		if (y >= snow&&mode ==true)
		{
			glColor3f(1, 1, 1);
		}
		else
			glColor3f(r, g, b);
	}
	glVertex3f(x, y, z);
}

int GLWindow::handle(int event){		// handle keyboard events
	//std::cout << event << std::endl;
	if (event == FL_PUSH)
	{
		if (Fl::event_button()==FL_LEFT_MOUSE)
			click = true;
		return 1;
	}
	if (event == FL_RELEASE)
	{
		if (Fl::event_button() == FL_LEFT_MOUSE)
			click = false;
		return 1;
	}
	if (event == FL_KEYUP){				// when the key is released, check for an event and handle it
		if (Fl::event_key() == 'a'){
			c->increasePhi(-7);
			redraw();
		}
		if (Fl::event_key() == 'd'){
			c->increasePhi(7);
			redraw();
		}
		if (Fl::event_key() == 'w'){
			c->increaseTheta(-7);
			redraw();
		}
		if (Fl::event_key() == 's'){
			c->increaseTheta(7);
			redraw();
		}
		if (Fl::event_key() == 'e'){
			c->increaseRad(-.5);					
			redraw();
		}
		if (Fl::event_key() == 'f'){
			c->increaseRad(.5);					
			redraw();
		}
		return 1;
	}
	if (event == FL_MOUSEWHEEL)
	{
		if (Fl::event_dy()==-1)
		{
			std::cout << "Decrease Mouse Wheel" << std::endl;
			c->increaseRad(.5);
			redraw();
		}
		if (Fl::event_dy() == 1)
		{
			std::cout << "Increase Mouse Wheel" << std::endl;
			c->increaseRad(-.5);
			redraw();
		}
		return 1;
	}
	if (event== FL_DRAG)//event == FL_MOVE && click == true)
	{
		if (vert == 0)
			vert = Fl::event_y();
		if (horiz == 0)
			horiz = Fl::event_x();
		c->increaseTheta(vert - Fl::event_y());
		c->increasePhi(horiz - Fl::event_x());
		vert = Fl::event_y();
		horiz = Fl::event_x();
		redraw();
		return 1;
	}
	return Fl_Gl_Window::handle(event);
}