#include "GL/gl.h"

#include "../include/fenkcaster/draw_shapes.hpp"

namespace fenk_gl {
	void draw_quad(int x_origin, int y_origin, int x_offset, int y_offset) {
		glBegin(GL_QUADS);
		glVertex2i(x_origin, y_origin);
		glVertex2i(x_origin, y_origin + y_offset);
		glVertex2i(x_origin + x_offset, y_origin + y_offset);
		glVertex2i(x_origin + x_offset, y_origin);
		glEnd();
	}
	
	void draw_quad_with_border(
			int x_origin, int y_origin, int x_offset, int y_offset) {
		glBegin(GL_QUADS);
		glVertex2i(x_origin + 1, y_origin + 1);
		glVertex2i(x_origin + 1, y_origin + y_offset - 1);
		glVertex2i(x_origin + x_offset - 1, y_origin + y_offset - 1);
		glVertex2i(x_origin + x_offset - 1, y_origin + 1);
		glEnd();
	}

	void draw_line(
			int thiccness, int x_begin, int y_begin, int x_end, int y_end) {
		glBegin(GL_LINES);
		glLineWidth(thiccness);
		glVertex2i(x_begin, y_begin);
		glVertex2i(x_end, y_end);
		glEnd();
	}
}

