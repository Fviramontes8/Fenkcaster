#include <cmath>

#include "../include/fenkcaster/player.hpp"

#define FGL_TWO_PI 2*M_PI
#define FGL_HALF_PI M_PI/2
#define FGL_THREE_HALF_PI 3 * M_PI/2

namespace fenk_gl {
	/*
	void horizontal_line_check(
			float player_x, float player_y, float ray_angle, float &ray_x, 
			float &ray_y, float game_map[], float map_size){
		int dof = 0;
		float x_offset, y_offset;
		const float neg_tan = -1 * tan(ray_angle);
		const float a_tan = 1 / neg_tan;
		if (ray_angle > M_PI) {
			ray_y = (((int) player_y >> 6) << 6) - 0.0001;
			ray_x = (player_y - ray_y) * a_tan + player_x;
			y_offset = -64;
			x_offset = -y_offset * a_tan;
		}
		if (ray_angle < M_PI) {
			ray_y = (((int) player_y >> 6) << 6) + 64;
			ray_x = (player_y - ray_y) * a_tan + player_x;
			y_offset = 64;
			x_offset = -y_offset * a_tan;
		}
		if ((ray_angle == 0) || (ray_angle == M_PI)) {
			ray_x = player_x;
			ray_y = player_y;
			dof = 8;
		}
		while (dof < 8) {
			int mx = ((int) ray_x) >>6;
			int my = ((int) ray_y) >>6;
			int mp = my * map_x + mx;
			if ((mp > 0) && (mp < map_size) && (game_map[mp]==1)) {
				dof = 8; // We hit the wall
				continue;
			}
			else {
				ray_x += x_offset;
				ray_y += y_offset;
				dof += 1;
			}
		}
	}
	*/
	Player::Player(float position_x, float position_y, float init_angle) :
			_pos_x{position_x}, _pos_y{position_y}, _angle{init_angle} {
		_deg_x = cos(init_angle) * 5;
		_deg_y = sin(init_angle) * 5;
	}

	float Player::x() const {
		return _pos_x;
	}

	float Player::y() const {
		return _pos_y;
	}

	float Player::angle() const {
		return _angle;
	}

	float Player::deg_x() const {
		return _deg_x;
	}
		
	float Player::deg_y() const {
		return _deg_y;
	}

	void Player::set_angle(float new_angle) {
		_angle = new_angle;
		if (_angle > FGL_TWO_PI) {
			_angle -= FGL_TWO_PI;
		}
		if (_angle < 0) {
			_angle += FGL_TWO_PI;
		}
		_deg_x = cos(_angle) * 5;
		_deg_y = sin(_angle) * 5;
	}
	void Player::add_angle(float delta) {
		set_angle(angle() + delta);
	}

	void Player::sub_angle(float delta) {
		set_angle(angle() - delta);
	}

	void Player::update_position(float delta_x, float delta_y) {
		_pos_x += delta_x;
		_pos_y += delta_y;
	}
}

