#define _INCLUDE_3DH 0

#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "user32.lib")

#include "World.h"

LRESULT CALLBACK window_proc(HWND hwnd, UINT u_msg, WPARAM w_param, LPARAM l_param)
{
	switch (u_msg)
	{
	case WM_CLOSE:
		data::running = false;
		return 0;
	case WM_DESTROY:
		data::running = false;
		return 0;
	case WM_LBUTTONDOWN:
		data::mouse.t_left = true;
		data::mouse.left = true;
		return 0;
	case WM_LBUTTONUP:
		data::mouse.left = false;
		return 0;
	case WM_MBUTTONDOWN:
		data::mouse.t_middle = true;
		data::mouse.middle = true;
		return 0;
	case WM_MBUTTONUP:
		data::mouse.middle = false;
		return 0;
	case WM_RBUTTONDOWN:
		data::mouse.t_right = true;
		data::mouse.right = true;
		return 0;
	case WM_RBUTTONUP:
		data::mouse.right = false;
		return 0;
	default:
		return DefWindowProcW(hwnd, u_msg, w_param, l_param);
	}
}

int WINAPI wWinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPWSTR lpCmdLine,
	int nShowCmd
)
{
	graphics::init();
	if (font::init())
	{
		MessageBoxW(nullptr, L"'font.bin' file cant found!", L"Error", MB_OK);
		return 0;
	}

	WNDCLASSW wc = {};
	wc.lpfnWndProc = window_proc;
	wc.hInstance = hInstance;
	wc.lpszClassName = L"6.1";

	if (!RegisterClassW(&wc))
	{
		MessageBoxW(nullptr, L"Failed to register Window Class!", L"Error", MB_OK);
		return 0;
	}

	HWND window = CreateWindowExW(
		0,
		wc.lpszClassName,
		wc.lpszClassName,
		WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT,
		screen_size.x + extra_size.x, screen_size.y + extra_size.y,
		nullptr, nullptr, hInstance, nullptr
	);

	if (window == nullptr)
	{
		UnregisterClassW(wc.lpszClassName, hInstance);

		MessageBoxW(nullptr, L"Failed to create Window!", L"Error", MB_OK);
		return 0;
	}

	bitmap_info.bmiHeader.biSize = sizeof(bitmap_info.bmiHeader);
	bitmap_info.bmiHeader.biWidth = screen_size.x;
	bitmap_info.bmiHeader.biHeight = screen_size.y;
	bitmap_info.bmiHeader.biPlanes = 1;
	bitmap_info.bmiHeader.biBitCount = 32;
	bitmap_info.bmiHeader.biCompression = BI_RGB;

	HDC hdc = GetDC(window);

	ShowWindow(window, nShowCmd);
	UpdateWindow(window);

	FILE* fp = nullptr;
	if constexpr (CONSOLE)
	{
		AllocConsole();
		freopen_s(&fp, "CONOUT$", "w", stdout);
	}

	/*
	point test_a{ 1, 2 }, test_b{ 5, 6 }, test_c = test_a + test_b;
	std::cout << test_a << " + " << test_b << " = " << test_c;
	*/

	/*
	d3point test_a{ 1, 2, 3 }, test_b{ 5, 6, 7 }, test_c = test_a + test_b;
	std::cout << test_a << " + " << test_b << " = " << test_c;
	*/

	// graphics::surface resized_screen = graphics::surface(screen_size >> 2);
	graphics::surface* bad_apple = graphics::read_binary_into_surface("image-2.bin", graphics::RBIS_24B);

	// graphics::reverse_colors(*bad_apple);
	graphics::black_and_white(*bad_apple);
	graphics::blur(*bad_apple);

	MSG msg = {};
	DWORD start_time;

	/*
	d3fpoint ROT_AMOUNT = { 0, 0, 0 };

	d3point
		c_center = { 0, 0, 300 },
		c111,
		c112,
		c121,
		c122,
		c211,
		c212,
		c221,
		c222,
		cc111 = { 100, 100, 200 },
		cc112 = { 100, -100, 200 },
		cc121 = { -100, 100, 200 },
		cc122 = { -100, -100, 200 },
		cc211 = { 100, 100, 400 },
		cc212 = { 100, -100, 400 },
		cc221 = { -100, 100, 400 },
		cc222 = { -100, -100, 400 };

	d3_math::camera main_cam = { { 200, 200, -200 }, { 0.5f, -0.2f, 0 } };
	*/

	while (data::running)
	{
		start_time = timeGetTime();
		while (PeekMessageW(&msg, window, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessageW(&msg);
		}

		update_mouse(window);

		colors::black >> screen;

		font::draw_string({ 30, 30 }, "Hello, World!", colors::lime, screen);
		font::draw_string({ 30, 50 }, "Hello, World!", colors::cyan, screen);
		font::draw_string({ 30, 70 }, "Hello, World!", colors::gray, screen);
		font::draw_string({ 30, 90 }, "Hello, World!", colors::purple, screen);
		font::draw_string({ 30, 110 }, "Hello, World!", colors::orange, screen);
		font::draw_string({ 30, 130 }, "Hello, World!", colors::white, screen);
		font::draw_string({ 30, 150 }, "Hello, World!", colors::yellow, screen);

		// graphics::slight_blur(screen);

		/*
		c111 = d3_math::rotate_orgin(cc111, c_center, ROT_AMOUNT);
		c112 = d3_math::rotate_orgin(cc112, c_center, ROT_AMOUNT);
		c121 = d3_math::rotate_orgin(cc121, c_center, ROT_AMOUNT);
		c122 = d3_math::rotate_orgin(cc122, c_center, ROT_AMOUNT);

		c211 = d3_math::rotate_orgin(cc211, c_center, ROT_AMOUNT);
		c212 = d3_math::rotate_orgin(cc212, c_center, ROT_AMOUNT);
		c221 = d3_math::rotate_orgin(cc221, c_center, ROT_AMOUNT);
		c222 = d3_math::rotate_orgin(cc222, c_center, ROT_AMOUNT);

		ROT_AMOUNT.x += 0.01f;
		ROT_AMOUNT.y += 0.01f;
		ROT_AMOUNT.z += 0.01f;

		point
			a111 = d3_math::perspective_d2(c111, main_cam, screen),
			a112 = d3_math::perspective_d2(c112, main_cam, screen),
			a121 = d3_math::perspective_d2(c121, main_cam, screen),
			a122 = d3_math::perspective_d2(c122, main_cam, screen),
			a211 = d3_math::perspective_d2(c211, main_cam, screen),
			a212 = d3_math::perspective_d2(c212, main_cam, screen),
			a221 = d3_math::perspective_d2(c221, main_cam, screen),
			a222 = d3_math::perspective_d2(c222, main_cam, screen);

		graphics::draw::line(a111, a112, colors::white, screen);
		graphics::draw::line(a121, a122, colors::white, screen);
		graphics::draw::line(a111, a121, colors::white, screen);
		graphics::draw::line(a112, a122, colors::white, screen);

		graphics::draw::line(a211, a212, colors::white, screen);
		graphics::draw::line(a221, a222, colors::white, screen);
		graphics::draw::line(a211, a221, colors::white, screen);
		graphics::draw::line(a212, a222, colors::white, screen);

		graphics::draw::line(a211, a111, colors::white, screen);
		graphics::draw::line(a212, a112, colors::white, screen);
		graphics::draw::line(a221, a121, colors::white, screen);
		graphics::draw::line(a222, a122, colors::white, screen);

		graphics::draw::circle(a111, 5, colors::yellow, screen);
		graphics::draw::circle(a112, 5, colors::yellow, screen);
		graphics::draw::circle(a121, 5, colors::yellow, screen);
		graphics::draw::circle(a122, 5, colors::yellow, screen);

		graphics::draw::circle(a211, 5, colors::yellow, screen);
		graphics::draw::circle(a212, 5, colors::yellow, screen);
		graphics::draw::circle(a221, 5, colors::yellow, screen);
		graphics::draw::circle(a222, 5, colors::yellow, screen);
		*/

		// graphics::checkers(screen, 30, graphics::rgb_color(0x40, 0x30, 0x30));

		// graphics::rgb_color(0x40, 0x30, 0x30) >> screen;

		/*
		color_t* px_start = screen.buffer, * px, color;
		for (int x = 0; x < 360; ++x, ++px_start)
		{
			px = px_start;
			color = graphics::hsv_to_rgb(x, UINT8_MAX, UINT8_MAX);
			for (int y = 0; y < 60; ++y, px += screen_size.x)
				*px = color;
		}
		*/

		// graphics::resize_surface(screen, resized_screen);
		// graphics::blit_surface(screen, resized_screen, (screen_size >> 3) * 3, false, false);

		// graphics::blit_surface(screen, *bad_apple, { 30, 90 }, false, false);

		StretchDIBits(
			hdc,
			0, 0, screen_size.x, screen_size.y,
			0, 0, screen_size.x, screen_size.y,
			screen.buffer, &bitmap_info,
			DIB_RGB_COLORS, SRCCOPY
		);

		clear_mouse_tick();

		data::performance = timeGetTime() - start_time;
		if (data::performance < data::target_frame_time)
		{
			Sleep(data::target_frame_time - data::performance);
			data::delta_time = data::target_frame_time;
		}
		else data::delta_time = data::performance;
		++data::tick;
	}

	ReleaseDC(window, hdc);
	DestroyWindow(window);
	UnregisterClassW(wc.lpszClassName, hInstance);

	if constexpr (CONSOLE)
	{
		if (fp) fclose(fp);
		FreeConsole();
	}

	free(screen.buffer);
	screen.buffer = nullptr;
	graphics::clean_up();
	font::clean_up();

	return 0;
}
