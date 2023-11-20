#include "pch.h"
#include "vtable.h"
#include "anticheat/stub/helper/helper.h"


bool stub::vmt::verify_vtable_pointer(void* instance)
{
	if (instance == nullptr)
	{
		return false;
	}

	uintptr_t* p_vtable = *reinterpret_cast<uintptr_t**>(instance);

	return helper::is_address_in_game_module((PVOID)p_vtable);
}

bool stub::vmt::verify_vtable_integrity(void* instance)
{
	if (instance == nullptr)
	{
		return false;
	}

	uintptr_t* p_vtable = *reinterpret_cast<uintptr_t**>(instance);

	for (uintptr_t* p_func = p_vtable; *p_func != NULL; ++p_func)
	{
		if (!helper::is_address_in_game_module((PVOID)(*p_func)))
		{
			std::cout << "Found invalid vmt func at: 0x" << std::hex << *p_func << std::endl;
			return false;
		}
	}

	return true;
}