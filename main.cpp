#pragma once
#include <Gui/Overlay/Overlay.hpp>
#include <Includes/Includes.hpp>
#include <Core/SDK/Memory.hpp>
#include <Includes/Utils.hpp>
#include <Core/SDK/SDK.hpp>
#include <Core/Core.hpp>
#include <Gui/gui.hpp>
#include <winternl.h>
#include <windows.h>
#include <dwmapi.h>
#include <tchar.h>
#include <vector>
#include <regex>
#include "../auth/auth.hpp"
#include <Security/AntiCrack.hpp>
#include <Includes/CustomWidgets/Custom.hpp>
#include <Includes/ImGui/Fonts.hpp>
#include <Includes/CustomWidgets/Notify.hpp>
#include "skStr.h"
#pragma comment (lib,"urlmon.lib")


                                              


RECT rc;

void style() {
	ImGuiStyle* style = &ImGui::GetStyle();
	style->WindowRounding = 10.0f;
	style->WindowPadding = ImVec2(0.f, 0.f);
	style->WindowBorderSize = 1.f;
	style->Alpha = 1.1f;
	style->Colors[ImGuiCol_WindowBg] = ImVec4(ImColor(14, 14, 14));
	style->Colors[ImGuiCol_ChildBg] = ImVec4(ImColor(255, 255, 255, 255));
	style->Colors[ImGuiCol_Border] = ImVec4(255, 255, 255, 0.0);
}

ID3D11Device* g_pd3dDevice = NULL;
ID3D11DeviceContext* g_pd3dDeviceContext = NULL;
IDXGISwapChain* g_pSwapChain = NULL;
ID3D11RenderTargetView* g_mainRenderTargetView = NULL;
D3DX11_IMAGE_LOAD_INFO info;
ID3DX11ThreadPump* pump{ nullptr };
HWND hwnd;

bool CreateDeviceD3D(HWND hWnd);
void CleanupDeviceD3D();
void CreateRenderTarget();
void CleanupRenderTarget();
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
ImVec2 window_size = ImVec2(400, 300);

void move_window() {
	ImGui::SetCursorPos(ImVec2(0, 0));
	if (ImGui::InvisibleButton("Move_detector", ImVec2(window_size.x, window_size.y)));
	if (ImGui::IsItemActive()) {
		GetWindowRect(hwnd, &rc);
		MoveWindow(hwnd, rc.left + ImGui::GetMouseDragDelta().x, rc.top + ImGui::GetMouseDragDelta().y, window_size.x, window_size.y, TRUE);
	}
}

inline std::string GetClipboardText() {
	std::string result = "";

	if (OpenClipboard(nullptr)) {
		HANDLE hData = GetClipboardData(CF_TEXT);
		if (hData) {
			char* pszText = static_cast<char*>(GlobalLock(hData));
			if (pszText) {
				result = pszText;
				GlobalUnlock(hData);
			}
		}
		CloseClipboard();
	}

	return result;
}


inline void CheatLogin() {
	// Inicializa o KeyAuth
	// KeyAuthApp.init();

	// if (!KeyAuthApp.data.success) {
	//	ExitProcess(0);
	// }

	// KeyAuthApp.license(std::string(g_MenuInfo.user));

	// if (!KeyAuthApp.data.success) {
	//	ExitProcess(0);
	// }

	g_MenuInfo.MenuSize = { 680, 500 };
	g_MenuInfo.IsLogged = true;
	Core::GetOffsets();

	ShowWindow(hwnd, SW_HIDE);
	int gay(); // 🚀 Inicia a injeção
}


bool flag = false;

bool render() {
	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(163, 163, 163)));
	ImGui::Dummy(ImVec2(0.0f, 2.0f)); // Espaço

	ImGui::SetCursorPos({ ((window_size.x - 130) * 0.5f), 100 });
	
	if (Custom::ButtonIJ(skCrypt("GO"), { 130, 130 }, 0)) {
		std::string clipboardText = GetClipboardText();

			std::thread{ CheatLogin }.detach();
			flag = true;
			std::thread([]() { Beep(100, 300); }).detach(); // Sucesso
			
	}

	ImGui::GetWindowDrawList()->AddText({ window_size.x / 2.4f - ImGui::CalcTextSize("Welcome to ").x / 2, window_size.y / 2 - ImGui::CalcTextSize("Welcome to ").y / 2 - 100 }, ImGui::GetColorU32(g_Col.TestingTest), "Welcome to ");
	ImGui::GetWindowDrawList()->AddText({ window_size.x / 1.6f - ImGui::CalcTextSize("Warning").x / 2, window_size.y / 2 - ImGui::CalcTextSize("Warning").y / 2 - 100 }, ImGui::GetColorU32(g_Col.Base), "Warning");
	ImGui::GetWindowDrawList()->AddText({ window_size.x / 2 - ImGui::CalcTextSize("Thank you very much for using our software.").x / 2, window_size.y / 2 - ImGui::CalcTextSize("Thank you very much for using our software.").y / 2 - 80 }, ImGui::GetColorU32(g_Col.SecundaryText), "Thank you very much for using our software.");

	ImGui::GetWindowDrawList()->AddText({ window_size.x / 2 - ImGui::CalcTextSize("Fivem.").x / 2, window_size.y / 2 - ImGui::CalcTextSize("Fivem.").y / 2 + 120 }, ImGui::GetColorU32(g_Col.Base), "Fivem.");

	ImGui::PopStyleColor();
	return flag;
}



int gay()
{
	if (!Mem.GetMaxPrivileges(GetCurrentProcess()))
	{
		//std::cout << xorstr( "[Error]: Failed GetMaxPrivileges\n" );
		//std::cin.get( );
		return 0;
	}


	//Utils::OpenConsole( );



	while (!g_Variables.g_hGameWindow)
	{

		g_Variables.g_hGameWindow = FindWindowA(xorstr("grcWindow"), nullptr);
		if (g_Variables.g_hGameWindow)
		{
			auto WindowInfo = Utils::GetWindowPosAndSize(g_Variables.g_hGameWindow);
			g_Variables.g_vGameWindowSize = WindowInfo.second;
			g_Variables.g_vGameWindowPos = WindowInfo.first;
			g_Variables.g_vGameWindowCenter = { g_Variables.g_vGameWindowSize.x / 2, g_Variables.g_vGameWindowSize.y / 2 };
			break;
		}

	}


	GetWindowThreadProcessId(g_Variables.g_hGameWindow, &g_Variables.ProcIdFiveM);
	//if (g_Variables.ProcIdFiveM != 0)
	//{

	//	g_Offsets.CurrentBuild = 0;

	//	if (ProcessName.find(xorstr("FiveM_b2060")) != std::string::npos)
	//	{
	//		g_Offsets.CurrentBuild = 2060;
	//	}
	//	else if (ProcessName.find(xorstr("FiveM_b2189")) != std::string::npos)
	//	{
	//		g_Offsets.CurrentBuild = 2189;
	//	}
	//	else if (ProcessName.find(xorstr("FiveM_b2372")) != std::string::npos)
	//	{
	//		g_Offsets.CurrentBuild = 2372;
	//	}
	//	else if (ProcessName.find(xorstr("FiveM_b2545")) != std::string::npos)
	//	{

	//		g_Offsets.CurrentBuild = 2545;
	//	}
	//	else if (ProcessName.find(xorstr("FiveM_b2612")) != std::string::npos)
	//	{

	//		g_Offsets.CurrentBuild = 2612;
	//	}
	//	else if (ProcessName.find(xorstr("FiveM_b2699")) != std::string::npos)
	//	{

	//		g_Offsets.CurrentBuild = 2699;
	//	}
	//	else if (ProcessName.find(xorstr("FiveM_b2802")) != std::string::npos)
	//	{

	//		g_Offsets.CurrentBuild = 2802;
	//	}
	//	else if (ProcessName.find(xorstr("FiveM_b2944")) != std::string::npos)
	//	{

	//		g_Offsets.CurrentBuild = 2944;

	//	}
	//	else if (ProcessName.find(xorstr("FiveM_b3095")) != std::string::npos)
	//	{

	//		g_Offsets.CurrentBuild = 3095;
	//	}
	//	else if (ProcessName.find(xorstr("FiveM_b3258")) != std::string::npos)
	//	{
	//		g_Offsets.CurrentBuild = 3258;
	//	}
	//	else if (ProcessName.find(xorstr("FiveM_GTAProcess")) != std::string::npos) {
	//		g_Offsets.CurrentBuild = 3258;

	//	}
	//	else {
	//		g_Offsets.CurrentBuild = 1604;
	//	}

	//	return 0;
	//}

	std::thread(&AntiCrack::DoProtect).detach();
	Core::SetupOffsets();
	Gui::cOverlay.Render();

	return 0;
}

int APIENTRY WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{

	/*AllocConsole();
	FILE* fDummy;
	freopen_s(&fDummy, "CONIN$", "r", stdin);
	freopen_s(&fDummy, "CONOUT$", "w", stderr);
	freopen_s(&fDummy, "CONOUT$", "w", stdout);*/

	WNDCLASSEXW wc;
	wc.cbSize = sizeof(WNDCLASSEXW);
	wc.style = CS_CLASSDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = NULL;
	wc.cbWndExtra = NULL;
	wc.hInstance = nullptr;
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = nullptr;
	wc.lpszMenuName = L" ";
	wc.lpszClassName = L" ";
	wc.hIconSm = LoadIcon(0, IDI_APPLICATION);

	RegisterClassExW(&wc);
	hwnd = CreateWindowExW(NULL, wc.lpszClassName, L" ", WS_POPUP, (GetSystemMetrics(SM_CXSCREEN) / 2) - (window_size.x / 2), (GetSystemMetrics(SM_CYSCREEN) / 2) - (window_size.y / 2), window_size.x, window_size.y, 0, 0, 0, 0);
	//gui::RenderBlur( globals.hwnd );

	//SetWindowDisplayAffinity(globals.hwnd, WDA_EXCLUDEFROMCAPTURE);

	SetWindowLongA(hwnd, GWL_EXSTYLE, GetWindowLong(hwnd, GWL_EXSTYLE) | WS_EX_LAYERED);
	SetLayeredWindowAttributes(hwnd, RGB(0, 0, 0), 255, LWA_ALPHA);

	MARGINS margins = { -1 };
	DwmExtendFrameIntoClientArea(hwnd, &margins);

	POINT mouse;
	rc = { 0 };
	GetWindowRect(hwnd, &rc);

	if (!CreateDeviceD3D(hwnd))
	{
		CleanupDeviceD3D();
		::UnregisterClassW(wc.lpszClassName, wc.hInstance);
		return 1;
	}


	::ShowWindow(hwnd, SW_SHOWDEFAULT);
	::UpdateWindow(hwnd);


	IMGUI_CHECKVERSION();
	ImGui::CreateContext(); {
		ImGui::StyleColorsDark();


		style();

	}
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	ImFontConfig cfg;
	cfg.FontBuilderFlags = ImGuiBackendFlags_None;
	cfg.FontDataOwnedByAtlas = false;
	io.Fonts->AddFontFromMemoryTTF(InterSemiBold, sizeof(InterSemiBold), 18.f, &cfg, io.Fonts->GetGlyphRangesCyrillic());

	//globals.m_FontSecundary = io.Fonts->AddFontFromMemoryTTF(montserrat_semibold_binary, sizeof(montserrat_semibold_binary), 14.f, &cfg, io.Fonts->GetGlyphRangesCyrillic());


	static const ImWchar icons_ranges[] = { 0xe000, 0xf8ff, 0 };
	ImFontConfig icons_config;
	icons_config.MergeMode = true;
	icons_config.PixelSnapH = true;
	icons_config.OversampleH = 3;
	icons_config.OversampleV = 3;

	static const ImWchar FontAwesomeRanges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };
	static const ImWchar FontAwesomeRangesBrands[] = { ICON_MIN_FAB, ICON_MAX_FAB, 0 };

	ImFontConfig FontAwesomeConfig;
	FontAwesomeConfig.MergeMode = true;
	FontAwesomeConfig.PixelSnapH = true;
	FontAwesomeConfig.GlyphMinAdvanceX = 17.f;

	//globals.FontAwesomeSolid = io.Fonts->AddFontFromMemoryCompressedTTF(FontAwesome6Solid_compressed_data, sizeof(FontAwesome6Solid_compressed_size), 17.f, &FontAwesomeConfig, FontAwesomeRanges);
	//globals.FontAwesomeRegular = io.Fonts->AddFontFromMemoryCompressedTTF(FontAwesome6Regular_compressed_data, sizeof(FontAwesome6Regular_compressed_size), 17.f, &FontAwesomeConfig, FontAwesomeRanges);
	//globals.FontAwesomeBrands = io.Fonts->AddFontFromMemoryCompressedTTF(FontAwesome6Brands_compressed_data, sizeof(FontAwesome6Brands_compressed_size), 17.f, &FontAwesomeConfig, FontAwesomeRangesBrands);

	io.IniFilename = nullptr;

	ImGui_ImplWin32_Init(hwnd);
	ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);

	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	static bool done = false;
	while (!done)
	{

		MSG msg;
		while (::PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
			if (msg.message == WM_QUIT)
				done = true;
		}

		if (done)
			break;

		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();

		static bool hide = true;
		static int opticaly = 255;
		/*if ( GetAsyncKeyState( VK_INSERT ) & 0x1 ) hide = !hide;
		if ( GetAsyncKeyState( VK_DELETE ) & 1 ) { exit( 0 ); }*/
		opticaly = ImLerp(opticaly, opticaly <= 255 && hide ? 300 : 0, ImGui::GetIO().DeltaTime * 8.f);
		if (opticaly > 255) opticaly = 255;

		SetLayeredWindowAttributes(hwnd, RGB(0, 0, 0), opticaly, LWA_ALPHA);

		//SetWindowDisplayAffinity(globals.hwnd, WDA_EXCLUDEFROMCAPTURE);

		ShowWindow(hwnd, opticaly > 0 ? SW_SHOW : SW_HIDE);

		ImGui::NewFrame();
		{
			ImGui::SetNextWindowPos({ 0, 0 }, ImGuiCond_Once);
			ImGui::SetNextWindowSize({ window_size.x, window_size.y }, ImGuiCond_Once);

			ImGui::Begin(" ", &done, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_::ImGuiWindowFlags_NoTitleBar);
			{

				if (!flag) {
					render();
					move_window();

				}
				else
				{
					ShowWindow(hwnd, SW_HIDE);
					done = true;
					gay();
				}

			}
			ImGui::End();
		}

		ImGui::Render();


		const float clear_color_with_alpha[4] = { 0 };
		g_pd3dDeviceContext->OMSetRenderTargets(1, &g_mainRenderTargetView, NULL);
		g_pd3dDeviceContext->ClearRenderTargetView(g_mainRenderTargetView, clear_color_with_alpha);
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

		g_pSwapChain->Present(1, 0);
	}

	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	CleanupDeviceD3D();
	::DestroyWindow(hwnd);
	::UnregisterClassW(wc.lpszClassName, wc.hInstance);

	return 0;
}

bool CreateDeviceD3D(HWND hWnd)
{
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 2;
	sd.BufferDesc.Width = 0;
	sd.BufferDesc.Height = 0;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = hWnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	UINT createDeviceFlags = 0;
	//createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
	D3D_FEATURE_LEVEL featureLevel;
	const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
	if (D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext) != S_OK)
		return false;

	CreateRenderTarget();
	return true;
}

void CleanupDeviceD3D()
{
	CleanupRenderTarget();
	if (g_pSwapChain) {
		g_pSwapChain->Release();
		g_pSwapChain = NULL;
	}

	if (g_pd3dDeviceContext) {
		g_pd3dDeviceContext->Release();
		g_pd3dDeviceContext = NULL;
	}

	if (g_pd3dDevice) {
		g_pd3dDevice->Release();
		g_pd3dDevice = NULL;
	}
}

void CreateRenderTarget()
{
	ID3D11Texture2D* pBackBuffer;
	g_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
	g_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &g_mainRenderTargetView);
	pBackBuffer->Release();
}

void CleanupRenderTarget()
{
	if (g_mainRenderTargetView) {
		g_mainRenderTargetView->Release();
		g_mainRenderTargetView = NULL;
	}
}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
		return true;

	switch (msg)
	{
	case WM_SIZE:
		if (g_pd3dDevice != NULL && wParam != SIZE_MINIMIZED)
		{
			CleanupRenderTarget();
			g_pSwapChain->ResizeBuffers(0, (UINT)LOWORD(lParam), (UINT)HIWORD(lParam), DXGI_FORMAT_UNKNOWN, 0);
			CreateRenderTarget();
		}
		return 0;
	case WM_SYSCOMMAND:
		if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
			return 0;
		break;
	case WM_DESTROY:
		::PostQuitMessage(0);
		return 0;
	}
	return ::DefWindowProc(hWnd, msg, wParam, lParam);
}







std::string hwid;