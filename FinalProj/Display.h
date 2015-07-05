#ifndef DISPLAY_H
#define DISPLAY_H
#include <Fl/Fl_Window.H>
#include <Fl/Fl_Hold_Browser.H>
#include <Fl/Fl_Button.H>
#include <Fl/Fl_Value_Slider.H>
#include <Fl/Fl_Value_Input.H>
#include <FL/Fl_Color_Chooser.H>
#include <FL/Fl_Round_Button.H>
#include <FL/Fl_Slider.H>
#include "GLWindow.h"
#include "algebra3.h"
#include "Map.h"

class Controller;	// forward declaration

class Display: public Fl_Window{
private:
	GLWindow* win;				// the OpenGL window
	Controller* m;				// pointer back to the controller
	Fl_Value_Input* row;
	Fl_Value_Input* col;
	Fl_Value_Input* x_dist;
	Fl_Value_Input* y_dist;
	Fl_Value_Input* snow;
	Fl_Button* create;
	Fl_Button* sub;
	Map* map;
	Fl_Value_Input* high;
	Fl_Value_Input* low;
	Fl_Round_Button* solid;
	Fl_Round_Button* mesh;
	Fl_Round_Button* both;
	Fl_Color_Chooser* color;
	Fl_Value_Input* fractal;
	Fl_Button* up;
	Fl_Button* down;
	Fl_Button* left;
	Fl_Button* right;
	Fl_Slider* h;
	Fl_Button* top_view;
	Fl_Button* side_view;
	float max;
	float min;
public:
	int r;		//how many rows in map.
	int c;		//how many columns in map.
	float x;		//constant distance between points in x direction.
	float y;		//constant distance between points in y direction.
	int tile_x;
	int tile_y;
	Display(int x, int y, int w, int h, Controller* c);				// constructor
	void updateBrowser();											// update the browser
	void updateDrawing(){win->redraw();}							// redraw the OpenGL window
	const int numPolys();											// get the number of faces
	mat4 getPoly(int i);											// get a face
	Map* getMap(){ return map; };
	GLWindow* getGWin(){ return win; };

	static void topCB(Fl_Button* w, Display* d);
	static void sideCB(Fl_Button* w, Display* d);
	static void snowCB(Fl_Value_Input* w, Display* c);
	static void hCB(Fl_Slider* s, Display* d);
	static void upCB(Fl_Button* w, Display* d);
	static void downCB(Fl_Button* w, Display* d);
	static void leftCB(Fl_Button* w, Display* d);
	static void rightCB(Fl_Button* w, Display* d);
	static void fracCB(Fl_Value_Input* w, Display* c);
	static void solidCB(Fl_Round_Button* b, Display* d);
	static void meshCB(Fl_Round_Button* b, Display* d);
	static void bothCB(Fl_Round_Button* b, Display* d);
	static void colorCB(Fl_Color_Chooser* color, Display* d);
	static void maxCB(Fl_Value_Input* w, Display* c);
	static void minCB(Fl_Value_Input* w, Display* c);
	static void subCB(Fl_Button* w, Display* c);
	static void rowCB(Fl_Value_Input* w,Display* d);
	static void colCB(Fl_Value_Input* w, Display* d);
	static void xCB(Fl_Value_Input* w, Display* d);
	static void yCB(Fl_Value_Input* w, Display* d);
	static void createCB(Fl_Button* w, Display* d);
};


#endif
