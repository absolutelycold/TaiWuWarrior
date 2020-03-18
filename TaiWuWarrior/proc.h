#pragma once
#include <Windows.h>
#include <tchar.h>
#include <TlHelp32.h>
#include <stdio.h>
#include <iostream>
#include <vector>


DWORD getPIDByName(TCHAR* name);
HANDLE getProcessHandle(DWORD pid);
ULONGLONG getModuleBaseAddr(TCHAR* name, DWORD pid);
ULONGLONG getFinalAddddy(std::vector<DWORD> offsetVector, ULONGLONG BaseAddr, HANDLE hProcess);
BOOL writeToMemoryInt(HANDLE hProcess, ULONGLONG addr, DWORD value);
DWORD readMemoryInt(HANDLE hProcess, ULONGLONG addr);