#include "includes.h"
using namespace std;

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
Present oPresent;
ResizeBuffers oResizeBuffers;

static bool init = false;
FILE* filePointer;

//窗口回调
LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) 
{
	if (uMsg == WM_KEYDOWN)
	{
		if (wParam == VK_INSERT) 
		{
			g_config::bMenuVisible = !g_config::bMenuVisible;
		}
	}

	//if (g_config::bImGuiIsInit)		//绘制鼠标
	//{
	//	ImGui::GetIO().MouseDrawCursor = g_config::bMenuVisible;
	//	if (g_config::bMenuVisible)
	//	{
	//		ImGui::GetIO().ConfigFlags &= ~ImGuiConfigFlags_NoMouse;
	//	}
	//	else
	//	{
	//		ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_NoMouse;
	//	}
	//}

	if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}


HRESULT __stdcall hkResizeBuffers(IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT Flags)
{
	// 释放之前的渲染目标视图
	if (mainRenderTargetView)
	{
		mainRenderTargetView->Release();
		mainRenderTargetView = nullptr;
		cout << "Release RenderTargetView" << endl;
	}

	// 获取并更新交换链缓冲区
	HRESULT hr = oResizeBuffers(pSwapChain, BufferCount, Width, Height, NewFormat, Flags);
	if (FAILED(hr)) return hr;
	cout << "Update ResizeBuffers" << endl;

	// 获取新的渲染目标视图
	ID3D11Texture2D* pBuffer = nullptr;
	hr = pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBuffer);
	if (FAILED(hr)) return hr;
	cout << "GetBuffer" << endl;

	// 创建新的渲染目标视图
	hr = pDevice->CreateRenderTargetView(pBuffer, nullptr, &mainRenderTargetView);
	pBuffer->Release();
	if (FAILED(hr)) return hr;
	cout << "CreateRenderTargetView" << endl;

	// 清除渲染目标视图并重新创建 ImGui 设备对象
	ImGui_ImplDX11_InvalidateDeviceObjects();
	ImGui_ImplDX11_CreateDeviceObjects();
	cout << "InvalidateDeviceObjects And CreateDeviceObjects" << endl;

	return hr;
}

DWORD __stdcall EjectThread(LPVOID lpParameter)
{
	Sleep(100);
	FreeLibraryAndExitThread(g_module, 0);
	return 0;
}

void shutdown(FILE* pFile, std::string reason)
{
	SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG_PTR)oWndProc);
	kiero::unbind(8);
	kiero::unbind(13);
	RELEASE_D3D(mainRenderTargetView);

	auto ctx = ImGui::GetCurrentContext();
	if (ctx && ctx->Initialized)
	{
		ImGui_ImplDX11_Shutdown();
		ImGui_ImplWin32_Shutdown();
		ImGui::DestroyContext();
	}

	std::cout << reason << std::endl;
	Sleep(1000);
	if (pFile != nullptr)
		fclose(pFile);
	FreeConsole();
	CreateThread(0, 0, EjectThread, 0, 0, 0);
}

//开始hook
HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
	if (!init)
	{
		// 尝试获取设备
		if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&pDevice)))
		{
			// 获取设备的上下文
			pDevice->GetImmediateContext(&pContext);
			// 获取交换链描述信息
			DXGI_SWAP_CHAIN_DESC sd;
			pSwapChain->GetDesc(&sd);
			// 获取窗口句柄
			hwnd = sd.OutputWindow;
			// 获取后备缓冲区
			ID3D11Texture2D* pBackBuffer;
			pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
			// 创建渲染目标视图
			pDevice->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetView);
			// 释放后备缓冲区
			pBackBuffer->Release();

			// 替换窗口过程函数
			oWndProc = (WNDPROC)SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG_PTR)WndProc);

			// ImGui初始化
			Init::ImGuiInit();
			std::cout << "ImGui初始化完成" << std::endl;

			Process = GetCurrentProcess();

			//全局取模块
			UnityPlayer = (DWORD64)GetModuleHandleA("UnityPlayer.dll");
			cout << "UnityPlayer: " << UnityPlayer << endl;

			//内存初始化
			Init::MemoryInit();
			std::cout << "内存初始化完成" << std::endl;

			init = true;
		}
		else
			return oPresent(pSwapChain, SyncInterval, Flags);	// 调用原始的EndScene函数
	}

	if (Process != NULL)
	{
		{
			ImGui_ImplDX11_NewFrame();
			ImGui_ImplWin32_NewFrame();
			ImGui::NewFrame();

			//菜单绘制线程
			Menu::Draw();

			//Update线程
			Loop::Update();

			ImGui::Render();

			pContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
			ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
		}
	}
	else
	{
		MessageBox(NULL, CN("无法找到当前进程"), CN("找了两年半我没有找到你这个进程！"), MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);
		shutdown(filePointer, "无法找到当前进程");
	}

	return oPresent(pSwapChain, SyncInterval, Flags);
}

//开始Kiero D3D11
DWORD WINAPI kieroThread(LPVOID lpReserved)
{
	AllocConsole();
	freopen_s(&filePointer, "CONOUT$", "w", stdout);

	std::cout << "start hook..." << std::endl;

	bool init_hook = false;

	do
	{
		if (kiero::init(kiero::RenderType::D3D11) == kiero::Status::Success)
		{
			kiero::bind(8, (void**)&oPresent, hkPresent);
			kiero::bind(13, (void**)&oResizeBuffers, hkResizeBuffers);
			init_hook = true;
		}
	} while (!init_hook);

	//卸载Dll
	while (true)
	{
		if (GetAsyncKeyState(VK_END))
			break;
	}
	shutdown(filePointer, "Un Load");
	
	return TRUE;
}

BOOL WINAPI DllMain(HMODULE hMod, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		g_module = hMod;
		CreateThread(nullptr, 0, kieroThread, hMod, 0, nullptr);
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}