#include "pch.h"

void initialize(uintptr_t module_base, size_t module_size)
{
	globals::executable_base = (uintptr_t)GetModuleHandle(nullptr);
	globals::module_base = module_base;
	globals::module_size = ((PIMAGE_NT_HEADERS32)(module_base + ((PIMAGE_DOS_HEADER)module_base)->e_lfanew))->OptionalHeader.SizeOfImage;

#ifdef _DEBUG
	AllocConsole();
	FILE* f;
	freopen_s(&f, "CONOUT$", "w", stdout);

	std::cout << "Initialized" << std::endl;
	std::cout << "Executable Base: 0x" << std::hex << globals::executable_base << std::endl;
	std::cout << "Module Base: 0x" << std::hex << globals::module_base << std::endl;
	std::cout << "Module Size: " << globals::module_size << std::endl;
#endif

	offsets::initialize_offsets();

	game::player* local_player = *(game::player**)(globals::executable_base + offsets::p_local_player);
}
