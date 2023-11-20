#include "pch.h"
#include "helper.h"

bool helper::is_address_in_our_module(PVOID addr)
{
	const auto module_end = globals::module_base + globals::module_size;
	return (uintptr_t)addr >= globals::module_base && (uintptr_t)addr < module_end;
}

bool helper::is_address_in_game_module(PVOID addr)
{
	const auto nt_hdr = (PIMAGE_NT_HEADERS32)(globals::executable_base + ((PIMAGE_DOS_HEADER)globals::executable_base)->e_lfanew);
	const auto module_size = nt_hdr->OptionalHeader.SizeOfImage;

	const auto module_end = globals::executable_base + module_size;

	return (uintptr_t)addr >= globals::executable_base && (uintptr_t)addr < module_end;
}

bool helper::is_address_within_specified_module(PVOID addr, const char* module_name)
{
	const auto module = (uintptr_t)GetModuleHandleA(module_name);
	if (!module) return false;

	const auto nt_hdr = (PIMAGE_NT_HEADERS32)(module + ((PIMAGE_DOS_HEADER)module)->e_lfanew);
	const auto module_size = nt_hdr->OptionalHeader.SizeOfImage;

	const auto module_end = module + module_size;

	return (uintptr_t)addr >= module && (uintptr_t)addr < module_end;
}

std::vector<MODULEENTRY32> helper::get_all_modules()
{
	std::vector<MODULEENTRY32> modules{};

	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, GetCurrentProcessId());
	if (snapshot && snapshot != INVALID_HANDLE_VALUE)
	{
		MODULEENTRY32 me32;
		me32.dwSize = sizeof(MODULEENTRY32);
		if (Module32First(snapshot, &me32))
		{
			do {
				modules.push_back(me32);
			} while (Module32Next(snapshot, &me32));
		}
		CloseHandle(snapshot);
	}
	return modules;
}