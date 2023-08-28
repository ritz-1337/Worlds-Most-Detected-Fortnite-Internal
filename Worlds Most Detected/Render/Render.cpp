#include "Render.h"
#include "../Settings.h"
#include <thread>
#include "../Hooks/Polyhook2/Detour/ADetour.hpp"
#include "../Hooks/Polyhook.h"
#include "../Cheat/Cheat.h"
#include "../Util.h"

bool firstTime = true;

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WndProcHook(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (Settings.ShowMenu && ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam)) {

	}

	return CallWindowProc(oWndProc, hWnd, msg, wParam, lParam);
}

__declspec(noinline) HRESULT D3D11Present(IDXGISwapChain* swap, UINT sync_interval, UINT flags)
{
	
		ID3D11Texture2D* pRenderTargetTexture;
		
		if (firstTime || !g_pRenderTargetView) {
			swap->GetDevice(__uuidof(ID3D11Device), (void**)&uDevice);

			if (!uDevice) return false;

			uDevice->GetImmediateContext(&m_pContext);

			if (!m_pContext) return false;

			if (SUCCEEDED(swap->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pRenderTargetTexture)))
			{
				uDevice->CreateRenderTargetView(pRenderTargetTexture, NULL, &g_pRenderTargetView);
				pRenderTargetTexture->Release();
				uDevice->Release();
			}

			m_pContext->RSGetViewports(&vps, &viewport);

			Width = viewport.Width;
			Height = viewport.Height;


			IMGUI_CHECKVERSION();
			ImGui::CreateContext();
			ImGuiIO& io = ImGui::GetIO(); (void)io;

			ImGui::StyleColorsDark();

			ImGui_ImplWin32_Init(Gamewindow);
			ImGui_ImplDX11_Init(uDevice, m_pContext);
			ImGui_ImplDX11_CreateDeviceObjects();
			oWndProc = reinterpret_cast<WNDPROC>(SetWindowLongPtrW(Gamewindow, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(WndProcHook)));
			firstTime = false;
	}
		

	if (g_pRenderTargetView)
	{

		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0, 0, 0, 0));
		ImGui::Begin(("##scene"), nullptr, ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoTitleBar);

		auto& io = ImGui::GetIO();
		ImGui::SetWindowPos(ImVec2(0, 0), ImGuiCond_Always);
		ImGui::SetWindowSize(ImVec2(io.DisplaySize.x, io.DisplaySize.y), ImGuiCond_Always);
		//draw
		//ImGui::GetWindowDrawList()->AddCircle(ImVec2(1920 / 2, 1080 / 2), 50, ImColor(200, 50, 200), 99, 3);
		CheatTick();
		ImGui::End();
		ImGui::PopStyleColor();
		ImGui::PopStyleVar(2);

		if (GetAsyncKeyState(VK_INSERT) & 1)
			Settings.ShowMenu = !Settings.ShowMenu;

		if (Settings.ShowMenu)
		{
			ImGui::Begin("Menu");

			DrawHighlightMenu();

			ImGui::End();
			ImGui::GetIO().MouseDrawCursor = true;
		}
		else {
			ImGui::GetIO().MouseDrawCursor = false;
		}

		ImGui::EndFrame();
		ImGui::Render();
		m_pContext->OMSetRenderTargets(1, &g_pRenderTargetView, NULL);
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	}

	
	return PLH::FnCast(PresentOriginal, &D3D11Present)(swap, sync_interval, flags);
}


__declspec(noinline) HRESULT ResizeHook(IDXGISwapChain* swapChain, UINT bufferCount, UINT width, UINT height, DXGI_FORMAT newFormat, UINT swapChainFlags) {

	ImGui_ImplDX11_Shutdown();
	g_pRenderTargetView->Release();
	m_pContext->Release();
	uDevice->Release();

	g_pRenderTargetView = nullptr;
	uDevice = nullptr;

	return PLH::FnCast(ResizeOriginal, &ResizeHook)(swapChain, bufferCount, width, height, newFormat, swapChainFlags);
}

__declspec(noinline) void StartInitDX11() {
	do
	{
		Gamewindow = FindWindowA((LPCSTR)NULL, (LPCSTR)FortniteWindow);
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	} while (!Gamewindow);

	if (FindWindowA((LPCSTR)("SplashScreen"), (LPCSTR)NULL)) {
		do
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		} while (FindWindowA((LPCSTR)("SplashScreen"), (LPCSTR)NULL));
	}

	Gamewindow = FindWindowA((LPCSTR)NULL, (LPCSTR)FortniteWindow);

	//std::this_thread::sleep_for(std::chrono::seconds(5));
	

	D3D_FEATURE_LEVEL requestedLevels[] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_1 };
	D3D_FEATURE_LEVEL obtainedLevel;
	ID3D11Device* d3dDevice = nullptr;
	ID3D11DeviceContext* d3dContext = nullptr;

	std::this_thread::sleep_for(std::chrono::milliseconds(2));

	DXGI_SWAP_CHAIN_DESC scd;
	ZeroMemory(&scd, sizeof(scd));
	scd.BufferCount = 1;
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scd.OutputWindow = Gamewindow;
	scd.SampleDesc.Count = (UINT)1;
	scd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	scd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	scd.Windowed = true;

	UINT createFlags = 0;
#ifdef _DEBUG
	createFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	IDXGISwapChain* d3dSwapChain = 0;
	UINT FeatureLevels = (UINT)sizeof(requestedLevels) / sizeof(D3D_FEATURE_LEVEL);
	IDXGIAdapter* Adapter = NULL;
	HMODULE MODULE = NULL;

	if (FAILED(D3D11CreateDeviceAndSwapChain(
		Adapter,
		D3D_DRIVER_TYPE_HARDWARE,
		MODULE,
		createFlags,
		(CONST D3D_FEATURE_LEVEL*)requestedLevels,
		FeatureLevels,
		(UINT)D3D11_SDK_VERSION,
		(CONST DXGI_SWAP_CHAIN_DESC*) & scd,
		&g_pSwapChain,
		&uDevice,
		&obtainedLevel,
		&pContext)))
	{
		MessageBoxA(0, "Failed to create directX device!",
			0, MB_ICONERROR);
	}

	std::this_thread::sleep_for(std::chrono::milliseconds(2));

	auto table = *reinterpret_cast<PVOID**>(g_pSwapChain);
	auto present = table[8];
	auto resize = table[13];

	PolyHookDetour(reinterpret_cast<char*>(present),
		(char*)&D3D11Present, (uint64_t*)&PresentOriginal);

	PolyHookDetour(reinterpret_cast<char*>(resize),
		(char*)&ResizeHook, (uint64_t*)&ResizeOriginal);

}