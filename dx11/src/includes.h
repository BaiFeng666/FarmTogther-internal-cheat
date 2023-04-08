#pragma once
#define RELEASE_D3D(p) if(p) { p->Release(); p = nullptr; }
#define memoryFix(add) if (add == 0x0) MsgBox(0,"error",0,0)
#define CN(str) (const char*)u8##str

#include<d3d11.h>

#include<windows.h>
#include<string>
#include<iostream>
#include<dxgi.h>

#include"../ImGui/imconfig.h"
#include"../ImGui/imgui.h"
#include"../ImGui/imgui_impl_dx11.h"
#include"../ImGui/imgui_impl_win32.h"
#include"../ImGui/imgui_internal.h"

#include"../Kiero/kiero.h"


typedef HRESULT(_stdcall* Present)(IDXGISwapChain* pSwapChain, UINT SyncInterval,UINT Flags);
typedef HRESULT(__stdcall* ResizeBuffers)(IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags);

ID3D11Device* pDevice = NULL;
ID3D11RenderTargetView* mainRenderTargetView;
ID3D11DeviceContext* pContext = NULL;
HWND hwnd = NULL;
WNDPROC oWndProc;

HMODULE g_module;
HANDLE Process;
DWORD64 UnityPlayer;
ImFont* SimheiFont;

#include "g_config.h"
#include "Feature/Offsets.hpp"
#include "Gui/Init.hpp"

#include "Feature/Feature.hpp"
#include "Gui/Menu.hpp"
#include "Feature/Loop.hpp"



