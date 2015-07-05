#pragma once
#include <vector>
#include "algebra3.h"
class Map
{
private:
	std::vector<vec3>* vertexes;
	std::vector<float>* heights;
	std::vector<vec3>*  new_row_list;
	int row;		//how many rows in map.
	int col;		//how many columns in map.
	float x_dist;		//constant distance between points in x direction.
	float y_dist;		//constant distance between points in y direction.
	float max;
	float min;
	float red;
	float green;
	float blue;
	float frac;
	int draw_type;
	float snow;
public:
	void setSnow(float height);
	float getSnow(){ return snow; };
	void changeCoord(int x,int y,float height);
	float getMax(float h1, float h2, float h3, float h4);
	float getMin(float h1, float h2, float h3, float h4);
	Map();
	std::vector<vec3>* getMap();		//returns the set of vertices for the map.
	void fractalize();					//divides up vertices and returns new list of vertices.
	void setFrac(float f);
	void setSize(int row, int col,float x_dist,float y_dist);
	void createMap();
	vec3 getVertex(int row, int col);
	void setRange(float max, float min);
	float getHeights(int x,int y);
	void setColor(float r, float g, float b);
	void setType(int type);
	int getRow(){ return row; };
	int getCol(){ return col; };
	vec3 getColors(){ return vec3(red, green, blue); }; \
	int getType(){ return draw_type; };
};