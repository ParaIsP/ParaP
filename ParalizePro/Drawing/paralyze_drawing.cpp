#include "paralyze_drawing.h"
#include <ThemidaSDK.h>
#include <Windows.h>
#include <cstdint>
#include <cstdio>
#include "../CheatManager.h"

#include "../ImGui/imgui.h"
#include "../ImGui/imgui_impl_win32.h"
#include "../ImGui/imgui_impl_dx11.h"
#include "../MetaStr.h"
#include "Renderer.h"
#include <thread>
#include "../utils.h"


paralyze_drawing::paralyze_drawing()
{
}


paralyze_drawing::~paralyze_drawing()
{
}

void menu_design()
{
	/*ImGuiStyle& style = ImGui::GetStyle();
	style.Alpha = 1.0f;
	style.WindowPadding = ImVec2(8, 8);
	style.WindowMinSize = ImVec2(32, 32);
	style.WindowRounding = 0.0f;
	style.FramePadding = ImVec2(4, 3);
	style.FrameRounding = 0;
	style.ItemSpacing = ImVec2(8, 4);
	style.ItemInnerSpacing = ImVec2(4, 4);
	style.TouchExtraPadding = ImVec2(0, 0);
	style.IndentSpacing = 21.0f;
	style.ColumnsMinSpacing = 3.0f;
	style.ScrollbarSize = 2.0f;
	style.ScrollbarRounding = 0.0f;
	style.GrabMinSize = 2.0f;
	style.GrabRounding = 0;
	style.DisplayWindowPadding = ImVec2(22, 22);
	style.DisplaySafeAreaPadding = ImVec2(4, 4);
	style.AntiAliasedLines = true;
	style.WindowTitleAlign = ImVec2(0.5, 0.5);
	style.WindowBorderSize = 0.0f;

	style.Colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
	style.Colors[ImGuiCol_WindowBg] = ImColor(53, 59, 81);
	style.Colors[ImGuiCol_ChildWindowBg] = ImColor(53, 59, 81);
	style.Colors[ImGuiCol_Border] = ImVec4(0.f, 0.f, 0.f, 1.f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style.Colors[ImGuiCol_FrameBg] = ImColor(64, 72, 95);
	style.Colors[ImGuiCol_FrameBgHovered] = ImColor(77, 86, 115);
	style.Colors[ImGuiCol_FrameBgActive] = ImColor(70, 79, 104);
	style.Colors[ImGuiCol_TitleBg] = ImColor(64, 72, 95);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImColor(64, 72, 95);
	style.Colors[ImGuiCol_TitleBgActive] = ImColor(64, 72, 95);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(1.00f, 0.0f, 0.0f, 0.96f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImColor(53, 59, 81);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImColor(101, 112, 142);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImColor(97, 107, 135);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImColor(90, 100, 127);
	style.Colors[ImGuiCol_CheckMark] = ImColor(25, 176, 215);
	style.Colors[ImGuiCol_SliderGrab] = ImColor(25, 176, 215);
	style.Colors[ImGuiCol_SliderGrabActive] = ImColor(27, 178, 217);
	style.Colors[ImGuiCol_Button] = ImColor(64, 72, 95);
	style.Colors[ImGuiCol_ButtonHovered] = ImColor(31, 143, 207);
	style.Colors[ImGuiCol_ButtonActive] = ImColor(25, 176, 215);
	style.Colors[ImGuiCol_Header] = ImColor(74, 72, 180);
	style.Colors[ImGuiCol_HeaderHovered] = ImColor(31, 143, 207);
	style.Colors[ImGuiCol_HeaderActive] = ImColor(25, 176, 215);
	style.Colors[ImGuiCol_ResizeGrip] = ImColor(64, 72, 95);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImColor(64, 72, 95);
	style.Colors[ImGuiCol_ResizeGripActive] = ImColor(64, 72, 95);
	style.Colors[ImGuiCol_PlotLines] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.0f, 0.0f, 0.86f);
	style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.87f, 0.87f, 0.87f, 0.87f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.87f, 0.87f, 0.87f, 0.87f);
	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(1.00f, 1.00f, 1.00f, 0.35f);
	style.Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(.1f, .1f, .1f, .1f);
	ImGui::GetStyle() = style;*/


	/* NEW DESIGN */
	/*ImGuiStyle& style = ImGui::GetStyle();

	ImVec4 mainColorHovered = ImVec4(0.52 + 0.1f, 0.05 + 0.1f, 0.1f, 1);
	ImVec4 mainColorActive = ImVec4(0.52 + 0.2f, 0.05 + 0.2f, 0.1f + 0.2f, 1);
	ImVec4 menubarColor = ImVec4(0.02, 0.02, 0.02, 0.02 - 0.8f);
	ImVec4 frameBgColor = ImVec4(0.02, 0.02, 0.02, 0.02 + .1f);
	ImVec4 tooltipBgColor = ImVec4(0.02, 0.02, 0.02, 0.02 + .05f);

	style.Alpha = 1.0f;
	style.WindowPadding = ImVec2(8, 8);
	style.WindowMinSize = ImVec2(32, 32);
	style.WindowRounding = 0.0f;
	style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
	style.FramePadding = ImVec2(4, 3);
	style.FrameRounding = 0.0f;
	style.ItemSpacing = ImVec2(8, 4);
	style.ItemInnerSpacing = ImVec2(4, 4);
	style.TouchExtraPadding = ImVec2(0, 0);
	style.IndentSpacing = 21.0f;
	style.ColumnsMinSpacing = 3.0f;
	style.ScrollbarSize = 12.0f;
	style.ScrollbarRounding = 0.0f;
	style.GrabMinSize = 5.0f;
	style.GrabRounding = 0.0f;
	style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
	style.DisplayWindowPadding = ImVec2(22, 22);
	style.DisplaySafeAreaPadding = ImVec2(4, 4);
	style.AntiAliasedLines = true;
	style.AntiAliasedFill = true;
	style.CurveTessellationTol = 1.25f;
	style.FrameBorderSize = 0.25f;
	style.WindowBorderSize = 0.f;

	style.Colors[ImGuiCol_Text] = ImVec4(1.f, 1.f, 1.f, 1.f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.02, 0.02, 0.02, 0.75f);
	style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(.0f, .0f, .0f, .0f);
	style.Colors[ImGuiCol_PopupBg] = tooltipBgColor;
	style.Colors[ImGuiCol_Border] = ImVec4(0.835, 0.f, 0.09f, 1.f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.92f, 0.91f, 0.88f, 0.00f);
	style.Colors[ImGuiCol_FrameBg] = frameBgColor;
	style.Colors[ImGuiCol_FrameBgHovered] = mainColorHovered;
	style.Colors[ImGuiCol_FrameBgActive] = mainColorActive;
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.835, 0.f, 0.09f, 1.f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 0.98f, 0.95f, 0.75f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.835, 0.f, 0.09f, 1.f);
	style.Colors[ImGuiCol_MenuBarBg] = menubarColor;
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(frameBgColor.x + .05f, frameBgColor.y + .05f, frameBgColor.z + .05f, frameBgColor.w);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.835, 0.f, 0.09f, 1.f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = mainColorHovered;
	style.Colors[ImGuiCol_ScrollbarGrabActive] = mainColorActive;
	style.Colors[ImGuiCol_CheckMark] = ImVec4(0.835, 0.f, 0.09f, 1.f);
	style.Colors[ImGuiCol_SliderGrab] = mainColorHovered;
	style.Colors[ImGuiCol_SliderGrabActive] = mainColorActive;
	style.Colors[ImGuiCol_Button] = ImVec4(0.835, 0.f, 0.09f, 1.f);
	style.Colors[ImGuiCol_ButtonHovered] = mainColorHovered;
	style.Colors[ImGuiCol_ButtonActive] = mainColorActive;
	style.Colors[ImGuiCol_Header] = ImVec4(0.835, 0.f, 0.09f, 1.f);
	style.Colors[ImGuiCol_HeaderHovered] = mainColorHovered;
	style.Colors[ImGuiCol_HeaderActive] = mainColorActive;
	style.Colors[ImGuiCol_Separator] = ImVec4(0.835, 0.f, 0.09f, 0.7f);
	style.Colors[ImGuiCol_SeparatorHovered] = mainColorHovered;
	style.Colors[ImGuiCol_SeparatorActive] = mainColorActive;
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.835, 0.f, 0.09f, 1.f);
	style.Colors[ImGuiCol_ResizeGripHovered] = mainColorHovered;
	style.Colors[ImGuiCol_ResizeGripActive] = mainColorActive;
	style.Colors[ImGuiCol_PlotLines] = ImVec4(0.835, 0.f, 0.09f, 1.f);
	style.Colors[ImGuiCol_PlotLinesHovered] = mainColorHovered;
	style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.835, 0.f, 0.09f, 1.f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = mainColorHovered;
	style.Colors[ImGuiCol_TextSelectedBg] = mainColorHovered;
	style.Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(0.0f, 0.0f, 0.0f, 0.75f);*/


	/*ImGuiStyle& style = ImGui::GetStyle();
	style.TabRounding = 0.0f;
	style.FrameBorderSize = 1.0f;
	style.ScrollbarRounding = 0.0f;
	style.ScrollbarSize = 10.0f;
	ImVec4* colors = ImGui::GetStyle().Colors;
	colors[ImGuiCol_Text] = ImVec4(0.95f, 0.95f, 0.95f, 1.00f);
	colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
	colors[ImGuiCol_WindowBg] = ImVec4(0.12f, 0.12f, 0.12f, 1.00f);
	colors[ImGuiCol_ChildBg] = ImVec4(0.04f, 0.04f, 0.04f, 0.50f);
	colors[ImGuiCol_PopupBg] = ImVec4(0.12f, 0.12f, 0.12f, 0.94f);
	colors[ImGuiCol_Border] = ImVec4(0.25f, 0.25f, 0.27f, 0.50f);
	colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_FrameBg] = ImVec4(0.20f, 0.20f, 0.22f, 0.50f);
	colors[ImGuiCol_FrameBgHovered] = ImVec4(0.25f, 0.25f, 0.27f, 0.75f);
	colors[ImGuiCol_FrameBgActive] = ImVec4(0.30f, 0.30f, 0.33f, 1.00f);
	colors[ImGuiCol_TitleBg] = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
	colors[ImGuiCol_TitleBgActive] = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
	colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.04f, 0.04f, 0.04f, 0.75f);
	colors[ImGuiCol_MenuBarBg] = ImVec4(0.18f, 0.18f, 0.19f, 1.00f);
	colors[ImGuiCol_ScrollbarBg] = ImVec4(0.24f, 0.24f, 0.26f, 0.75f);
	colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.41f, 0.41f, 0.41f, 0.75f);
	colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.62f, 0.62f, 0.62f, 0.75f);
	colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.94f, 0.92f, 0.94f, 0.75f);
	colors[ImGuiCol_CheckMark] = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
	colors[ImGuiCol_SliderGrab] = ImVec4(0.41f, 0.41f, 0.41f, 0.75f);
	colors[ImGuiCol_SliderGrabActive] = ImVec4(0.62f, 0.62f, 0.62f, 0.75f);
	colors[ImGuiCol_Button] = ImVec4(0.20f, 0.20f, 0.22f, 1.00f);
	colors[ImGuiCol_ButtonHovered] = ImVec4(0.25f, 0.25f, 0.27f, 1.00f);
	colors[ImGuiCol_ButtonActive] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
	colors[ImGuiCol_Header] = ImVec4(0.18f, 0.18f, 0.19f, 1.00f);
	colors[ImGuiCol_HeaderHovered] = ImVec4(0.25f, 0.25f, 0.27f, 1.00f);
	colors[ImGuiCol_HeaderActive] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
	colors[ImGuiCol_Separator] = ImVec4(0.25f, 0.25f, 0.27f, 1.00f);
	colors[ImGuiCol_SeparatorHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
	colors[ImGuiCol_SeparatorActive] = ImVec4(0.62f, 0.62f, 0.62f, 1.00f);
	colors[ImGuiCol_ResizeGrip] = ImVec4(0.30f, 0.30f, 0.33f, 0.75f);
	colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.41f, 0.41f, 0.41f, 0.75f);
	colors[ImGuiCol_ResizeGripActive] = ImVec4(0.62f, 0.62f, 0.62f, 0.75f);
	colors[ImGuiCol_Tab] = ImVec4(0.21f, 0.21f, 0.22f, 1.00f);
	colors[ImGuiCol_TabHovered] = ImVec4(0.37f, 0.37f, 0.39f, 1.00f);
	colors[ImGuiCol_TabActive] = ImVec4(0.30f, 0.30f, 0.33f, 1.00f);
	colors[ImGuiCol_TabUnfocused] = ImVec4(0.12f, 0.12f, 0.12f, 0.97f);
	colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.18f, 0.18f, 0.19f, 1.00f);
	colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
	colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
	colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
	colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.50f);
	colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
	colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
	colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
	colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
	style.WindowMenuButtonPosition = ImGuiDir_Right;*/


ImGuiStyle* style = &ImGui::GetStyle();
ImVec4* colors = style->Colors;

colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.06f, 0.06f, 0.94f);
colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
colors[ImGuiCol_Border] = ImVec4(0.30f, 0.30f, 0.30f, 0.50f);
colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
colors[ImGuiCol_FrameBg] = ImVec4(0.17f, 0.17f, 0.17f, 1.00f);
colors[ImGuiCol_FrameBgHovered] = ImVec4(0.69f, 0.23f, 0.13f, 1.00f);
colors[ImGuiCol_FrameBgActive] = ImVec4(0.96f, 0.35f, 0.21f, 1.00f);
colors[ImGuiCol_TitleBg] = ImVec4(0.69f, 0.23f, 0.13f, 1.00f);
colors[ImGuiCol_TitleBgActive] = ImVec4(0.96f, 0.35f, 0.21f, 1.00f);
colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
colors[ImGuiCol_CheckMark] = ImVec4(0.96f, 0.35f, 0.21f, 1.00f);
colors[ImGuiCol_SliderGrab] = ImVec4(0.69f, 0.23f, 0.13f, 1.00f);
colors[ImGuiCol_SliderGrabActive] = ImVec4(0.96f, 0.35f, 0.21f, 1.00f);
colors[ImGuiCol_Button] = ImVec4(0.69f, 0.23f, 0.13f, 1.00f);
colors[ImGuiCol_ButtonHovered] = ImVec4(0.96f, 0.35f, 0.21f, 1.00f);
colors[ImGuiCol_ButtonActive] = ImVec4(0.96f, 0.35f, 0.21f, 1.00f);
colors[ImGuiCol_Header] = ImVec4(0.69f, 0.23f, 0.13f, 1.00f);
colors[ImGuiCol_HeaderHovered] = ImVec4(0.96f, 0.35f, 0.21f, 1.00f);
colors[ImGuiCol_HeaderActive] = ImVec4(0.96f, 0.35f, 0.21f, 1.00f);
colors[ImGuiCol_Separator] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
colors[ImGuiCol_SeparatorHovered] = ImVec4(0.10f, 0.40f, 0.75f, 0.78f);
colors[ImGuiCol_SeparatorActive] = ImVec4(0.10f, 0.40f, 0.75f, 1.00f);
colors[ImGuiCol_ResizeGrip] = ImVec4(0.69f, 0.23f, 0.13f, 1.00f);
colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.69f, 0.23f, 0.13f, 1.00f);
colors[ImGuiCol_ResizeGripActive] = ImVec4(0.69f, 0.23f, 0.13f, 1.00f);
colors[ImGuiCol_Tab] = ImVec4(0.69f, 0.23f, 0.13f, 1.00f);
colors[ImGuiCol_TabHovered] = ImVec4(0.96f, 0.35f, 0.21f, 1.00f);
colors[ImGuiCol_TabActive] = ImVec4(0.96f, 0.35f, 0.21f, 1.00f);
colors[ImGuiCol_TabUnfocused] = ImVec4(0.07f, 0.10f, 0.15f, 0.97f);
colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.14f, 0.26f, 0.42f, 1.00f);
colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);



	ImGui::GetStyle().WindowPadding = ImVec2((float)8.0f, (float)8.0f);
	ImGui::GetStyle().FramePadding = ImVec2((float)4.0f, (float)3.0f);
	ImGui::GetStyle().ItemSpacing = ImVec2((float)8.0f, (float)4.0f);
	ImGui::GetStyle().ItemInnerSpacing = ImVec2((float)4.0f, (float)4.0f);
	ImGui::GetStyle().TouchExtraPadding = ImVec2((float)0.0f, (float)0.0f);
	ImGui::GetStyle().IndentSpacing = 21.0f;
	ImGui::GetStyle().ScrollbarSize = 14.0f;
	ImGui::GetStyle().GrabMinSize = 10.0f;

	// Borders
	ImGui::GetStyle().WindowBorderSize = 1.0f;
	ImGui::GetStyle().ChildBorderSize = 1.0f;
	ImGui::GetStyle().PopupBorderSize = 1.0f;
	ImGui::GetStyle().FrameBorderSize = 1.0f;
	ImGui::GetStyle().TabBorderSize = 1.0f;

	// Rounding
	ImGui::GetStyle().WindowRounding = 0.0f;
	ImGui::GetStyle().ChildRounding = 0.0f;
	ImGui::GetStyle().FrameRounding = 5.0f;
	ImGui::GetStyle().PopupRounding = 2.0f;
	ImGui::GetStyle().ScrollbarRounding = 9.0f;
	ImGui::GetStyle().GrabRounding = 2.0f;
	ImGui::GetStyle().TabRounding = 4.0f;


}

void paralyze_drawing::init_drawing(HWND gameWindow) {
	this->game_window = gameWindow;
	WINDOWINFO infow;
	//ShowWindow(this->game_window, SW_SHOWMAXIMIZED);
	//SetForegroundWindow(this->game_window);
	//BringWindowToTop(this->game_window);
	ZeroMemory(&infow, sizeof(infow));
	infow.cbSize = sizeof(infow);
	GetWindowInfo(this->game_window, &infow);
	Global::monitorX = ((infow.rcClient.right) - (infow.rcClient.left));
	Global::monitorY = ((infow.rcClient.bottom) - (infow.rcClient.top));
}

static DWORD dwLastFrameTime = 0;
BOOLEAN LockFPS(INT FPS)
{
	if (FPS == 0)
		FPS = 500;

	SYSTEMTIME st;
	GetSystemTime(&st);

	INT dwCurrentTime = st.wMilliseconds;
	if ((dwCurrentTime - dwLastFrameTime) < (1000 / FPS))
	{
		return TRUE;
	}
	dwLastFrameTime = dwCurrentTime;

	return FALSE;
}

void paralyze_drawing::start_drawing()
{
	if (swapchain_creator::create_device_d3d(this->game_window) < 0)
	{
		MessageBoxA(0, METASTRING("Unable to create D3D Device."), "", 0);
		swapchain_creator::cleanup_device_d3d();
	}

	swapchain_creator::init_rendering(this->game_window);


	pcdi = new paralyze_drawing_input();
	pcdi->spinup_threads();
	pcdm = new paralyze_drawing_menu();
	pcdv = new paralyze_drawing_visuals();

	menu_design();

	float clearColor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };

	ImFont* Font = Renderer::GetInstance()->m_pFont;
	while (true)
	{
		/*if (GetAsyncKeyState(VK_F5))
		{
			HWND abc = util::find_window_by_pid(pcm->r6pid);
			temporary_window window2;
			uint64_t WndThreadInfoLocal2 = pcm->get_wnd_thread(window2.handle());
			uint64_t WndThreadInfoTarget2 = pcm->get_wnd_thread(abc);
			pcm->set_wnd_thread(abc, WndThreadInfoLocal2);
			compositionVisual->SetContent(nullptr);
			compositionTarget->SetRoot(nullptr);
			compositionDevice->Release();
			compositionVisual->Release();
			compositionTarget->Release();
			pcm->set_wnd_thread(abc, WndThreadInfoTarget2);
			exit(0);
		}*/

		if (LockFPS((INT)120))
			continue;
		
		pcd->g_pd3dDeviceContext->OMSetRenderTargets(1, &pcd->g_mainRenderTargetView, NULL);

		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
		

		if (GetAsyncKeyState(VK_INSERT)) {
			Global::bMenu = !Global::bMenu;
			std::this_thread::sleep_for(std::chrono::milliseconds(250));
		}

		// Rendering
		if(Global::bMenu) {
			pcdm->draw_menu();
		}

		Renderer::GetInstance()->BeginScene();

		pcdv->draw_visuals();
		

		Renderer::GetInstance()->EndScene();
		
		ImGui::Render();
		g_pd3dDeviceContext->OMSetRenderTargets(1, &g_mainRenderTargetView, NULL);
		g_pd3dDeviceContext->ClearRenderTargetView(g_mainRenderTargetView, (float*)&clearColor);
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
		g_pSwapChain->Present(0, 0); // Present with vsync
	}

}



