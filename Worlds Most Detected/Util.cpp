#include "Util.h"
#include <consoleapi.h>
#include <cstdio>
#include "Settings.h"

void CreateConsole() {
	AllocConsole();
	freopen("CONIN$", "r", stdin);
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);
}

void Draw3dBox(APlayerController* PlayerController, Vector3 BoxExtent, Vector3 Origin, float thicky, ImColor color) {
	if (BoxExtent.x == 0 or BoxExtent.y == 0 or BoxExtent.z == 0)
		return;
	if (!(uintptr_t)PlayerController)
		return;

	auto v000 = Origin - BoxExtent;
	auto v111 = Origin + BoxExtent;

	auto v010 = Vector3(v000.x, v111.y, v000.z);
	auto v110 = Vector3(v111.x, v111.y, v000.z);
	auto v011 = Vector3(v000.x, v111.y, v111.z);

	// bottom box
	auto v101 = Vector3(v111.x, v000.y, v111.z);
	auto v100 = Vector3(v111.x, v000.y, v000.z);
	auto v001 = Vector3(v000.x, v000.y, v111.z);

	auto w1 = PlayerController->ProjectWorldLocationToScreen(Vector3(v000.x, v000.y, v000.z));
	if (!w1.valid_location())
		return;

	auto w2 = PlayerController->ProjectWorldLocationToScreen(Vector3(v111.x, v111.y, v111.z/* + config.BoxHight*/));
	if (!w2.valid_location())
		return;

	auto s1 = PlayerController->ProjectWorldLocationToScreen(v010);
	if (!s1.valid_location())
		return;

	auto s2 = PlayerController->ProjectWorldLocationToScreen(v110);
	if (!s2.valid_location())
		return;

	auto s3 = PlayerController->ProjectWorldLocationToScreen(v011);
	if (!s3.valid_location())
		return;

	auto s4 = PlayerController->ProjectWorldLocationToScreen(v101);
	if (!s4.valid_location())
		return;

	auto s5 = PlayerController->ProjectWorldLocationToScreen(v100);
	if (!s5.valid_location())
		return;

	auto s6 = PlayerController->ProjectWorldLocationToScreen(v001);
	if (!s6.valid_location())
		return;

	ImDrawList* draw_list = ImGui::GetForegroundDrawList();
	draw_list->AddLine(ImVec2(w1.x, w1.y), ImVec2(s6.x, s6.y), color, thicky);
	draw_list->AddLine(ImVec2(w1.x, w1.y), ImVec2(s5.x, s5.y), color, thicky);
	draw_list->AddLine(ImVec2(s4.x, s4.y), ImVec2(s5.x, s5.y), color, thicky);
	draw_list->AddLine(ImVec2(s4.x, s4.y), ImVec2(s6.x, s6.y), color, thicky);

	draw_list->AddLine(ImVec2(s1.x, s1.y), ImVec2(s3.x, s3.y), color, thicky);
	draw_list->AddLine(ImVec2(s1.x, s1.y), ImVec2(s2.x, s2.y), color, thicky);
	draw_list->AddLine(ImVec2(w2.x, w2.y), ImVec2(s2.x, s2.y), color, thicky);
	draw_list->AddLine(ImVec2(w2.x, w2.y), ImVec2(s3.x, s3.y), color, thicky);

	draw_list->AddLine(ImVec2(s6.x, s6.y), ImVec2(s3.x, s3.y), color, thicky);
	draw_list->AddLine(ImVec2(w1.x, w1.y), ImVec2(s1.x, s1.y), color, thicky);
	draw_list->AddLine(ImVec2(s4.x, s4.y), ImVec2(w2.x, w2.y), color, thicky);
	draw_list->AddLine(ImVec2(s5.x, s5.y), ImVec2(s2.x, s2.y), color, thicky);
}

void DrawHighlightMenu() {
	float innerColor[3] = { Settings.PawnHighlight.Inner.R, Settings.PawnHighlight.Inner.G, Settings.PawnHighlight.Inner.B };

	ImGui::ColorPicker3("Inner Color", innerColor);

	Settings.PawnHighlight.Inner.R = innerColor[0];
	Settings.PawnHighlight.Inner.G = innerColor[1];
	Settings.PawnHighlight.Inner.B = innerColor[2];

	float outerColor[3] = { Settings.PawnHighlight.Outer.R, Settings.PawnHighlight.Outer.G, Settings.PawnHighlight.Outer.B };

	ImGui::ColorPicker3("Outer Color", outerColor);

	Settings.PawnHighlight.Outer.R = innerColor[0];
	Settings.PawnHighlight.Outer.G = innerColor[1];
	Settings.PawnHighlight.Outer.B = innerColor[2];

	ImGui::SliderFloat("FresnelBrightness", &Settings.PawnHighlight.FresnelBrightness, 0, 100);
	ImGui::SliderFloat("FresnelExponent", &Settings.PawnHighlight.FresnelExponent, 0, 100); 
	ImGui::SliderFloat("UsesPulse", &Settings.PawnHighlight.UsesPulse, 0, 100);
}