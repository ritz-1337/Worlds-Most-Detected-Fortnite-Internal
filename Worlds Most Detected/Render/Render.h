#pragma once
#include <Windows.h>
#include <d3d11.h>
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_win32.h"

#define Fortnite "FortniteClient-Win64-Shipping.exe"
#define FortniteWindow "Fortnite  "

inline IDXGISwapChain* g_pSwapChain = NULL;
inline ID3D11DeviceContext* pContext = NULL;
inline DWORD_PTR* m_pSwapChainVtable = nullptr;
inline DWORD_PTR* pSwapChainVtable = NULL;
inline ID3D11DeviceContext* m_pContext = NULL;
inline ID3D11RenderTargetView* g_pRenderTargetView = NULL;
inline ID3D11Device* uDevice = NULL;
inline WNDPROC oWndProc = NULL;
inline UINT vps = 1;
inline D3D11_VIEWPORT viewport;

inline unsigned long long PresentOriginal = NULL;
inline unsigned long long CommandListOriginal = NULL;
inline unsigned long long ResizeOriginal = NULL;
inline HWND Gamewindow = NULL;
inline int Width, Height;

void StartInitDX11();