namespace fenk_gl {
	/*
	struct _float_pair {
		float first;
		float second;
	};
	
	using Float_pair = struct _float_pair;

	void horizontal_line_check(
		float player_x,
		float player_y,
		float ray_angle,
		float &ray_x,
		float &ray_y,
		float game_map[],
		float map_size
	);
	*/
	class Player {
		private:
			float _pos_x, _pos_y;
			float _angle, _deg_x, _deg_y;
		public:
			Player(float position_x, float position_y, float init_angle);

			float x() const;
			float y() const;
			float angle() const;
			float deg_x() const;
			float deg_y() const;

			void set_angle(float new_angle);
			void add_angle(float delta);
			void sub_angle(float delta);

			void update_position(float delta_x, float delta_y);
	};
}
