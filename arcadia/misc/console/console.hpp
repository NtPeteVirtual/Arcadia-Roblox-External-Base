#pragma once
#include <Windows.h>
#include <iostream>

namespace misc {
	class c_console {
	public:
		void set_title(std::string title);
		void set_font();
		void set_ansi();
		void print(bool success, const std::string& text);
	};

	inline const auto& g_console = std::make_unique<c_console>();
}