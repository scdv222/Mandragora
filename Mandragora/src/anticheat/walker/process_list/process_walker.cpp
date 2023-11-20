#include "pch.h"
#include "anticheat/walker/walker.h"

bool is_suspicious_process(const std::wstring& process_name)
{
	const std::vector<std::wstring> blacklist = {
		L"cheatengine.exe", L"x32dbg.exe", L"reclass.exe", L"reclassex.exe"
	};

	std::wstring lower_case_name = process_name;
	std::transform(lower_case_name.begin(), lower_case_name.end(), lower_case_name.begin(), ::tolower);

	return std::find(blacklist.begin(), blacklist.end(), lower_case_name) != blacklist.end();
}


bool walker::suspicious_process_scan()
{
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (!snapshot || snapshot == INVALID_HANDLE_VALUE)
		return false;

	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(PROCESSENTRY32);

	if (Process32First(snapshot, &pe32))
	{
		do {
			if (is_suspicious_process(pe32.szExeFile)) {
				std::cout << "[!] Process detected: " << pe32.szExeFile << std::endl;
				return false;
			}
		} while (Process32Next(snapshot, &pe32));
	}

	CloseHandle(snapshot);

	return true;
}
