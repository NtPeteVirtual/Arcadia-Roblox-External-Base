#pragma once
#include <misc/memory/memory.hpp>
#include <rbx/offsets.hpp>
#include <rbx/math.hpp>
#include <windows.h>
#include <iostream>
#include <string>
#include <vector>

namespace rbx {
	class c_instance {
	public:
		std::uintptr_t address = 0;

		std::string get_name();
		std::string get_class_name();
		std::vector<c_instance> get_children();

		c_instance find_first_child(std::string name);
		c_instance find_first_child_of_class(std::string name);
		c_instance get_parent();
	};
	inline const auto g_instance = std::make_unique<c_instance>();
}