#include "pch.h"
#include "walker.h"

void walker::initialize_walker()
{
	// todo: implement flag system
	while (true)
	{
		suspicious_process_scan();
		Sleep(1000);

		verify_mem_pages();
		Sleep(1000);

		iat_integrity_check();
		Sleep(1000);
	}
}