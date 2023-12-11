#pragma once

#include "Graphics.h"
#include "3Dpoint.h"

namespace d3_math
{
	struct camera
	{
		d3point pos;
		d3fpoint rot;
	};

	using ccr = const camera&;

	void rotate_xOv(d3point& pos, float angle)
	{
		if (angle == 0) return;
		float c = std::cosf(angle), s = std::sinf(angle);
		int temp = pos.y;
		pos.y = pos.y * c - pos.z * s;
		pos.z = temp * s + pos.z * c;
	}

	void rotate_yOv(d3point& pos, float angle)
	{
		if (angle == 0) return;
		float c = std::cosf(angle), s = std::sinf(angle);
		int temp = pos.x;
		pos.x = pos.x * c + pos.z * s;
		pos.z = pos.z * c - temp * s;
	}

	void rotate_zOv(d3point& pos, float angle)
	{
		if (angle == 0) return;
		float c = std::cosf(angle), s = std::sinf(angle);
		int temp = pos.x;
		pos.x = pos.x * c - pos.y * s;
		pos.y = temp * s + pos.y * c;
	}

	inline void rotate_d3Ov(d3point& pos, d3fpoint rot)
	{
		rotate_xOv(pos, rot.x);
		rotate_yOv(pos, rot.y);
		rotate_zOv(pos, rot.z);
	}

	inline d3point rotate_orgin(d3point pos, d3point orgin, d3fpoint rot)
	{
		pos -= orgin;
		rotate_xOv(pos, rot.x);
		rotate_yOv(pos, rot.y);
		rotate_zOv(pos, rot.z);
		return pos + orgin;
	}

	inline point perspective_d2(d3point pos, ccr cam, graphics::csrEx surf)
	{
		pos -= cam.pos;
		rotate_d3Ov(pos, -cam.rot);
		if (pos.z <= 0) return { 0, 0 };
		return {
			pos.x * surf.smaller_dim_h / pos.z + surf.half_size.x,
			pos.y * surf.smaller_dim_h / pos.z + surf.half_size.y
		};
	}
}
