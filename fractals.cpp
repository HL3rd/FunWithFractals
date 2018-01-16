// fractals.cpp
// Horacio Lopez
// Section 02
// This program displays fractal programs at the users' selection of 1-8 or quits at q

#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <math.h>
#include "gfx.h"

using namespace std;

void cantor(int x, int y, float len);
void printTriangle(int x1, int y1, int x2, int y2, int x3, int y3);
void printSquare(int x1, int y1, float r, float theta);
void sierpinski(int x1, int y1, int x2, int y2, int x3, int y3);
void shrinkingSquare(int x1, int y1, float r, float shrink, float theta);
void spiralSquares(int x1, int y1, float r, float theta, float theta_r);
void circularLace(int x1, int y1, float r, float theta);
void snowflake(int x1, int y1, float r, float theta);
void tree(int x1, int y1, float r, float theta);
void fern(int x1, int y1, float r, float theta, int count);
void spirals(int x1, int y1, float r, float theta);

int main()
{
	int wd = 800, ht = 800;
	int margin; // margin to never touch edge
	float pi = 3.14159; // pi definition
	float theta, r, theta_left;

	gfx_open(wd, ht, "Fractals.cpp");
	gfx_color(255, 255, 255);

	while(true) {
		char c = gfx_wait(); // character selected by user
		int x1, y1, x2, y2, x3, y3, x4, y4;
		switch (c) {
			case 49:
				gfx_clear();
				margin = 20;
				x1 = margin;
				y1 = margin;
				x2 = wd - margin;
				y2 = margin;
				x3 = wd / 2;
				y3 = ht - margin;
				sierpinski(x1, y1, x2, y2, x3, y3);
				break;
			case 50:
				gfx_clear();
				x1 = wd / 2;
				y1 = ht / 2; // staring center
				shrinkingSquare(x1, y1, 400, 0.48, pi/4); // x1, y1, r, shrink, theta
				break;
			case 51:
				gfx_clear();
				x1 = wd / 2;
				y1 = ht / 2;
				theta = pi/4;
				spiralSquares(x1, y1, 1, theta, pi/6); // x1, y1, r, theta, theta_r
				break;
			case 52:
				gfx_clear();
				x1 = wd / 2;
				y1 = ht / 2;
				circularLace(x1, y1, 650, 0.0); // x1, y1, r, theta
				break;
			case 53:
				gfx_clear();
				x1 = wd / 2;
				y1 = ht / 2;
				snowflake(x1, y1, 600, (2*pi)/5); // x1, y1, r, theta
				break;
			case 54:
				gfx_clear();
				x1 = wd / 2;
				y1 = 795;
				pi = 3.14159;
				tree(x1, y1, 300, (pi/2)); // x1, y1, r, theta
				break;
			case 55:
				gfx_clear();
				x1 = wd / 2;
				y1 = 795;
				fern(x1, y1, 120, (pi/2), 3); // x1, y1, r, theta, count
				break;
			case 56:
				gfx_clear();
				x1 = wd /2;
				y1 = ht /2;
				pi = 3.14159;
				spirals(x1, y1, 1250, pi/6);
				break;
			case 'q':
				return 0;
				break;
			default:
				break;
		}
	}

	return 0;
}


void printTriangle(int x1, int y1, int x2, int y2, int x3, int y3)
{
	gfx_line(x1, y1, x2, y2);
	gfx_line(x2, y2, x3, y3);
	gfx_line(x3, y3, x1, y1);
}

void printSquare(int x1, int y1, float r, float theta)
{
	float pi = 3.14159;
	float theta_i = pi/2; // increment of 90
	
	for (float i = theta; i < 2*pi; i += theta_i) { 
		gfx_line(x1 + r*cos(i), y1 + r*sin(i), x1 + r*cos(i + theta_i), y1 + r*sin(i + theta_i));
	}

}


void sierpinski(int x1, int y1, int x2, int y2, int x3, int y3)
{
	if (abs(x2-x1) < 5) return; // base case

	// draw triangle
	printTriangle(x1, y1, x2, y2, x3, y3);

	// recursive calls
	sierpinski(x1, y1, (x1+x2)/2, (y1+y2)/2, (x1+x3)/2, (y1+y3)/2);
	sierpinski((x1+x2)/2, (y1+y2)/2, x2, y2, (x2+x3)/2, (y2+y3)/2);
	sierpinski((x1+x3)/2, (y1+y3)/2, (x2+x3)/2, (y2+y3)/2, x3, y3);
}

void shrinkingSquare(int x1, int y1, float r, float shrink, float theta)
{
	float pi = 3.14159;
	float theta_i = (pi/2); // increment of 90


	if (r < 2) return; // base case

	//FIX THIS PART	
	r = r * shrink; // decrease r
	shrink -= 0.01; // accelerates how fast the radius shrinks

	// draw triangle
	printSquare(x1, y1, r, theta);

	//recursive calls
	for (float i = (pi/4); i <= (7*pi/4); i += theta_i)
		shrinkingSquare(x1 + r*cos(i), y1 + r*sin(i), r, shrink, theta);
	
	
}

// THIS ONE
void spiralSquares(int x1, int y1, float r, float theta, float theta_r)
{
	float pi = 3.14159;
	float theta_i = pi/6; // increment for theta of rotation

	if (r > 150) return; // base case

	printSquare(x1, y1, r, theta);

	spiralSquares(x1 + 2*r*cos(theta_r), y1 + 2*r*sin(2*pi - theta_r), r + (r/8), theta, theta_r +pi/6);
}

void circularLace(int x1, int y1, float r, float theta) 
{
	float pi = 3.14159;
	float theta_i = pi/3;

	if (r < 1) return; // base case
	
	r =  r /3; // shrinking r
	
	gfx_circle(x1, y1, r);

	for (float i = theta; i < 2*pi; i += theta_i) {
		circularLace(x1 + r*cos(i), y1 + r*sin(i), r, theta);
	}

}

void snowflake(int x1, int y1, float r, float theta)
{
	float pi = 3.14159;

	if (r < 1) return; // base case

	r = r/3; // shrinking line length

	// increment by (2*pi)/5
	for (float i = pi/2; i < (5*pi)/2; i += theta) {
		gfx_line(x1, y1, x1 + r*cos(i), y1 + r*sin(i));
		snowflake(x1 + r*cos(i), y1 + r*sin(i), r, theta);
	}
}

void tree(int x1, int y1, float r, float theta)
{
	float pi = 3.14159;

	int x2 = x1 + r*cos(theta);
	int y2 = y1 - r*sin(theta);

	gfx_line(x1, y1, x2, y2);

	if (r < 1) return; // base case
	r = r * 0.628; // shrinking r

	// recursive calls
	tree(x2, y2, r, theta-(pi/6)); // to the right
	tree(x2, y2, r, theta+(pi/6)); // to the left
	
}

void fern(int x1, int y1, float r, float theta, int count)
{
	float pi = 3.14159;
	if (r < 1) return; // base case

	gfx_line(x1, y1, x1 + r*cos(theta), y1 - r*sin(theta));	

	if (count != 0)
		fern(x1 + r*cos(theta), y1 - r*sin(theta), r, theta, count-1);

	count = 3;

	// recursive calls		
	fern(x1 + r*cos(theta), y1 - r*sin(theta), r/3, theta + (pi/6), count);
	fern(x1 + r*cos(theta), y1 - r*sin(theta), r/3, theta - (pi/6), count);


}

void spirals(int x1, int y1, float r, float theta)
{
	float pi = 3.14159;

	if (r < 2) return; // base case

	// recursive calls
	int x2 = x1 + r*cos(theta);
	int y2 = y1 - r*sin(theta);

	gfx_point(x2, y2); // plot points

	// recursive calls
	spirals(x2, y2, r/3, theta - (pi/5));
	spirals(x1, y1, r/1.1, theta - (pi/5));

}
