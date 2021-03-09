#include <Windows.h>
#include <stdio.h>
#include <iostream>

int main()
{
	DWORD err;
	// path to our dll
	LPCSTR DllPath = "ENTER DLL PATH HERE";
	// enter PID of process
	DWORD PID = 0000; 

	// Get LoadLibrary function address –
	// the address doesn't change at remote process
	PVOID addrLoadLibrary = (LPVOID)GetProcAddress(GetModuleHandle(L"kernel32.dll"), "LoadLibraryA");
	// Open remote process
	HANDLE proc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, PID); 
	// Get a pointer to memory location in remote process,
	// big enough to store DLL path
	PVOID memAddr = VirtualAllocEx(proc, 0, strlen(DllPath) + 1, MEM_COMMIT, PAGE_READWRITE);
	if (NULL == memAddr) {
		err = GetLastError();
		return 0;
	}
	// Write DLL name to remote process memory
	BOOL check = WriteProcessMemory(proc, (LPVOID)memAddr, DllPath, strlen(DllPath) + 1, NULL);
	if (0 == check) {
		err = GetLastError();
		std::cout << err;
		system("PAUSE");
		return 0;
	}
	// Open remote thread, while executing LoadLibrary
	// with parameter DLL name, will trigger DLLMain
	HANDLE hRemote = CreateRemoteThread(proc, NULL, NULL, (LPTHREAD_START_ROUTINE)LoadLibrary, memAddr, 0, 0);
	if (NULL == hRemote) {
		err = GetLastError();
		std::cout << err;
		system("PAUSE");
		return 0;
	}
	WaitForSingleObject(hRemote, INFINITE);
	check = CloseHandle(hRemote);
	system("PAUSE");
	return 0;
}

