#include "console.hpp"
#include <iostream>

namespace misc {

	void c_console::set_title(std::string title) {
		SetConsoleTitleA(title.c_str());
	}

	void c_console::set_ansi() {
		HANDLE h_out = GetStdHandle(STD_OUTPUT_HANDLE);
		if (h_out == INVALID_HANDLE_VALUE) return;

		DWORD d_mode = 0;
		if (!GetConsoleMode(h_out, &d_mode)) return;

		d_mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
		SetConsoleMode(h_out, d_mode);
	}

	void c_console::print(bool success, const std::string& text) {
		constexpr auto blue = "\x1b[38;2;100;180;255m"; // soft blue
		constexpr auto red = "\x1b[38;2;255;80;80m";   // red (clean)
		constexpr auto reset = "\x1b[0m";

		if (success)
			std::cout << blue << "[INFO]" << reset << " " << text << std::endl;
		else
			std::cout << red << "[ERROR]" << reset << " " << text << std::endl;
	}
}