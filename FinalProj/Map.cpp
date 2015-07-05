#include "Map.h"
#include <iostream>

Map::Map()
{
	this->vertexes = new std::vector<vec3>();
	this->heights = new std::vector<float>();
	this->new_row_list = new std::vector<vec3>();
	frac = 0;
}

void Map::createMap()
{
	this->vertexes->clear();
	this->heights->clear();
	float current_x = -((row/2.0)*x_dist);
	float current_y = -((col / 2.0)*y_dist);
	for (int x = 0; x < row; x++)
	{
		for (int y = 0; y < col; y++)
		{
			//std::cout << "<" << current_x << "," << current_y << ">" << std::endl;
			float height = min + ((max - min) *  ((rand() % 100) / 100.0f));
			//std::cout << height << std::endl;
			heights->push_back(height);// saves it for when you fractalize later.
			vertexes->push_back(vec3(current_x, height, current_y));// there is no height for the initial mesh, so it's set to 0.
			current_y = current_y + y_dist;// change y by a contant amount.
		}
		current_y = -((col / 2.0)*y_dist);
		current_x = current_x + x_dist;	// change x by a contant amount.
	}
	std::cout << std::endl;
}

vec3 Map::getVertex(int r, int c)
{
	return (*vertexes)[r*(col)+c];
}

float Map::getHeights(int r, int c)
{
	return (*heights)[r*(col)+c];
}

void Map::setRange(float max, float min)
{
	this->max = max;
	this->min = min;
}

void Map::setSize(int row,int col, float x_dist,float y_dist)
{
	this->row = row;
	this->col = col;
	this->x_dist = x_dist;
	this->y_dist = y_dist;
}

void Map::fractalize()
{
	this->vertexes->clear();

	float current_x = -((row/2.0)*x_dist);
	float current_y = -((col / 2.0)*y_dist);

	float half_x_dist = x_dist / 2.0;
	float half_y_dist = y_dist / 2.0;

	float next_col_height = 0;
	std::vector<float>* new_heights = new std::vector<float>();

	for (int x = 0; x < row; x++)
	{
		//std::cout << std::endl;
		for (int y = 0; y < col; y++)
		{
			//std::cout << "<" << x << "," << y << ">" << std::endl;
			float current_height = this->getHeights(x, y);
			//std::cout << current_height << std::endl;
			this->vertexes->push_back(vec3(current_x, current_height, current_y));
			new_heights->push_back(current_height);
			if ((y+1)<col)
			{
				float next_col_height = this->getHeights(x, y + 1);
				float frac = ((((rand() % 100) / 100.0f)*2.0f) - 1.0f)*(this->frac*abs(current_height - next_col_height));
				this->vertexes->push_back(vec3(current_x, frac+((current_height + next_col_height) / 2.0), current_y + half_y_dist));
				new_heights->push_back((current_height + next_col_height) / 2.0);
			}
			if ((x + 1) < row)
			{
				float next_row_height = this->getHeights(x + 1, y);
				float frac = ((((rand() % 100) / 100.0f)*2.0f) - 1.0f)*(this->frac*abs(next_row_height - current_height));
				this->new_row_list->push_back(vec3(current_x + half_x_dist,frac +((next_row_height + current_height) / 2.0), current_y));
			}
			if ((x + 1) < row && (y + 1) < col)
			{
				float frac = ((((rand() % 100) / 100.0f)*2.0f) - 1.0f)*(this->frac*abs(getMax(current_height,this->getHeights(x, y + 1),this->getHeights(x + 1, y),this->getHeights(x + 1, y + 1))-getMin(current_height,this->getHeights(x, y + 1),this->getHeights(x + 1, y),this->getHeights(x + 1, y + 1))));
				this->new_row_list->push_back(vec3(current_x + half_x_dist, frac + ((current_height + this->getHeights(x, y + 1) + this->getHeights(x + 1, y) + this->getHeights(x + 1, y + 1)) / 4.0), current_y + half_y_dist));
			}
			//std::cout << "<" << current_x << "," << current_y << ">" << std::endl;

			current_y = current_y + (y_dist);// change y by a contant amount.

		}
		for (int x = 0; x < new_row_list->size(); x++)
		{
			vec3 v = (*new_row_list)[x];
			//std::cout << "<" << v[0] << "," << v[1] << "," << v[2] << ">" << std::endl;
			new_heights->push_back(v[1]);
			this->vertexes->push_back(v);
		}
		current_y = -((col / 2.0)*y_dist);
		current_x = current_x + (x_dist);	// change x by a contant amount.
		new_row_list->clear();
	}
	row = (row * 2)-1;
	col = (col * 2)-1;
	x_dist = half_x_dist;
	y_dist = half_y_dist;
	heights = new_heights;
}

float Map::getMax(float h1, float h2, float h3, float h4)
{
	float max= h1;
	if (h2 > h1)
		max = h2;
	if (h3 > max)
		max = h3;
	if (h4 > max)
		max = h4;
	return max;
}

float Map::getMin(float h1, float h2, float h3, float h4)
{
	float min = h1;
	if (h2 < h1)
		min = h2;
	if (h3 < min)
		min = h3;
	if (h4 < min)
		min = h4;
	return min;
}

std::vector<vec3>* Map::getMap()
{
	return this->vertexes;
}

void Map::setColor(float r, float g, float b)
{
	this->red = r;
	this->blue = b;
	this->green = g;
}

void Map::setType(int type)
{
	this->draw_type = type;
}

void Map::setFrac(float frac)
{
	this->frac = frac;
}

void Map::changeCoord(int x, int y, float height)
{
	(*heights)[x*(row)+y] = height;
	(*vertexes)[x*(row)+y][1] = height;

}

void Map::setSnow(float height)
{
	this->snow = height;
}

