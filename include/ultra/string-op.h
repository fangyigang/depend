#ifndef ULTRA_STRING_OP_H
#define ULTRA_STRING_OP_H

#include <Windows.h>
#include <wchar.h>
#include <cwctype>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

namespace ultra {
	
inline std::wstring _A2T( const std::string& strOrigin )
{
	std::wstring wstrTarget;
	int nLen = MultiByteToWideChar(CP_ACP, 0, strOrigin.c_str(), strOrigin.length()+1, NULL, NULL);
	
	wchar_t* pTarget = new wchar_t[nLen];
	ZeroMemory(pTarget, nLen*sizeof(wchar_t));
	MultiByteToWideChar(CP_ACP, 0, strOrigin.c_str(), strOrigin.length()+1, pTarget, nLen);

	wstrTarget = pTarget;
	delete pTarget;
	pTarget = NULL;
	return wstrTarget;
}

inline std::string _T2A( const std::wstring& wstrOrigin )
{
	std::string strTarget;
	int nLen = WideCharToMultiByte(CP_ACP, 0, wstrOrigin.c_str(), wstrOrigin.length()+1, NULL, NULL, NULL, NULL);

	char* pBuffer = new char[nLen];
	ZeroMemory(pBuffer, nLen*sizeof(char));
	WideCharToMultiByte(CP_ACP, 0, wstrOrigin.c_str(), wstrOrigin.length()+1, pBuffer, nLen, NULL, NULL);

	strTarget = pBuffer;
	delete pBuffer;
	pBuffer = NULL;
	return strTarget;
}

inline std::string _T2UTF( const std::wstring& wstrOrigin )
{
	std::string strTarget;
	int nLen = WideCharToMultiByte(CP_UTF8, 0, wstrOrigin.c_str(), wstrOrigin.length()+1, NULL, NULL, NULL, NULL);

	char* pBuffer = new char[nLen];
	ZeroMemory(pBuffer, nLen*sizeof(char));
	WideCharToMultiByte(CP_UTF8, 0, wstrOrigin.c_str(), wstrOrigin.length()+1, pBuffer, nLen, NULL, NULL);
	
	strTarget = pBuffer;
	delete pBuffer;
	pBuffer = NULL;
	return strTarget;
}

inline std::wstring _UTF2T( const std::string& strOrigin )
{
	std::wstring wstrTarget;
	int nLen = MultiByteToWideChar(CP_UTF8, 0, strOrigin.c_str(), strOrigin.length()+1, NULL, NULL);

	wchar_t* pTarget = new wchar_t[nLen];
	ZeroMemory(pTarget, nLen*sizeof(wchar_t));
	MultiByteToWideChar(CP_UTF8, 0, strOrigin.c_str(), strOrigin.length()+1, pTarget, nLen);
	
	wstrTarget = pTarget;
	delete pTarget;
	pTarget = NULL;
	return wstrTarget;
}

inline std::string _UTF2A( const std::string& strOrigin )
{
	return _T2A(_UTF2T(strOrigin));
}

inline std::string _A2UTF( const std::string& strOrigin )
{
	return _T2UTF(_A2T(strOrigin));
}

inline std::string ToUpper( std::string str )
{
	std::transform(str.begin(), str.end(), str.begin(), toupper);
	return str;
}

inline std::string ToLower( std::string str )
{
	std::transform(str.begin(), str.end(), str.begin(), tolower);
	return str;
}

inline std::wstring ToUpper( std::wstring wstr )
{
	std::transform(wstr.begin(), wstr.end(), wstr.begin(), toupper);
	return wstr;
}

inline std::wstring ToLower( std::wstring wstr )
{
	std::transform(wstr.begin(), wstr.end(), wstr.begin(), tolower);
	return wstr;
}

inline int CompareWcharNoCase( wchar_t c1, wchar_t c2)
{
	c1 = std::towupper(c1);
	c2 = std::towupper(c2);

	if (c1 == c2)
	{
		return 0;
	}
	else
	{
		return c1 < c2 ? -1 : 1;
	}
}

inline int CompareStringNoCase( const std::wstring& wstrComp1, const std::wstring& wstrComp2 )
{
	return wcsicmp(wstrComp1.c_str(), wstrComp2.c_str());
}

inline int CompareStringNoCase( const std::string& strComp1, const std::string& strComp2 )
{
	return stricmp(strComp1.c_str(), strComp2.c_str());
}

inline std::string ReplaceString( std::string& str, const std::string& strSrc, const std::string& strDst)
{
	std::string::size_type nPos = 0;
	std::string::size_type nSlen = strSrc.size();
	std::string::size_type nDlen = strDst.size();

	while( (nPos = str.find(strSrc, nPos)) != std::string::npos )
	{
		str.replace( nPos, nSlen, strDst );
		nPos += nDlen;
	}

	return str;
}

inline std::wstring ReplaceString( std::wstring& str, const std::wstring& strSrc, const std::wstring& strDst )
{
	std::wstring::size_type nPos = 0;
	std::wstring::size_type nSlen = strSrc.size();
	std::wstring::size_type nDlen = strDst.size();

	while( (nPos = str.find(strSrc, nPos)) != std::wstring::npos )
	{
		str.replace( nPos, nSlen, strDst );
		nPos += nDlen;
	}

	return str;
} 

template <class T>
inline std::string ConvertToString(T value)
{
	std::stringstream ss;
	ss << value;
	return ss.str();
}

template <class T>
inline std::wstring ConvertToWString(T value)
{
	std::wstringstream ss;
	ss << value;
	return ss.str();
}

template <class T1, class T2>
inline T2 ConvertA(T1 value)
{
	std::stringstream ss;
	ss << value;
	T2 result;
	ss >> result;
	return result;
}

template <class T1, class T2>
inline T2 Convert(T1 value)
{
	std::wstringstream ss;
	ss << value;
	T2 result;
	ss >> result;
	return result;
}


inline bool SplitString( const std::wstring wstrSrc, const std::wstring wstrSep, std::vector< std::wstring >* vec )
{
	if (wstrSrc.empty())
	{
		return false;
	}
	vec->clear();
	if (wstrSep.empty())
	{
		vec->push_back(wstrSrc);
		return true;
	}

	int nPos;
	std::wstring wstrTmp(wstrSrc);
	std::wstring wstrItem;
	int nSepLen = wstrSep.length();
	while ((nPos = wstrTmp.find(wstrSep)) != std::wstring::npos)
	{
		wstrItem = wstrTmp.substr(0, nPos);
		if (!wstrItem.empty())
		{
			vec->push_back(wstrItem);
		}
		wstrTmp = wstrTmp.substr(nPos + nSepLen);
	}

	if (!wstrTmp.empty())
	{
		vec->push_back(wstrTmp);
	}
	return true;
}

inline bool SplitList( const std::wstring wstrSrc, const std::wstring wstrSep1, const std::wstring wstrSep2, std::vector< std::vector< std::wstring > >* vec )
{
	std::vector< std::wstring > tempVec, temp;
	if (wstrSrc.empty())
	{
		return false;
	}
	vec->clear();
	SplitString(wstrSrc, wstrSep1, &tempVec);
	for (int i = 0; i < tempVec.size(); i++)
	{
		SplitString(tempVec.at(i), wstrSep2, &temp);
		vec->push_back(temp);
	}
	return true;
}


}
#endif