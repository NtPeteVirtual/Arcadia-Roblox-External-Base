#include "memory.hpp"
#include <xorstr/xorstr.hpp>
#include <lazy_importer/lazy_importer.hpp>

std::uint32_t misc::c_memory::find_process_id(const std::string& process_name)
{
	std::uint64_t local_process_id = 0;
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

	if (snapshot == INVALID_HANDLE_VALUE)
	{
		return local_process_id;
	}

	PROCESSENTRY32 process_entry{};
	process_entry.dwSize = sizeof(PROCESSENTRY32);

	if (Process32First(snapshot, &process_entry))
	{
		do
		{
			if (!_stricmp(process_name.c_str(), process_entry.szExeFile))
			{
				local_process_id = process_entry.th32ProcessID;
				process_id = local_process_id;
				break;
			}
		} while (Process32Next(snapshot, &process_entry));
	}

	CloseHandle(snapshot);
	return local_process_id;
}

std::uint64_t misc::c_memory::find_module_address(const std::string& module_name)
{
	std::uint64_t module_address = 0;

	if (!process_handle)
	{
		return module_address;
	}

	DWORD process_id = GetProcessId(process_handle);
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, process_id);

	if (snapshot == INVALID_HANDLE_VALUE)
	{
		return module_address;
	}

	MODULEENTRY32 module_entry{};
	module_entry.dwSize = sizeof(MODULEENTRY32);

	if (Module32First(snapshot, &module_entry))
	{
		do
		{
			if (!_stricmp(module_name.c_str(), module_entry.szModule))
			{
				module_address = reinterpret_cast<uint64_t>(module_entry.modBaseAddr);
				base_address = module_address;
				break;
			}
		} while (Module32Next(snapshot, &module_entry));
	}

	CloseHandle(snapshot);
	return module_address;
}

bool misc::c_memory::attach_to_process(const std::string& process_name)
{
	HANDLE process = OpenProcess(PROCESS_ALL_ACCESS, false, find_process_id(process_name));

	if (process == INVALID_HANDLE_VALUE)
	{
		return false;
	}

	process_handle = process;

	return true;
}

std::string misc::c_memory::read_string(std::uint64_t address)
{
	std::int32_t string_length = read<std::int32_t>(address + 0x10);
	std::uint64_t string_address = (string_length >= 16) ? read<std::uint64_t>(address) : address;

	if (string_length == 0 || string_length > 255)
	{
		return "Unknown";
	}

	std::vector<char> buffer(string_length + 1, 0);
	Luck_ReadVirtualMemory(process_handle, reinterpret_cast<void*>(string_address), buffer.data(), buffer.size(), nullptr);

	return std::string(buffer.data(), string_length);
}

void misc::c_memory::write_string(std::uint64_t address, const std::string& value) {
	const auto currentStringLength = read<int64_t>(address + 0x18);

	std::uint64_t stringAddress = currentStringLength >= 16u ? read<std::uint64_t>(address) : address;

	for (size_t i = 0; i < value.size() && i < 200; i++) {
		write<char>(stringAddress + i, value[i]);
	}

	write<char>(stringAddress + value.size(), '\0');

	write<int64_t>(address + 0x10, static_cast<int64_t>(value.size()));
}

std::uint32_t misc::c_memory::get_process_id()
{
	return process_id;
}

std::uint64_t misc::c_memory::get_module_address()
{
	return base_address;
}

HANDLE misc::c_memory::get_process_handle()
{
	return process_handle;
}