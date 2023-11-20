#pragma once

namespace helper
{
	bool is_address_in_our_module(PVOID addr);
	bool is_address_in_game_module(PVOID addr);
	bool is_address_within_specified_module(PVOID addr, const char* module_name);
	std::vector<MODULEENTRY32> get_all_modules();
}
