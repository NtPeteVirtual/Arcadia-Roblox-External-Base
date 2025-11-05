#pragma once
#include <Windows.h>
#include <iostream>
#include <vector>
#include <rbx/instance/instance.hpp>
#include <rbx/datamodel/datamodel.hpp>
#include <misc/globals/globals.hpp>
#include <misc/memory/memory.hpp>
#include <misc/console/console.hpp>
const char* roblox = "RobloxPlayerBeta.exe";
constexpr auto blue_2 = "\x1b[38;2;100;180;255m";
constexpr auto red_2 = "\x1b[38;2;255;80;80m";
constexpr auto reset_2 = "\x1b[0m";

void entry(const char* module_name) {

	misc::g_console->set_title("Arcadia - Debug");
	misc::g_console->set_ansi();

	misc::g_memory->attach_to_process(module_name);
	misc::g_memory->find_process_id(module_name);
	misc::g_memory->find_module_address(module_name);
	globals::base_address = misc::g_memory->get_module_address();

	std::uintptr_t fake_datamodel_pointer = misc::g_memory->read<std::uintptr_t>(globals::base_address + Offsets::FakeDataModel::Pointer);
	globals::game = misc::g_memory->read<rbx::c_instance>(fake_datamodel_pointer + Offsets::FakeDataModel::RealDataModel);
	globals::visualengine = misc::g_memory->read<rbx::c_visualengine>(globals::base_address + Offsets::VisualEngine::Pointer);
	globals::players = globals::game.find_first_child_of_class("Players");
	globals::workspace = globals::game.find_first_child_of_class("Workspace");

	misc::g_console->print(true, "Welcome To Arcadia, Initializing");
	misc::g_console->print(true, "Roblox Version -> " + Offsets::ClientVersion);
	std::cout << blue_2 << "[ADDRESS]: " << reset_2 << " Base Address -> 0x" << std::hex << globals::base_address << std::dec << std::endl;
	std::cout << blue_2 << "[ADDRESS]: " << reset_2 << " DataModel Address -> 0x" << std::hex << globals::game.address << std::dec << std::endl;
	std::cout << blue_2 << "[ADDRESS]: " << reset_2 <<  " VisualEngine Address -> 0x" << std::hex << globals::visualengine.address << std::dec << std::endl;
	std::cout << blue_2 << "[ADDRESS]: " << reset_2 << " Players Address -> 0x" << std::hex << globals::players.address << std::dec << std::endl;
	std::cout << blue_2 << "[ADDRESS]: " << reset_2 << " Workspace Address -> 0x" << std::hex << globals::workspace.address << std::dec << std::endl;

}

int main() {
	entry(roblox);
	std::cin.get();
}