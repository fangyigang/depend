#ifndef ULTRA_FIREWALL_H_
#define ULTRA_FIREWALL_H_

#include <Windows.h>
#include <string>
#include "Firewall/AddFireWall.h"

namespace ultra
{

	inline BOOL AddAppToFirewall(std::wstring sAppName, std::wstring sFireFlag)
	{
		BOOL bRet = TRUE;
		HRESULT hr = S_OK;
		HRESULT comInit = E_FAIL;
		INetFwProfile* fwProfile = NULL;

		// Initialize COM.
		comInit = CoInitializeEx(
			0,
			COINIT_APARTMENTTHREADED|COINIT_DISABLE_OLE1DDE
			);

		// Ignore RPC_E_CHANGED_MODE; this just means that COM has already been
		// initialized with a different mode. Since we don't care what the mode is,
		// we'll just use the existing mode.
		if (comInit != RPC_E_CHANGED_MODE)
		{
			hr = comInit;
			if (FAILED(hr))
			{
				printf("CoInitializeEx failed: 0x%08lx\n", hr);
				bRet = FALSE;
				goto error;
			}
		}

		// Retrieve the firewall profile currently in effect.
		hr = WindowsFirewallInitialize(&fwProfile);
		if (FAILED(hr))
		{
			printf("WindowsFirewallInitialize failed: 0x%08lx\n", hr);
			bRet = FALSE;
			goto error;
		}

		hr = WindowsFirewallAddApp(
			fwProfile,
			sAppName.data(),
			sFireFlag.data()
			);
		if (FAILED(hr))
		{
			printf("WindowsFirewallAddApp failed: 0x%08lx\n", hr);
			bRet = FALSE;
			goto error;
		}

error:

		// Release the firewall profile.
		WindowsFirewallCleanup(fwProfile);

		// Uninitialize COM.
		if (SUCCEEDED(comInit))
		{
			CoUninitialize();
		}
		return bRet;
	}

	inline BOOL AddPortToFirewall(int nPort, BOOL bTCP, std::wstring sFireFlag)
	{
		BOOL bRet = TRUE;
		HRESULT hr = S_OK;
		HRESULT comInit = E_FAIL;
		INetFwProfile* fwProfile = NULL;

		// Initialize COM.
		comInit = CoInitializeEx(
			0,
			COINIT_APARTMENTTHREADED|COINIT_DISABLE_OLE1DDE
			);

		// Ignore RPC_E_CHANGED_MODE; this just means that COM has already been
		// initialized with a different mode. Since we don't care what the mode is,
		// we'll just use the existing mode.
		if (comInit != RPC_E_CHANGED_MODE)
		{
			hr = comInit;
			if (FAILED(hr))
			{
				printf("CoInitializeEx failed: 0x%08lx\n", hr);
				bRet = FALSE;
				goto error;
			}
		}

		// Retrieve the firewall profile currently in effect.
		hr = WindowsFirewallInitialize(&fwProfile);
		if (FAILED(hr))
		{
			printf("WindowsFirewallInitialize failed: 0x%08lx\n", hr);
			bRet = FALSE;
			goto error;
		}

		NET_FW_IP_PROTOCOL_ nType = NET_FW_IP_PROTOCOL_TCP;
		if (bTCP == FALSE)
		{
			nType = NET_FW_IP_PROTOCOL_UDP;
		}
		// Add port to list of globally open ports.
		hr = WindowsFirewallPortAdd(fwProfile, nPort, nType, sFireFlag.data());
		if (FAILED(hr))
		{
			printf("WindowsFirewallPortAdd failed: 0x%08lx\n", hr);
			bRet = FALSE;
			goto error;
		}

error:

		// Release the firewall profile.
		WindowsFirewallCleanup(fwProfile);

		// Uninitialize COM.
		if (SUCCEEDED(comInit))
		{
			CoUninitialize();
		}
		return bRet;
	}
	/**/

}


#endif