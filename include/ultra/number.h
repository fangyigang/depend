#ifndef ULTRA_NUMBER_H
#define ULTRA_NUMBER_H

#include <cstdlib>
#include <algorithm>
#include <Windows.h>
#include <WinDef.h>


namespace ultra
{

inline DWORD GetProgress(DWORD dwSmall, DWORD dwBig)
{
	if (dwBig == 0 && dwSmall == 0)
	{
		return 0;
	}
	if (dwSmall < 0 || dwBig <= 0)
	{
		return -1;
	}
	return min((UINT64)dwSmall*100/dwBig, 100);
}

}

#endif