#pragma once
#include <Windows.h>
#include <tchar.h>
#include <TlHelp32.h>
#include "proc.h"
#include <vector>
#include <iostream>

class TaiWuInfo
{
public:

	DWORD processId = 0;
	HANDLE hProcess = NULL;
	ULONGLONG bdwgcModuleBaseAddr = 0;
	ULONGLONG UnityPlayerBaseAddr = 0;
	std::vector<DWORD> daysOffset = { 0x004A2308, 0x210, 0x170, 0x60, 0x38,  0x8, 0x10, 0x8EC};
	std::vector<DWORD> experienceOffset = { 0x004A2308, 0x210, 0x170, 0x60, 0x38, 0x8, 0x10, 0x8F0 };
	std::vector<DWORD> cuiOffset = { 0x004A2308, 0x210, 0x338, 0x18, 0x30, 0x18, 0xC0, 0x20 };
	std::vector<DWORD> qinOffset = { 0x004A2308, 0x210, 0x338, 0x18, 0x30, 0x18, 0xC0, 0x24 };
	std::vector<DWORD> huOffset = { 0x004A2308, 0x210, 0x338, 0x18, 0x30, 0x18, 0xC0, 0x28 };
	std::vector<DWORD> qiOffset = { 0x004A2308, 0x210, 0x338, 0x18, 0x30, 0x18, 0xC0, 0x2C };
	std::vector<DWORD> wuxingOffset = { 0x0229AAE0, 0x130 , 0xB8, 0xA8, 0x8, 0xB8, 0x58, 0x13C };
	
	ULONGLONG dayAddress = 0;
	ULONGLONG expAddr = 0;
	ULONGLONG cuiAddr = 0;
	ULONGLONG qinAddr = 0;
	ULONGLONG huAddr = 0;
	ULONGLONG qiAddr = 0;
	
	BOOL writeDay(DWORD num);
	BOOL AddExp(DWORD num);
	BOOL AddCuipo(DWORD num);
	BOOL AddQinyin(DWORD num);
	BOOL AddHuti(DWORD num);
	BOOL AddQiqiao(DWORD num);
	BOOL writeWuxing(DWORD num);

	TaiWuInfo(TCHAR* processName);
	~TaiWuInfo();
private:
	

};

