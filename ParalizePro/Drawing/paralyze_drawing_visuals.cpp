#include "paralyze_drawing_visuals.h"
#include "Renderer.h"
#include "../MetaStr.h"
#include "../utils.h"
#include "../CheatManager.h"
#include "../Entity.h"
#include "../Offsets.h"
#include "../GameRenderer.h"
#include "../StatusManager.h"
#include "../LocalPlayerManager.h"
#include "../Settings.h"
#include "../GlowManager.h"

#pragma warning(disable:4996)


paralyze_drawing_visuals::paralyze_drawing_visuals()
{
}


paralyze_drawing_visuals::~paralyze_drawing_visuals()
{
}

std::string VariableText(const char* format, ...)
{
	va_list argptr;
	va_start(argptr, format);

	char buffer[2048];
	vsprintf(buffer, format, argptr);

	va_end(argptr);

	return buffer;
}


int AshBones[] = {
		0x33,//high_neck
		0x32,//low_neck
		0x07,//r_shoulder
		0x60,//l_shoulder
		0x08,//r_elbow
		0x61,//l_elbow
		0x09,//r_hand
		0x62,//l_hand
		0x05,//high_stomach
		0x04,//low_stomach
		0x02,//pelvis
		0xC0,//r_knee
		0xCA,//l_knee
		0xC1,//r_foot
		0xCB//l_foot
};

void paralyze_drawing_visuals::draw_visuals()
{
	if (!StatusManager::InGame()) return;

	GlowManager::doGlow();

	if (Settings::bDrawFOV) {
		Renderer::GetInstance()->DrawCircle(Vector2(ImGui::GetIO().DisplaySize.x / 2, ImGui::GetIO().DisplaySize.y / 2), Settings::aimFov, Vector4(255,255,255,255), 1.0f);
	}

	uint64_t gameManager = pcm->rvm<uint64_t>(pcm->r6base + ADDRESS_GAMEMANAGER);
	uint64_t entityList = pcm->rvm<uint64_t>(gameManager + 0x1C8);

	uint64_t localPlayer = LocalPlayerManager::getLocalPlayer();

	for (int i = 0; i <= 10; i++) {
		uint64_t entity = pcm->rvm<uint64_t>(entityList + i * 0x8);
		if (!entity) continue;

		Vector3 Position = GameRenderer::W2S(Entity::getPosition(entity));
		Vector3 HeadPosition = GameRenderer::W2S(Entity::getHead(entity));
		BYTE Team = Entity::getTeam(entity);
		BYTE LocalTeam = Entity::getTeam(localPlayer);
		int Health = Entity::getHealth(entity);

		if (Position.z >= 1.0f && Health > 0 && Health < 250) { // Valid Entity

			float BoxHeight = fabs((HeadPosition.y - Position.y));
			float BoxWidth = BoxHeight / 1.8f;

			Vector2 TopLeft = Vector2(HeadPosition.x - (BoxWidth / 2), HeadPosition.y - (BoxHeight / 5));
			Vector2 TopRight = Vector2(HeadPosition.x - (BoxWidth / 2), HeadPosition.y + (BoxHeight / 5));
			Vector2 BottomLeft = Vector2(HeadPosition.x - (BoxWidth / 2), Position.y);
			Vector2 BottomRight = Vector2(HeadPosition.x + (BoxWidth / 2), Position.y);
			Vector2 BottomCenter = Vector2(Position.x, Position.y);
			Vector2 TopCenter = Vector2(HeadPosition.x, HeadPosition.y - (BoxWidth / 2));


			if (Settings::bESPBoxes) {
				if (Settings::bESPTeam) {
					if (Team == LocalTeam)
						Renderer::GetInstance()->DrawBestBox(TopLeft, BottomRight, ImGui::GetColorU32(ImVec4(Settings::fESPBoxColorTeam[0], Settings::fESPBoxColorTeam[1], Settings::fESPBoxColorTeam[2], 255.f)), 0.f, Settings::fESPBoxesThickness);
					else
						Renderer::GetInstance()->DrawBestBox(TopLeft, BottomRight, ImGui::GetColorU32(ImVec4(Settings::fESPBoxColor[0], Settings::fESPBoxColor[1], Settings::fESPBoxColor[2], 255.f)), 0.f, Settings::fESPBoxesThickness);

					if (Settings::bESPBoxesFilled)
						Renderer::GetInstance()->DrawFilledBox(ImVec2(TopLeft.x, TopLeft.y), ImVec2(BottomRight.x, BottomRight.y), Vector4(0, 0, 0, Settings::fESPFillOpacity));
				}
				else {
					if (Team != LocalTeam) {
						Renderer::GetInstance()->DrawBestBox(TopLeft, BottomRight, ImGui::GetColorU32(ImVec4(Settings::fESPBoxColor[0], Settings::fESPBoxColor[1], Settings::fESPBoxColor[2], 255.f)), 0.f, Settings::fESPBoxesThickness);
						
						if (Settings::bESPBoxesFilled)
							Renderer::GetInstance()->DrawFilledBox(ImVec2(TopLeft.x, TopLeft.y), ImVec2(BottomRight.x, BottomRight.y), Vector4(0, 0, 0, Settings::fESPFillOpacity));
					}
				}
			}

			if (Settings::bESPHead && Team != LocalTeam) {
				Renderer::GetInstance()->DrawCircleScale(ImVec2(HeadPosition.x, HeadPosition.y), 5.f, ImGui::GetColorU32(ImVec4(Settings::fESPHeadColor[0], Settings::fESPHeadColor[1], Settings::fESPHeadColor[2], 255.f)), ImVec2(Position.x, Position.y), ImVec2(HeadPosition.x, HeadPosition.y));
			}

			if (Settings::bESPSnapline && Team != LocalTeam) {
				Renderer::GetInstance()->DrawLine(Vector2(ImGui::GetIO().DisplaySize.x / 2, ImGui::GetIO().DisplaySize.y), Vector2(Position.x, Position.y), Vector4(Settings::fESPSnaplinesColor[0], Settings::fESPSnaplinesColor[1], Settings::fESPSnaplinesColor[2], 255.f), 0.6f);
			}

			if (Settings::bESPDistance && Team != LocalTeam) {
				float distance = GameRenderer::GetTranslation().Distance(Entity::getPosition(entity));
				Renderer::GetInstance()->DrawText(Renderer::GetInstance()->m_pFont, VariableText(METASTRING("%.1fm"), distance).c_str(), Vector2(HeadPosition.x, Position.y + 1.f), 14.f, Vector4(Settings::fESPBoxColor[0] / 255.f, Settings::fESPBoxColor[1] / 255.f, Settings::fESPBoxColor[2] / 255.f, 255.f), true);
			}

			if (Settings::bESPHealth && Team != LocalTeam) {
				float HP = Health > 120 ? 120 : Health;
				Vector4 healthColor = Vector4(255 - (HP * 2.55), HP * 2.55, 0, 255);

				Renderer::GetInstance()->DrawFilledBox(ImVec2(BottomLeft.x - 6.f, BottomLeft.y), ImVec2(TopLeft.x - 2.f, TopLeft.y), Vector4(0, 0, 0, 255));
				Renderer::GetInstance()->DrawFilledBox(ImVec2(BottomLeft.x - 5.f, BottomLeft.y), ImVec2(TopLeft.x - 3.f, BottomLeft.y - (((BottomLeft.y - TopLeft.y) / 120) * HP)), healthColor);
			}
		}
	}
}




