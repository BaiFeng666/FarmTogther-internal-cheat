#pragma once
namespace Init
{
	void ImGuiInit()
	{
		//ImGui ³õÊ¼»¯
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();

		io.IniFilename = nullptr;
		io.LogFilename = nullptr;
		SimheiFont = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\msyh.ttc", 16.f, NULL, io.Fonts->GetGlyphRangesChineseFull());
		ImGui_ImplWin32_Init(hwnd);
		ImGui_ImplDX11_Init(pDevice, pContext);

		ImGui::StyleColorsLight();

		ImGuiStyle* style = &ImGui::GetStyle();
		style->FrameBorderSize = 1;
		style->FrameRounding = 3;
		style->GrabRounding = 3;
		style->WindowBorderSize = 0;
		style->GrabMinSize = 10;

		g_config::bImGuiIsInit = true;
	}

	void MemoryInit()
	{
			
	}
}