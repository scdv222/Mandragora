#include "pch.h"
#include "anticheat/walker/walker.h"
#include "anticheat/stub/helper/helper.h"

bool walker::iat_integrity_check()
{
	LPVOID executable_base = GetModuleHandle(nullptr);
	PIMAGE_DOS_HEADER dos_headers = (PIMAGE_DOS_HEADER)executable_base;
	PIMAGE_NT_HEADERS nt_headers = (PIMAGE_NT_HEADERS)((DWORD_PTR)executable_base + dos_headers->e_lfanew);

	IMAGE_DATA_DIRECTORY imports_directory = nt_headers->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT];
	PIMAGE_IMPORT_DESCRIPTOR import_descriptor = (PIMAGE_IMPORT_DESCRIPTOR)(imports_directory.VirtualAddress + (DWORD_PTR)executable_base);

	while (import_descriptor->Name != NULL)
	{
		LPCSTR library_name = (LPCSTR)import_descriptor->Name + (DWORD_PTR)executable_base;

		PIMAGE_THUNK_DATA original_first_thunk = (PIMAGE_THUNK_DATA)((DWORD_PTR)executable_base + import_descriptor->OriginalFirstThunk);
		PIMAGE_THUNK_DATA first_thunk = (PIMAGE_THUNK_DATA)((DWORD_PTR)executable_base + import_descriptor->FirstThunk);

		while (original_first_thunk->u1.AddressOfData != NULL)
		{
			PIMAGE_IMPORT_BY_NAME import_by_name = (PIMAGE_IMPORT_BY_NAME)((DWORD_PTR)executable_base + original_first_thunk->u1.AddressOfData);
			PROC* function = (PROC*)&first_thunk->u1.Function;

			if (!helper::is_address_within_specified_module((PVOID)*function, library_name))
			{
				std::cout << "[!] IAT Modification found. Modified function: " << import_by_name->Name << " in module: " << library_name << std::endl;
				return false;
			}

			++original_first_thunk;
			++first_thunk;
		}
	}
	return true;
}