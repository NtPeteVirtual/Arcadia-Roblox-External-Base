#pragma once
#include <windows.h>
#include <iostream>
#include <map>
#include <filesystem>
#include <rbx/instance/instance.hpp>
#include <rbx/datamodel/datamodel.hpp>
#include <rbx/visualengine/visualengine.hpp>

namespace globals {
	inline std::uintptr_t base_address;

	inline std::filesystem::path logs_folder;
	inline std::filesystem::path config_folder;
	inline std::filesystem::path workspace_folder;

	inline rbx::c_instance game;
	inline rbx::c_instance players;
	inline rbx::c_instance workspace;
	inline rbx::c_visualengine visualengine;
	
}