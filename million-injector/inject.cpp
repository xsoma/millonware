#include <windows.h>

int main() {
	const auto csgo_window = FindWindowA(0, "Counter-Strike: Global Offensive");

	char dll_name[] = "million-sdk.dll";
	char dll_path[256] = { 0 };

	GetFullPathNameA(dll_name, 256, dll_path, 0);

	auto pid = 0ul;
	GetWindowThreadProcessId(csgo_window, &pid);

	const auto process = OpenProcess(PROCESS_ALL_ACCESS, false, pid);
	
	const auto remote_memory = VirtualAllocEx(process, 0x0, strlen(dll_path) + 1, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	WriteProcessMemory(process, remote_memory, dll_path, strlen(dll_path), 0);
	
	const auto load_lib = reinterpret_cast<void*>(GetProcAddress(GetModuleHandleA("kernel32.dll"), "LoadLibraryA"));

	const auto thread = CreateRemoteThread(process, nullptr, 0, 
		reinterpret_cast<LPTHREAD_START_ROUTINE>(load_lib), remote_memory, 0, nullptr);

	WaitForSingleObject(thread, INFINITE);
	CloseHandle(thread);
	
	VirtualFreeEx(process, remote_memory, strlen(dll_path) + 1, MEM_FREE);

	CloseHandle(process);
}