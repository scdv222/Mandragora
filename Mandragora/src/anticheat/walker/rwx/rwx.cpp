#include "pch.h"
#include "anticheat/walker/walker.h"
#include "anticheat/stub/helper/helper.h"

bool is_address_in_peb(LPCVOID address)
{
	std::vector<MODULEENTRY32> modules = helper::get_all_modules();

	uintptr_t addr = reinterpret_cast<uintptr_t>(address);
	for (const auto& module : modules)
	{
		uintptr_t module_start = reinterpret_cast<uintptr_t>(module.modBaseAddr);
		uintptr_t module_end = module_start + module.modBaseSize;
		if (addr >= module_start && addr < module_end)
			return true;
	}

	return false;
}

bool walker::verify_mem_pages()
{
	SYSTEM_INFO sys_info;
	GetSystemInfo(&sys_info);
	LPCVOID max_addr = sys_info.lpMaximumApplicationAddress;
	LPCVOID address = sys_info.lpMinimumApplicationAddress;

	MEMORY_BASIC_INFORMATION mbi{};
	while (address < max_addr)
	{
		if (VirtualQuery(address, &mbi, sizeof(mbi)) == 0)
			break;

		
		if ((mbi.Protect & PAGE_EXECUTE_READWRITE) || (mbi.Protect & PAGE_EXECUTE_READ))
		{
			if (!is_address_in_peb(mbi.BaseAddress))
			{
				std::cout << "Unmapped memory region found at: " << std::hex << mbi.BaseAddress << std::endl;
				return false;
			}
		}

		address = static_cast<const char*>(mbi.BaseAddress) + mbi.RegionSize;
	}

	return true;
}