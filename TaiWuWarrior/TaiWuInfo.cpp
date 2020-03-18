#include "TaiWuInfo.h"


TaiWuInfo::TaiWuInfo(TCHAR* processName)
{
	processId = getPIDByName(processName);
	if (processId != 0)
	{
		hProcess = getProcessHandle(processId);
	}
	if (processId != 0)
	{
		bdwgcModuleBaseAddr = getModuleBaseAddr((TCHAR*)(TEXT("mono-2.0-bdwgc.dll")), processId);
		UnityPlayerBaseAddr = getModuleBaseAddr(PTCHAR(TEXT("UnityPlayer.dll")), processId);
	}
	if (bdwgcModuleBaseAddr != 0)
	{
		dayAddress = getFinalAddddy(daysOffset, bdwgcModuleBaseAddr, hProcess);
		expAddr = getFinalAddddy(experienceOffset, bdwgcModuleBaseAddr, hProcess);
		cuiAddr = getFinalAddddy(cuiOffset, bdwgcModuleBaseAddr, hProcess);
		qinAddr = getFinalAddddy(qinOffset, bdwgcModuleBaseAddr, hProcess);
		huAddr = getFinalAddddy(huOffset, bdwgcModuleBaseAddr, hProcess);
		qiAddr = getFinalAddddy(qiOffset, bdwgcModuleBaseAddr, hProcess);
		buildTimeAddr = getFinalAddddy(buildTimeOffset, UnityPlayerBaseAddr, hProcess);

	}

}

TaiWuInfo::~TaiWuInfo()
{
	if (hProcess != NULL)
	{
		CloseHandle(hProcess);
	}
	
}

BOOL TaiWuInfo::writeDay(DWORD num)
{
	return writeToMemoryInt(hProcess, dayAddress, 30);
}

BOOL TaiWuInfo::AddExp(DWORD num)
{
	DWORD currentExp = readMemoryInt(hProcess, expAddr);
	return writeToMemoryInt(hProcess, expAddr, currentExp + num);
}

BOOL TaiWuInfo::AddCuipo(DWORD num)
{
	DWORD currentCuipo = readMemoryInt(hProcess, cuiAddr);
	return writeToMemoryInt(hProcess, cuiAddr, currentCuipo + num);
}

BOOL TaiWuInfo::AddQinyin(DWORD num)
{
	DWORD currentQinyin = readMemoryInt(hProcess, qinAddr);
	return writeToMemoryInt(hProcess, qinAddr, currentQinyin + num);
}

BOOL TaiWuInfo::AddHuti(DWORD num)
{
	DWORD currentHuti = readMemoryInt(hProcess, huAddr);
	return writeToMemoryInt(hProcess, huAddr, currentHuti + num);
}

BOOL TaiWuInfo::AddQiqiao(DWORD num)
{
	DWORD currentQiqiao = readMemoryInt(hProcess, qiAddr);
	return writeToMemoryInt(hProcess, qiAddr, currentQiqiao + num);
}

BOOL TaiWuInfo::writeWuxing(DWORD num)
{
	ULONGLONG wuxingAddr = getFinalAddddy(wuxingOffset, UnityPlayerBaseAddr, hProcess);
	return writeToMemoryInt(hProcess, wuxingAddr, num);
}

BOOL TaiWuInfo::zeroBuildTime()
{
	buildTimeAddr = getFinalAddddy(buildTimeOffset, UnityPlayerBaseAddr, hProcess);
	return writeToMemoryInt(hProcess, buildTimeAddr, 0);
}

BOOL TaiWuInfo::infiniteHeart()
{
	heartAddr = getFinalAddddy(heartOffset, UnityPlayerBaseAddr, hProcess);
	return writeToMemoryInt(hProcess, heartAddr, 99);
}

BOOL TaiWuInfo::zeroBuildLabor()
{
	buildLaborAddr = getFinalAddddy(buildLaborOffset, UnityPlayerBaseAddr, hProcess);
	return writeToMemoryInt(hProcess, buildLaborAddr, 0);
}


