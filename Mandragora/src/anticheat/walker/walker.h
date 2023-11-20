#pragma once

class walker
{
private:
	bool suspicious_process_scan();
	bool verify_mem_pages();
	bool iat_integrity_check();
public:
	void initialize_walker();
};