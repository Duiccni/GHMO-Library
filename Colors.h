#pragma once

using color_t = unsigned int;

namespace colors
{
	constexpr color_t
		alpha = 0xFF000000,
		black = 0,
		transparent = black,
		visiable_transparent_color = alpha & transparent,
		gray = 0x808080,
		white = 0xFFFFFF,
		red = 0xFF0000,
		green = 0xFF00,
		blue = 0xFF,
		cyan = 0xFFFF,
		purple = 0xFF00FF,
		yellow = 0xFFFF00,
		orange = 0xFF8000,
		lime = 0x08FF00,
		dark_blue = 0x80,
		dark_red = 0x800000,
		dark_green = 0x8000;
}
