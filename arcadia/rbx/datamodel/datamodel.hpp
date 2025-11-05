#pragma once
#include <windows.h>
#include <iostream>
#include <rbx/instance/instance.hpp>

namespace rbx {
	class c_datamodel : public c_instance {
	public:
		std::uint64_t get_place_id();
		std::uint64_t get_game_id();
		bool get_game_loaded();
		std::string get_server_ip();

		std::uint64_t get_place_version();
		std::uint64_t get_creator_id();
		int get_primitive_count();
		c_instance* get_workspace();
	};
}