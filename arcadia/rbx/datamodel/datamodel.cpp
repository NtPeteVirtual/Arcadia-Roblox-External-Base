#pragma once
#include "datamodel.hpp"
#include <misc/globals/globals.hpp>

namespace rbx {

	std::uint64_t c_datamodel::get_place_id() {
		return misc::g_memory->read<std::uint64_t>(globals::game.address + Offsets::DataModel::PlaceId);
	}

	std::uint64_t c_datamodel::get_game_id() {
		return misc::g_memory->read<std::uint64_t>(globals::game.address + Offsets::DataModel::GameId);
	}

	bool c_datamodel::get_game_loaded() {
		return misc::g_memory->read<bool>(globals::game.address + Offsets::DataModel::GameLoaded);
	}

	std::string c_datamodel::get_server_ip() {
		return misc::g_memory->read_string(globals::game.address + Offsets::DataModel::ServerIP);
	}

	std::uint64_t c_datamodel::get_place_version() {
		return misc::g_memory->read<std::uint64_t>(globals::game.address + Offsets::DataModel::PlaceVersion);
	}

	std::uint64_t c_datamodel::get_creator_id() {
		return misc::g_memory->read<std::uint64_t>(globals::game.address + Offsets::DataModel::CreatorId);
	}

	int c_datamodel::get_primitive_count() {
		return misc::g_memory->read<int>(globals::game.address + Offsets::DataModel::PrimitiveCount);
	}

}