#include "Display.h"
#include "eController.h"

Display::Display(int x, int y, int w, int h, Controller* m):Fl_Window(x, y, w, h, "Fractalizer"){
		this->m = m;
		this->tile_x = 0;
		this->tile_y = 0;
		map = new Map();
		win = new GLWindow(0, 0, 4 * w / 6.5, h);

		high = new Fl_Value_Input(600, 175, 30, 20, "Max");
		high->value(0.9);
		max = 0.9;
		low = new Fl_Value_Input(680, 175, 30, 20, "Min");
		low->value(0.1);
		min = 0.1;
		row = new Fl_Value_Input(550,10,50,20,"Row");
		row->value(6);
		this->r = 6;
		col = new Fl_Value_Input(630,10,50,20,"Col");
		col->value(6);
		this->c = 6;
		x_dist = new Fl_Value_Input(550,40,35,20,"x_dist");
		x_dist->value(0.75);
		this->x = 0.75;
		y_dist = new Fl_Value_Input(650,40,35,20,"y_dist");
		y_dist->value(0.75);
		this->y = 0.75;
		create = new Fl_Button(600,75,100,30,"Create Mesh");
		sub = new Fl_Button(650,120,100,30,"Fractalize");
		mesh = new Fl_Round_Button(660, 210, 64, 15, "Mesh");
		mesh->type(FL_RADIO_BUTTON);
		solid = new Fl_Round_Button(660, 230, 64, 15, "Solid");
		solid->type(FL_RADIO_BUTTON);
		both = new Fl_Round_Button(660, 250, 64, 15, "Both");
		both->type(FL_RADIO_BUTTON);
		color = new Fl_Color_Chooser(550, 230, 110, 100, "ColorChooser");
		fractal = new Fl_Value_Input(550, 120, 50, 20, "Fractal");
		fractal->value(0.25);
		this->map->setFrac(fractal->value());
		up = new Fl_Button(600, 375, 30, 30, "up");
		down = new Fl_Button(600, 410, 35, 30, "down");
		left = new Fl_Button(560, 400, 35, 30, "left");
		right = new Fl_Button(640, 400, 35, 30, "right");
		this->h = new Fl_Slider(520, 400, 35, 80, "height");
		this->snow = new Fl_Value_Input(600, 350, 50, 20, "Snow Height");
		this->snow->value(0.8);
		this->map->setSnow(0.8);
		this->top_view = new Fl_Button(600, 500, 75, 30, "Top View");
		this->side_view = new Fl_Button(520, 500, 75, 30, "Side View");

		this->top_view->callback((Fl_Callback*) topCB, this);
		this->side_view->callback((Fl_Callback*)sideCB, this);
		this->snow->callback((Fl_Callback*)snowCB, this);
		this->h->callback((Fl_Callback*)hCB, this);
		up->callback((Fl_Callback*)upCB, this);
		right->callback((Fl_Callback*)rightCB, this);
		left->callback((Fl_Callback*)leftCB, this);
		down->callback((Fl_Callback*)downCB, this);
		fractal->callback((Fl_Callback*)fracCB, this);
		color->callback((Fl_Callback*)colorCB, this);
		mesh->callback((Fl_Callback*)meshCB, this);
		solid->callback((Fl_Callback*)solidCB, this);
		both->callback((Fl_Callback*)bothCB, this);
		high->callback((Fl_Callback*)maxCB, this);
		low->callback((Fl_Callback*)minCB, this);
		sub->callback((Fl_Callback*)subCB, this);
		row->callback((Fl_Callback*)rowCB, this);
		col->callback((Fl_Callback*)colCB, this);
		x_dist->callback((Fl_Callback*)xCB, this);
		y_dist->callback((Fl_Callback*)yCB, this);
		create->callback((Fl_Callback*)createCB, this);
}

void Display::snowCB(Fl_Value_Input* w, Display* c)
{
	Map* m = c->getMap();
	m->setSnow(w->value());
	GLWindow* win = c->getGWin();
	win->setMap(m);
	win->redraw();
}

void Display::hCB(Fl_Slider* s, Display* d)
{
	s->range(d->min, d->max);
	Map* m = d->getMap();
	m->changeCoord(d->tile_x, d->tile_y, s->value());
	float height = m->getHeights(d->tile_x, d->tile_y);
	s->value(height);
	GLWindow* win = d->getGWin();
	win->setMap(m);
	win->redraw();
}

void Display::upCB(Fl_Button* w, Display* d)
{
	Map* m = d->getMap();
	GLWindow* win = d->getGWin();
	//std::cout << d->tile_x <<d->tile_y<< std::endl;
	if (d->tile_y == 0)
		d->tile_y = m->getRow()-1;
	else
		d->tile_y--;
	win->setColor(d->tile_x, d->tile_y);
	win->redraw();
}
void Display::downCB(Fl_Button* w, Display* d)
{
	Map* m = d->getMap();
	GLWindow* win = d->getGWin();
	//std::cout << d->tile_x << d->tile_y << std::endl;
	if (d->tile_y == m->getRow() - 1)
		d->tile_y = 0;
	else
		d->tile_y++;
	win->setColor(d->tile_x, d->tile_y);
	win->redraw();
}
void Display::leftCB(Fl_Button* w, Display* d)
{
	Map* m = d->getMap();
	GLWindow* win = d->getGWin();
	//std::cout << d->tile_x <<d->tile_y<< std::endl;
	if (d->tile_x == 0)
		d->tile_x = m->getCol() - 1;
	else
		d->tile_x--;
	win->setColor(d->tile_x, d->tile_y);
	win->redraw();
}
void Display::rightCB(Fl_Button* w, Display* d)
{
	Map* m = d->getMap();
	GLWindow* win = d->getGWin();
	//std::cout << d->tile_x <<d->tile_y<< std::endl;
	if (d->tile_x == m->getCol() - 1)
		d->tile_x = 0;
	else
		d->tile_x++;
	win->setColor(d->tile_x, d->tile_y);
	win->redraw();
}

void Display::fracCB(Fl_Value_Input* w, Display* c)
{
	Map* m = c->getMap();
	m->setFrac(w->value());
}

void Display::solidCB(Fl_Round_Button* b, Display* d)
{
	Map* m = d->getMap();
	m->setType(1);
	GLWindow* win = d->getGWin();
	win->setMap(m);
	win->redraw();
}
void Display::meshCB(Fl_Round_Button* b, Display* d)
{
	Map* m = d->getMap();
	m->setType(0);
	GLWindow* win = d->getGWin();
	win->setMap(m);
	win->redraw();
}
void Display::bothCB(Fl_Round_Button* b, Display* d)
{
	Map* m = d->getMap();
	m->setType(2);
	GLWindow* win = d->getGWin();
	win->setMap(m);
	win->redraw();
}
void Display::colorCB(Fl_Color_Chooser* color, Display* d)
{
	Map* m = d->getMap();
	m->setColor(color->r(), color->g(), color->b());
	GLWindow* win = d->getGWin();
	win->setMap(m);
	win->redraw();
}
void Display::maxCB(Fl_Value_Input* w, Display* c){
	c->max = w->value();
}

void Display::minCB(Fl_Value_Input* w, Display* c){
	c->min = w->value();
}

void Display::rowCB(Fl_Value_Input* w, Display* c){
	c->r = w->value();
}

void Display::colCB(Fl_Value_Input* w, Display* c){
	c->c = w->value();
}

void Display::xCB(Fl_Value_Input* w, Display* c){
	c->x = w->value();
}

void Display::yCB(Fl_Value_Input* w, Display* c){
	c->y = w->value();
}

void Display::subCB(Fl_Button* w, Display* c)
{
	Map* m = c->getMap();
	//std::cout<<m->getHeights(0, 0) << std::endl;
	m->fractalize();
	//std::cout << m->getHeights(5, 4) << std::endl;
	GLWindow* win = c->getGWin();
	win->setMap(m);
	win->redraw();
}

void Display::createCB(Fl_Button* w, Display* c){
	Map* m = c->getMap();
	c->tile_x = c->tile_y = 0;
	m->setSize(c->r,c->c,c->x,c->y);
	//std::cout << c->max << std::endl;
	m->setRange(c->max, c->min);
	m->createMap();
	GLWindow* win = c->getGWin();
	win->setColor(c->tile_x, c->tile_y);
	win->setMap(m);
	win->redraw();
}

void Display::topCB(Fl_Button* w, Display* d)
{
	GLWindow* g = d->getGWin();
	Camera* c = g->getCam();
	c->setTheta(-70);
	g->setCam(c);
	g->redraw();
}
void Display::sideCB(Fl_Button* w, Display* d)
{
	GLWindow* g = d->getGWin();
	Camera* c = g->getCam();
	c->setPhi(4);
	g->setCam(c);
	g->redraw();
}