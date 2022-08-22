#ifndef FENK_GL_SHAPES
#define FENK_GL_SHAPES

namespace fenk_gl {
	/*
	 * @brief Draws a 'simple' quadrilateral
	 *
	 *  (x_origin, y_origin+y_offset)|--------|(x_origin+x_offset, 
	 *                               |        |            y_origin+y_offset)
	 *                               |        |
	 *                               |        |
	 *           (x_origin, y_origin)|________|(x_origin+x_offset, y_origin)
	 *
	 * @param x_origin The origin x point, which will be the lower left 
	 * 	corner on the x-axis of the square
	 *
	 * @param y_origin The origin y point, which will be the lower left 
	 * 	corner on the y-axis of the square
	 *
	 * @param x_offset Determines the width offset of the quadrilateral,
	 * 	x_offset - x_origin is the width of the quadrilateral in pixels
	 *
	 * @param y_offset Determines the height offset of the quadrilateral,
	 *  y_offset - y_origin is the height of the quadrilateral in pixels
	 *
	 * @see draw_quad_with_border Draws a 'simple' quadrilateral with a
	 *  1 pixel border
	 */
	void draw_quad(int x_origin, int y_origin, int x_offset, int y_offset);

	/*
	 * @brief Draws a 'simple' quadrilateral with a 1 pixel border
	 *
	 * @param x_origin The origin x point, which will be the lower left 
	 *  corner on the x-axis of the square
	 *
	 * @param y_origin The origin y point, which will be the lower left 
	 *  corner on the y-axis of the square
	 *
	 * @param x_offset Determines the width offset of the quadrilateral, 
	 *  x_offset - x_origin is the width of the quadrilateral in pixels
	 *
	 * @param y_offset Determines the height offset of the quadrilateral,
	 *  y_offset - y_origin is the height of the quadrilateral in pixels
	 *
	 * @see draw_quad Draws a 'simple' quadrilateral
	 */
	void draw_quad_with_border(
		int x_origin, 
		int y_origin, 
		int x_offset, 
		int y_offset
	);

	/*
	 * @brief Draws a line with a specified thickness
	 *
	 *                          /(x_end, y_end)
	 *                         /
	 *                        /
	 *                       /
	 *  (x_begin, y_begin)/
	 *
	 *  @param thiccness The pixel thickness of the line
	 *  @param x_begin The beginning x coordinate of the line
	 *  @param y_begin The beginning y coordinate of the line
	 *  @param x_end The ending x coordinate of the line
	 *  @param y_end The ending y coordinate of the line
	 */
	void draw_line(
		int thiccness,
		int x_begin, 
		int y_begin, 
		int x_end, 
		int y_end
	);

}

#endif // FENK_GL_SHAPES
