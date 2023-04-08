#pragma once
namespace Feature
{
	Offsets::Currency* GetLocalCurrency() 
	{
		try {
			DWORD64* BaseAddress = (DWORD64*)(UnityPlayer + currency_Address);
			DWORD64* currency = (DWORD64*)(*BaseAddress + of_currency1);
			currency = (DWORD64*)(*currency + of_currency2);
			currency = (DWORD64*)(*currency + of_currency3);
			currency = (DWORD64*)(*currency + of_currency4); 
			currency = (DWORD64*)(*currency + of_currency5);
			currency = (DWORD64*)(*currency + of_currency6);

			return *(Offsets::Currency**)currency;
		}
		catch (...) {
			printf("%s\n", "°¥Ó´~Äã¸ÉÂï~~³ö´íÁËÀ²~");
			return static_cast<Offsets::Currency*>(nullptr);
		}
	}

	Offsets::Resource* GetLocalResource()
	{
		try {
			DWORD64* BaseAddress = (DWORD64*)(UnityPlayer + resource_Address);
			DWORD64* resource = (DWORD64*)(*BaseAddress + of_resource1);
			resource = (DWORD64*)(*resource + of_resource2);
			resource = (DWORD64*)(*resource + of_resource3);
			resource = (DWORD64*)(*resource + of_resource4);
			resource = (DWORD64*)(*resource + of_resource5);
			resource = (DWORD64*)(*resource + of_resource6);

			return *(Offsets::Resource**)resource;
		}
		catch (...) {
			printf("%s\n", "°¥Ó´~Äã¸ÉÂï~~³ö´íÁËÀ²~");
			return static_cast<Offsets::Resource*>(nullptr);
		}
	}
}