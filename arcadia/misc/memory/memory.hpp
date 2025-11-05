#pragma once
#include <Windows.h>
#include <iostream>
#include <vector>
#include <string>
#include <TlHelp32.h>
#include <memory>
#include <xorstr/xorstr.hpp>
#include <json/json.hpp>

extern "C" intptr_t
Luck_ReadVirtualMemory
(
	HANDLE ProcessHandle,
	PVOID BaseAddress,
	PVOID Buffer,
	ULONG NumberOfBytesToRead,
	PULONG NumberOfBytesRead
);

extern "C" intptr_t
Luck_WriteVirtualMemory
(
	HANDLE Processhandle,
	PVOID BaseAddress,
	PVOID Buffer,
	ULONG NumberOfBytesToWrite,
	PULONG NumberOfBytesWritten
);

namespace misc {
	class c_memory {
	public:
		std::uint32_t find_process_id(const std::string& process_name);
		std::uint64_t find_module_address(const std::string& module_name);

		bool attach_to_process(const std::string& process_name);

		std::string read_string(std::uint64_t address);
		void write_string(std::uint64_t address, const std::string& value);

		template <typename T>
		T read(std::uint64_t address);

		template <typename T>
		void write(std::uint64_t address, T value);

		std::uint32_t get_process_id();
		std::uint64_t get_module_address();
		HANDLE get_process_handle();

	private:
		std::uint32_t process_id;
		std::uint64_t base_address;
		HANDLE process_handle;
	};

	template <typename T>
	T c_memory::read(uint64_t address)
	{
		T buffer{};

		Luck_ReadVirtualMemory(process_handle, reinterpret_cast<void*>(address), &buffer, sizeof(T), nullptr);

		return buffer;
	}

	template <typename T>
	void c_memory::write(uint64_t address, T value)
	{
		Luck_WriteVirtualMemory(process_handle, reinterpret_cast<void*>(address), &value, sizeof(T), nullptr);
	}

	inline const auto g_memory = std::make_unique<c_memory>();
}