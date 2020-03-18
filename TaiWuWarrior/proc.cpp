#include "proc.h"

DWORD getPIDByName(TCHAR* name)
{
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnap == INVALID_HANDLE_VALUE)
	{
		return 0;
	}

	PROCESSENTRY32 pe;
	pe.dwSize = sizeof(PROCESSENTRY32);


	if (Process32First(hSnap, &pe))
	{

		do
		{
			if (_tcscmp(pe.szExeFile, name) == 0) {
				CloseHandle(hSnap);
				return pe.th32ProcessID;
			}

		} while (Process32Next(hSnap, &pe));

	}
	return 0;
}

HANDLE getProcessHandle(DWORD pid) {
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, pid);
	if (hProcess != NULL)
	{
		return hProcess;
	}
	else
	{
		return NULL;
	}
}

ULONGLONG getModuleBaseAddr(TCHAR* name, DWORD pid) {

	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, pid);

	if (hSnap == INVALID_HANDLE_VALUE)
	{
		DWORD error = GetLastError();
		return NULL;
	}

	MODULEENTRY32 me;
	me.dwSize = sizeof(MODULEENTRY32);

	if (Module32First(hSnap, &me))
	{
		do
		{
			if (_tcscmp(me.szModule, name) == 0)
			{
				CloseHandle(hSnap);
				return (ULONGLONG)(me.modBaseAddr);
			}
		} while (Module32Next(hSnap, &me));
	}
}

ULONGLONG getFinalAddddy(std::vector<DWORD> offsetVector, ULONGLONG BaseAddr, HANDLE hProcess)
{
	DWORD offsetNum = offsetVector.size();

	ULONGLONG myAddy = BaseAddr;

	for (int i = 0; i < offsetNum - 1; i++)
	{
		ReadProcessMemory(hProcess, LPCVOID(myAddy + offsetVector[i]), &myAddy, sizeof(ULONGLONG), NULL);
	}

	myAddy += offsetVector[offsetNum - 1];

	return myAddy;
}

BOOL writeToMemoryInt(HANDLE hProcess, ULONGLONG addr, DWORD value)
{
	SIZE_T sizeToWrite = 0;
	DWORD prevProtect = 0;
	VirtualProtectEx(hProcess, (LPVOID)addr, 4, PAGE_READWRITE, &prevProtect);
	if (WriteProcessMemory(hProcess, (LPVOID)addr, &value, 4, &sizeToWrite) == 0) {
		MessageBox(NULL, TEXT("Error to write process memory"), NULL, NULL);
		VirtualProtectEx(hProcess, (LPVOID)addr, 4, prevProtect, &prevProtect);
		return FALSE;
	}
	VirtualProtectEx(hProcess, (LPVOID)addr, 4, prevProtect, &prevProtect);
	return TRUE;
}

DWORD readMemoryInt(HANDLE hProcess, ULONGLONG addr)
{
	DWORD value = 0;

	ReadProcessMemory(hProcess, (LPCVOID)addr, &value, 4, NULL);

	return value;
}
