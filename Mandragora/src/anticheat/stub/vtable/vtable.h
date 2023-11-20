#pragma once

namespace stub
{
	namespace vmt
	{
		bool verify_vtable_pointer(void* instance); // checks for shadow vmt
		bool verify_vtable_integrity(void* instance); // checks function pointers within vtable
	}
}

