#pragma once
#include "Renderer.h"
#include "../MetaStr.h"
#include "../ImGui/imgui.h"
#include "../ImGui/imgui_internal.h"
#include "../CheatManager.h"
#include "../Vectors.h"


Renderer* Renderer::m_pInstance;

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::Initialize()
{
	ImGuiIO& io = ImGui::GetIO();

	io.Fonts->AddFontFromFileTTF(METASTRING("C:\\Windows\\Fonts\\Arial.ttf"), 13.f, NULL, io.Fonts->GetGlyphRangesCyrillic());
	m_pFont = io.Fonts->AddFontFromFileTTF(METASTRING("C:\\Windows\\Fonts\\Arial.ttf"), 13.f, NULL, io.Fonts->GetGlyphRangesCyrillic());
}

void Renderer::BeginScene()
{
	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
	ImGui::Begin("", reinterpret_cast<bool*>(true), ImVec2(0, 0), 0.0f, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoInputs);

	ImGui::SetWindowPos(ImVec2(0, 0), ImGuiCond_Always);
	ImGui::SetWindowSize(ImVec2(pcd->screenWidth, pcd->screenHeight), ImGuiCond_Always);

	ImGuiWindow* window = ImGui::GetCurrentWindow();
}

void Renderer::DrawScene()
{
	ImGuiIO& io = ImGui::GetIO();
}

void Renderer::EndScene()
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	window->DrawList->PushClipRectFullScreen();

	ImGui::End();
	ImGui::PopStyleColor();
}

float Renderer::DrawText(ImFont* pFont, const char* text, Vector2 pos, float size, Vector4 color, bool center)
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();

	float a = color.w;
	float r = color.x;
	float g = color.y;
	float b = color.z;

	float y = 0.0f;
	int i = 0;

	ImVec2 textSize = m_pFont->CalcTextSizeA(size, FLT_MAX, 0.0f, text);

	if (center)
	{
		/*window->DrawList->AddText(m_pFont, size, ImVec2((pos.x - textSize.x / 2.0f) + 1, (pos.y + textSize.y * i) + 1), ImGui::GetColorU32(ImVec4(.1f, .1f, .1f, a / 255)), text);
		window->DrawList->AddText(m_pFont, size, ImVec2((pos.x - textSize.x / 2.0f) - 1, (pos.y + textSize.y * i) - 1), ImGui::GetColorU32(ImVec4(.1f, .1f, .1f, a / 255)), text);
		window->DrawList->AddText(m_pFont, size, ImVec2((pos.x - textSize.x / 2.0f) + 1, (pos.y + textSize.y * i) - 1), ImGui::GetColorU32(ImVec4(.1f, .1f, .1f, a / 255)), text);
		window->DrawList->AddText(m_pFont, size, ImVec2((pos.x - textSize.x / 2.0f) - 1, (pos.y + textSize.y * i) + 1), ImGui::GetColorU32(ImVec4(.1f, .1f, .1f, a / 255)), text);

		window->DrawList->AddText(m_pFont, size, ImVec2(pos.x - textSize.x / 2.0f, pos.y + textSize.y * i), ImGui::GetColorU32(ImVec4(r / 255, g / 255, b / 255, a / 255)), text);*/


		window->DrawList->AddText(m_pFont, size, ImVec2(pos.x - textSize.x / 2.0f, pos.y + textSize.y * i), ImGui::GetColorU32(ImVec4(r / 255, g / 255, b / 255, a / 255)), text); 
	}
	else
	{
		/*window->DrawList->AddText(m_pFont, size, ImVec2((pos.x) + 1, (pos.y + textSize.y * i) + 1), ImGui::GetColorU32(ImVec4(0.f, 0.f, 0.f, a / 255)), text);
		window->DrawList->AddText(m_pFont, size, ImVec2((pos.x) - 1, (pos.y + textSize.y * i) - 1), ImGui::GetColorU32(ImVec4(0.f, 0.f, 0.f, a / 255)), text);
		window->DrawList->AddText(m_pFont, size, ImVec2((pos.x) + 1, (pos.y + textSize.y * i) - 1), ImGui::GetColorU32(ImVec4(0.f, 0.f, 0.f, a / 255)), text);
		window->DrawList->AddText(m_pFont, size, ImVec2((pos.x) - 1, (pos.y + textSize.y * i) + 1), ImGui::GetColorU32(ImVec4(0.f, 0.f, 0.f, a / 255)), text);
		*/	

		window->DrawList->AddText(pFont, size, ImVec2(pos.x, pos.y + textSize.y * i), ImGui::GetColorU32(ImVec4(r / 255, g / 255, b / 255, a / 255)), text);
	}

	y = pos.y + textSize.y * (i + 1);
	i++;

	return y;
}

void Renderer::DrawFilledBox(const ImVec2& pos, const ImVec2& headPosition, Vector4 color) {
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	window->DrawList->AddRectFilled(pos, headPosition, ImGui::GetColorU32(ImVec4(color.x / 255, color.y / 255, color.z / 255, color.w / 255)));
}

void Renderer::DrawLine(Vector2 from, Vector2 to,Vector4 color, float thickness)
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();

	window->DrawList->AddLine(ImVec2(from.x, from.y), ImVec2(to.x, to.y), ImGui::GetColorU32(ImVec4(color.x / 255, color.y / 255, color.z / 255, color.w / 255)), thickness);
}

void Renderer::DrawBox(Vector2 from, Vector2 size,Vector4 color, float rounding, float thickness)
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();

	//window->DrawList->AddRect(ImVec2(from.x-1, from.y - 1), ImVec2(size.x - 1, size.y - 1), ImGui::GetColorU32(ImVec4(0 / 255, 0 / 255, 0 / 255, 255 / 255)), rounding, 15, thickness+3);
	window->DrawList->AddRect(ImVec2(from.x, from.y), ImVec2(size.x, size.y), ImGui::GetColorU32(ImVec4(color.x / 255, color.y / 255, color.z / 255, color.w / 255)), rounding, 15, thickness);
}

void Renderer::DrawBoxFilled(Vector2 from, Vector2 size,Vector4 color, float rounding)
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();

	window->DrawList->AddRectFilled(ImVec2(from.x, from.y), ImVec2(size.x, size.y), ImGui::GetColorU32(ImVec4(color.x / 255, color.y / 255, color.z / 255, color.w / 255)), rounding, 15);
}

void Renderer::DrawCircle(Vector2 from, float radius,Vector4 color, float thickness)
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();

	window->DrawList->AddCircle(ImVec2(from.x, from.y), radius, ImGui::GetColorU32(ImVec4(color.x / 255, color.y / 255, color.z / 255, color.w / 255)), 180, thickness);
}

void Renderer::DrawCircleFilled(Vector2 from, float radius,Vector4 color)
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();

	window->DrawList->AddCircleFilled(ImVec2(from.x, from.y), radius, ImGui::GetColorU32(ImVec4(color.x / 255, color.y / 255, color.z / 255, color.w / 255)), 180);
}

void Renderer::DrawCircleScale(const ImVec2& position, float radius, uint32_t color, const ImVec2& scalepos, const ImVec2& scaleheadPosition, float thickness)
{
	float rad = (scaleheadPosition.y + 15 - scalepos.y) / 10.5f;
	ImGuiWindow* window = ImGui::GetCurrentWindow();


	window->DrawList->AddCircle(position, rad, color, 12, thickness);
}

#include <cstdint>
void Renderer::DrawBestBox(Vector2 from, Vector2 size, uint32_t color, float rounding, float thickness)
{
	float a = (color >> 24) & 0xff;
	float r = (color >> 16) & 0xff;
	float g = (color >> 8) & 0xff;
	float b = (color) & 0xff;


	ImGuiWindow* window = ImGui::GetCurrentWindow();
	window->DrawList->AddRect(ImVec2(from.x, from.y), ImVec2(size.x, size.y), color, rounding, 15, thickness);
}

Renderer* Renderer::GetInstance()
{
	if (!m_pInstance)
		m_pInstance = new Renderer();

	return m_pInstance;
}