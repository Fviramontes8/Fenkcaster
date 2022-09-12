#include <iostream>
#include <cmath>
#include "GL/gl.h" 
#include "GL/glu.h"
#include "GL/glut.h"

#include "../include/fenkcaster/draw_shapes.hpp"
#include "../include/fenkcaster/player.hpp"

#define WIDTH 1024
#define HEIGHT 512

#define TWO_PI 2*M_PI
#define HALF_PI M_PI/2.0
#define THREE_HALF_PI 3 * M_PI/2.0

#define ONE_DEG 0.0174533
#define HALF_DEG 0.0174533/2.0
#define THIRTY_DEG M_PI/6.0

int map_x, map_y, map_size;

const int game_map[] = {
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 1, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 1, 0, 1, 0, 0, 1,
	1, 0, 1, 0, 0, 0, 0, 1,
	1, 0, 1, 0, 0, 0, 0, 1,
	1, 1, 1, 1, 1, 1, 1, 1
};

void draw_map() {
	int x, y;
	for (y=0; y<map_y; ++y) {
		for (x=0; x<map_x; ++x) {
			// Chooses color of square
			if (game_map[(y * map_x) + x] > 0) {
				glColor3f(1, 1, 1);
			}
			else {
				glColor3f(0, 0, 0);
			}

			const int x_offset = x * map_size;
			const int y_offset = y * map_size;

			// Draw square
			fenk_gl::draw_quad_with_border(
				x_offset, 
				y_offset, 
				map_size, 
				map_size
			);
		}
	}
}

// float player_x, player_y, player_degree_x, player_degree_y, player_angle;

fenk_gl::Player player(100, 100, THIRTY_DEG); 

void draw_player() {
	// Draw player as a smol square dot
	glColor3f(1, 0 ,1);
	glPointSize(8);
	glBegin(GL_POINTS);
	glVertex2i(player.x(), player.y());
	glEnd();

	/*
	glLineWidth(3);
	glBegin(GL_LINES);
	glVertex2i(player_x, player_y);
	glVertex2i(
		player_x + (player_degree_x * 5),
		player_y + (player_degree_y * 5)
	);
	glEnd();
	*/
}

float distance(float x1, float y1, float x2, float y2) {
	return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

void draw_rays_3D() {
	int r, mx, my, mp, dof;
	float hray_x, hray_y, ray_angle;
	float vray_x, vray_y;
	float x_offset, y_offset;

	// To start the 60 degree cone
	ray_angle = player.angle() - THIRTY_DEG;
	if (ray_angle < 0) {
		ray_angle += TWO_PI;
	}
	const int cone_degree = 120;

	for (r=0; r<cone_degree; ++r) {
		dof = 0;
		const float neg_tan = -1 * tan(ray_angle);
		const float a_tan = 1 / neg_tan;
		if (ray_angle > M_PI) {
			hray_y = (((int) player.y() >> 6) << 6) - 0.0001;
			hray_x = (player.y() - hray_y) * a_tan + player.x();
			y_offset = -64;
			x_offset = -y_offset * a_tan;
		}
		if (ray_angle < M_PI) {
			hray_y = (((int) player.y() >> 6) << 6) + 64;
			hray_x = (player.y() - hray_y) * a_tan + player.x();
			y_offset = 64;
			x_offset = -y_offset * a_tan;
		}
		if ((ray_angle == 0) || (ray_angle == M_PI)) {
			hray_x = player.x();
			hray_y = player.y();
			dof = 8;
		}
		while (dof < 8) {
			mx = ((int) hray_x) >>6;
			my = ((int) hray_y) >>6;
			mp = my * map_x + mx;
			if ((mp > 0) && (mp < map_size) && (game_map[mp]==1)) {
				dof = 8; // We hit the wall
				continue;
			}
			else {
				hray_x += x_offset;
				hray_y += y_offset;
				dof += 1;
			}
		}
		const float h_dist = distance(player.x(), player.y(), hray_x, hray_y);

		dof = 0;
		if ((ray_angle > HALF_PI) && ( ray_angle < THREE_HALF_PI)) {
			vray_x = (((int) player.x() >> 6) << 6) - 0.0001;
			vray_y = (player.x() - vray_x) * neg_tan + player.y();
			x_offset = -64;
			y_offset = -x_offset * neg_tan;
		}
		if ((ray_angle > THREE_HALF_PI) || (ray_angle < HALF_PI)) {
			vray_x = (((int) player.x() >> 6) << 6) + 64;
			vray_y = (player.x() - vray_x) * neg_tan + player.y();
			x_offset = 64;
			y_offset = -x_offset * neg_tan;
		}
		if ((ray_angle == 0) || (ray_angle == M_PI)) {
			vray_x = player.x();
			vray_y = player.y();
			dof = 8;
		}
		while (dof < 8) {
			mx = ((int) vray_x) >>6;
			my = ((int) vray_y) >>6;
			mp = my * map_x + mx;
			if ((mp > 0) && (mp < map_size) && (game_map[mp]==1)) {
				dof = 8; // We hit the wall
			}
			else {
				vray_x += x_offset;
				vray_y += y_offset;
				dof += 1;
			}
		}
		const float v_dist = distance(player.x(), player.y(), vray_x, vray_y);

		float ray_x, ray_y;
		float ray_dist;
		if (h_dist > v_dist) {
			ray_x = vray_x;
			ray_y = vray_y;
			ray_dist = v_dist;
			glColor3f(0, 0.8, 0);
		}
		else {
			ray_x = hray_x;
			ray_y = hray_y;
			ray_dist = h_dist;
			glColor3f(0, 1, 0);
		}

		fenk_gl::draw_line(1, player.x(), player.y(), ray_x, ray_y);

		float line_height = (map_size * 320) / ray_dist;
		if (line_height > 320) {
			line_height = 320;
		}
		const float horizontal_screen_offset = WIDTH - (r << 2) - 24;
		const float line_offset = 240 - line_height / 2;
		fenk_gl::draw_line(
			8, 
			horizontal_screen_offset, 
			line_offset, 
			horizontal_screen_offset, 
			line_height + line_offset
		);

		ray_angle += HALF_DEG;
		if (ray_angle > TWO_PI) {
			ray_angle -= TWO_PI;
		}
	}
}

void buttons(unsigned char key, int delta_x, int delta_y) {
	if (key == 'a') {
		player.add_angle(0.1);
	}

	if (key == 'd') {
		player.sub_angle(0.1);
	}

	if (key == 's') {
		player.update_position(-player.deg_x(), -player.deg_y());
	}

	if (key == 'w') {
		player.update_position(player.deg_x(), player.deg_y());
	}

	glutPostRedisplay();
}

void display() {
	// Clear display
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Draw player generated map
	draw_map();
	// Draw out little dot of a player :)
	draw_player();
	draw_rays_3D();
	glutSwapBuffers();
}

void init() {
	glClearColor(0.3, 0.3, 0.3, 0);
	gluOrtho2D(0, WIDTH, 0, HEIGHT);
	map_x = 8, map_y = 8, map_size = 64;
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("Future DOOM Clone");

	// Initialize some variables
	init();

	// Bind some functions to glut
	glutDisplayFunc(display);
	glutKeyboardFunc(buttons);

	glutMainLoop();
	return 0;
}
