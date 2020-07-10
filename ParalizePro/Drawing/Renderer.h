#pragma once
#include "../Vectors.h"
#include "../ImGui/imgui.h"
#include <windows.h>
#include <cstdint>

class Renderer
{
public:
  void Initialize();
  void BeginScene();
  void DrawScene();
  void EndScene();

  static Renderer* GetInstance();

  ImFont* m_pFont;
  ImFont* m_pBigFont;

  Renderer();
  ~Renderer();

  float DrawText(ImFont* pFont, const char* text, Vector2 pos, float size, Vector4 color, bool center);
  void DrawLine(Vector2 from, Vector2 to, Vector4 color, float thickness);
  void DrawBox(Vector2 from, Vector2 size, Vector4 color, float rounding, float thickness);
  void DrawBoxFilled(Vector2 from, Vector2 size, Vector4 color, float rounding);
  void DrawCircle(Vector2 from, float radius, Vector4 color, float thickness = 1.f);
  void DrawCircleFilled(Vector2 from, float radius, Vector4 color);
  void DrawFilledBox(const ImVec2& position, const ImVec2& headPosition, Vector4 color);
  void DrawCircleScale(const ImVec2& position, float radius, uint32_t color, const ImVec2& scalepos, const ImVec2& scaleheadPosition, float thickness = 1.0f);
  void DrawBox3D(Vector3 positon, Vector4 color, float thickness, Vector3 min, Vector3 max, Vector3 angels);
  void DrawBestBox(Vector2 from, Vector2 size, uint32_t color, float rounding, float thickness);
private:
  static Renderer* m_pInstance;
};
