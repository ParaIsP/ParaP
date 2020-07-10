#include "paralyze_drawing_menu.h"
#include "../MetaStr.h"
#include "Renderer.h"
#include "../CheatManager.h"
#include "../Settings.h"
#include "../Offsets.h"
#include <ThemidaSDK.h>
#include "../utils.h"
#include "../ImGui/imgui_internal.h"

paralyze_drawing_menu::paralyze_drawing_menu( )
{ }

paralyze_drawing_menu::~paralyze_drawing_menu( )
{ }

#pragma warning(disable:4996)

bool mainMenu = true;
bool configsMenu = false;

void color_pickerFuerWixxer( std::string name, float pcolor[ 4 ] )
{
	STR_ENCRYPT_START
		bool openPopupTeamBoxColor = ImGui::ColorButton( std::string( METASTRING( "colorButton" ) + name ).c_str( ), ImColor{ pcolor[ 0 ], pcolor[ 1 ], pcolor[ 2 ], 0.9f }, ImGuiColorEditFlags_NoTooltip );
	if ( openPopupTeamBoxColor )
		ImGui::OpenPopup( std::string( METASTRING( "ColorPopup" ) + name ).c_str( ) );
	if ( ImGui::BeginPopup( std::string( METASTRING( "ColorPopup" ) + name ).c_str( ) ) )
	{
		ImGui::ColorPicker4( name.c_str( ), pcolor, ImGuiColorEditFlags_RGB );
		ImGui::EndPopup( );
	}
	STR_ENCRYPT_END
}

/*void paralyze_drawing_menu::draw_menu()
{
	STR_ENCRYPT_START
	if (ImGui::BeginMainMenuBar())
	{
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(8 * 2.0f, 4 * 2.0f));

		ImGui::Selectable(METASTRING("Main Window"), &mainMenu, 0, ImVec2(ImGui::CalcTextSize(METASTRING("Main Window"), NULL, true).x, 0.0f));
		ImGui::Selectable(METASTRING("Configs"), &configsMenu, 0, ImVec2(ImGui::CalcTextSize(METASTRING("Configs"), NULL, true).x, 0.0f));

		ImGui::PopStyleVar();
		ImGui::EndMainMenuBar();
	}

	if (mainMenu) {
		ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(450.f, 375.f));

		static int page = 0;

		if (ImGui::Begin(METASTRING("Rainbow Six"), &mainMenu, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar)) {
			const char* tabs[] = {
				("Aim"),
				("Visual"),
				("Others")
			};

			for (int i = 0; i < IM_ARRAYSIZE(tabs); i++)
			{
				int distance = i == page ? 0 : i > page ? i - page : page - i;

				ImGui::GetStyle().Colors[ImGuiCol_Button] = ImVec4(
					0.52 + 0.2f - (distance * 0.035f),
					0.05 + 0.2f - (distance * 0.035f),
					0.1f + 0.2f - (distance * 0.035f),
					1.f
				);

				if (ImGui::Button(tabs[i], ImVec2(ImGui::GetWindowSize().x / IM_ARRAYSIZE(tabs) - 9, 0)))
					page = i;

				if (i < IM_ARRAYSIZE(tabs) - 1)
					ImGui::SameLine();
			}

			ImGui::Separator();

			if (page == 0) // Aimbot
			{
				ImGui::Checkbox(METASTRING("Enabled"), &Settings::bAimbotEnabled);
				ImGui::SameLine();
				ImGui::Checkbox(METASTRING("Silent Aim"), &Settings::bSilentAim);
				ImGui::SameLine();
				//ImGui::Checkbox("Anti Aim", &Settings::bAntiAim);
				//ImGui::SameLine();
				ImGui::Checkbox(METASTRING("Draw FOV"), &Settings::bDrawFOV);

				ImGui::Spacing();
				ImGui::Separator();
				ImGui::Spacing();

				ImGui::PushItemWidth(339.f);
				ImGui::SliderInt(METASTRING("FOV"), &Settings::aimFov, 1, 1800);
				ImGui::SliderInt(METASTRING("Aim Distance"), &Settings::aimDist, 1, 300);
				ImGui::SliderInt(METASTRING("Aim Smooth"), &Settings::aimSmooth, 1, 15);

				ImGui::Spacing();
				ImGui::Separator();
				ImGui::Spacing();

				const char* AimbotKey[] = { ("CAPSLOCK"), ("LEFT MOUSE"), ("RIGHT MOUSE"), ("ALT"), ("MIDDLE MOUSE"), ("MOUSE 4"), ("MOUSE 5") };

				ImGui::PushItemWidth(339.f);
				ImGui::Combo(METASTRING("Aimbot Key"), &Settings::iAimbotKey, AimbotKey, 7);
				ImGui::PopItemWidth();

				ImGui::Spacing();
				ImGui::Separator();
				ImGui::Spacing();

				ImGui::Text(METASTRING("Extra Modifications"));

				ImGui::Checkbox(METASTRING("No Spread"), &Settings::bNoSpread);
				ImGui::Checkbox(METASTRING("No Recoil"), &Settings::bNoRecoil);
			}
			if (page == 1) // ESP
			{
				ImGui::Checkbox(METASTRING("Enabled"), &Settings::bESPEnable);

				ImGui::Spacing();
				ImGui::Separator();
				ImGui::Spacing();

				ImGui::Checkbox(METASTRING("Team ESP"), &Settings::bESPTeam);
				ImGui::NextColumn();
				ImGui::Checkbox(METASTRING("Caveira ESP"), &Settings::bCavESP);

				ImGui::Spacing();
				ImGui::Separator();
				ImGui::Spacing();

				ImGui::Checkbox(METASTRING("2D Box"), &Settings::bESPBoxes);
				ImGui::SameLine();
				color_pickerFuerWixxer(METASTRING("BoxColor"), Settings::fESPBoxColor);
				ImGui::SameLine();
				color_pickerFuerWixxer(METASTRING("Team Boxcolor"), Settings::fESPBoxColorTeam);
				ImGui::SameLine();
				ImGui::Checkbox(METASTRING("Filled"), &Settings::bESPBoxesFilled);

				ImGui::Checkbox(METASTRING("Head"), &Settings::bESPHead);
				ImGui::SameLine();
				color_pickerFuerWixxer(METASTRING("HeadColor"), Settings::fESPHeadColor);
				ImGui::SameLine();
				color_pickerFuerWixxer(METASTRING("Team HeadColor"), Settings::fESPHeadColorTeam);

				ImGui::Checkbox(METASTRING("Health"), &Settings::bESPHealth);
				//ImGui::SameLine();

				ImGui::Checkbox(METASTRING("Distance"), &Settings::bESPDistance);

				ImGui::Checkbox(METASTRING("Snaplines"), &Settings::bESPSnapline);
				ImGui::SameLine();
				color_pickerFuerWixxer(METASTRING("SnaplinesColor"), Settings::fESPSnaplinesColor);

				ImGui::Spacing();
				ImGui::Separator();
				ImGui::Spacing();

				ImGui::SliderFloat(METASTRING("Box Thickness"), &Settings::fESPBoxesThickness, 1, 5);
				ImGui::SliderFloat(METASTRING("Fill Opacity"), &Settings::fESPFillOpacity, 120, 255);
			}
			else if (page == 2) //glow
			{
				ImGui::NextColumn();

				ImGui::Checkbox(METASTRING("Glow Enabled"), &GlowSettings::bGlowEnable);
				ImGui::SameLine();
				color_pickerFuerWixxer(METASTRING("GlowColor"), GlowSettings::fGlowColor);
				ImGui::SliderFloat(METASTRING("Opacity"), &GlowSettings::fGlowOpacity, 0, 10);
				ImGui::SliderFloat(METASTRING("Distance"), &GlowSettings::fGlowDistance, 0, 50);

				ImGui::NextColumn();

				ImGui::Separator();

				ImGui::NextColumn();
				ImGui::SliderInt(METASTRING("Speed"), &Settings::iSpeed, 105, 200);

				ImGui::Separator();

				ImGui::NextColumn();

				ImGui::BeginGroup();
				if (ImGui::Button(METASTRING("Unlock All"), ImVec2(85, 25))) {
						pcm->virtual_protect(pcm->r6base + ADDRESS_UNLOCKALL, 0x300, 0x40);

						BYTE ass1 = 0x19;
						pcm->wvm<BYTE>(pcm->r6base + ADDRESS_UNLOCKALL + 0x23C, ass1);

						BYTE ass2 = 0x0;
						pcm->wvm<BYTE>(pcm->r6base + ADDRESS_UNLOCKALL + 0x259, ass2);
				}
				ImGui::EndGroup();
			}
			else if (page == 3) //skin
			{
			}

			ImGui::End();
			ImGui::PopStyleVar();
		}
	}

	STR_ENCRYPT_END
}*/

static void HelpMarker( const char* desc )
{
	ImGui::TextDisabled( "(?)" );
	if ( ImGui::IsItemHovered( ) )
	{
		ImGui::BeginTooltip( );
		ImGui::PushTextWrapPos( ImGui::GetFontSize( ) * 35.0f );
		ImGui::TextUnformatted( desc );
		ImGui::PopTextWrapPos( );
		ImGui::EndTooltip( );
	}
}

bool mainMenuToggle = true;
bool aimbotMenu = false;
bool espMenu = false;
bool miscMenu = false;
bool vsyncOption = true;

void paralyze_drawing_menu::draw_menu( )
{
	if ( mainMenuToggle )
	{
		ImGui::Begin( "             Ham Mafia | Rainbow Six: Siege | Production Build", &mainMenuToggle, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse );
		ImGui::SetWindowSize( ImVec2( 550, 95 ) );
		if ( ImGui::BeginMenuBar( ) )
		{
			ImGui::Text( "User: %s", pca->get_credentials( ).at( 0 ) );
			float posOffset = 65.0f;
			ImGui::SameLine( ImGui::GetWindowWidth( ) - 35.0f );
			HelpMarker( "Toggles Vertial Sync for the cheat." );
			posOffset += ImGui::GetItemRectSize( ).x + 10.0f;
			ImGui::SameLine( ImGui::GetWindowWidth( ) - posOffset );
			ImGui::Checkbox( "VSync", &vsyncOption );

			posOffset += ImGui::GetItemRectSize( ).x + 135.0f;
			ImGui::SameLine( ImGui::GetWindowWidth( ) - posOffset );
			ImGui::Text( "Cheat Framerate: %.1f FPS", ImGui::GetIO( ).Framerate );

			ImGui::EndMenuBar( );
		}

		ImGui::BeginColumns( "MainMenuColums", 3, ImGuiColumnsFlags_NoResize );

		if ( ImGui::Button( "Aimbot Menu", ImVec2( ImGui::GetColumnWidth( ) * 0.92f, 40.0f ) ) )
		{
			aimbotMenu = !aimbotMenu;
		}

		ImGui::NextColumn( );

		if ( ImGui::Button( "ESP Menu", ImVec2( ImGui::GetColumnWidth( ) * 0.92f, 40.0f ) ) )
		{
			espMenu = !espMenu;
		}

		ImGui::NextColumn( );

		if ( ImGui::Button( "Misc Menu", ImVec2( ImGui::GetColumnWidth( ) * 0.93f, 40.0f ) ) )
		{
			miscMenu = !miscMenu;
		}

		ImGui::EndColumns( );

		ImGui::End( );
	}

	if ( aimbotMenu )
	{
		ImGui::Begin( "                    Aimbot Menu", nullptr, ImGuiWindowFlags_NoResize );
		ImGui::SetWindowSize( ImVec2( 410, 255 ) );

		ImGui::BeginColumns( "AimbotHeaders", 2, ImGuiColumnsFlags_NoResize );
		ImGui::Separator( );

		ImGui::Text( "Aimbot Options" );
		ImGui::NextColumn( );
		ImGui::Text( "Aimbot Key Config" );
		ImGui::SameLine( ); HelpMarker( "Change the button that activates aimbot." );

		ImGui::EndColumns( );
		ImGui::BeginColumns( "AimbotColums", 2, ImGuiColumnsFlags_NoResize );
		ImGui::Separator( );

		ImGui::Checkbox( "Aimbot Enabled", &Settings::bAimbotEnabled );
		ImGui::SameLine( ); HelpMarker( "Toggle overall aimbot." );
		ImGui::Checkbox( "Silent Aim", &Settings::bSilentAim );
		ImGui::SameLine( ); HelpMarker( "Aimbot will NOT move your mouse when active, allowing you to sustain regular\nmovement while aimbotting!" );
		ImGui::Checkbox( "Draw FOV", &Settings::bDrawFOV );
		ImGui::SameLine( ); HelpMarker( "Display the radius from your crosshair the aimbot will detect enemies." );
		ImGui::Checkbox( "No Recoil", &Settings::bNoRecoil );
		ImGui::SameLine( ); HelpMarker( "Disable all recoil while aiming." );
		ImGui::Checkbox( "No Spread", &Settings::bNoSpread );
		ImGui::SameLine( ); HelpMarker( "Disable all spread while aiming." );
		ImGui::NextColumn( );
		if ( ImGui::Selectable( "LEFT MOUSE", &Settings::aimKey[ 0 ] ) )
		{
			for ( int i = 0; i < 7; i++ )
			{
				if ( i == 0 ) continue;
				Settings::aimKey[ i ] = 0;
			}
		}
		if ( ImGui::Selectable( "RIGHT MOUSE", &Settings::aimKey[ 1 ] ) )
		{
			for ( int i = 0; i < 7; i++ )
			{
				if ( i == 1 ) continue;
				Settings::aimKey[ i ] = 0;
			}
		}
		if ( ImGui::Selectable( "CAPS LOCK", &Settings::aimKey[ 2 ] ) )
		{
			for ( int i = 0; i < 7; i++ )
			{
				if ( i == 2 ) continue;
				Settings::aimKey[ i ] = 0;
			}
		}
		if ( ImGui::Selectable( "LEFT ALT", &Settings::aimKey[ 3 ] ) )
		{
			for ( int i = 0; i < 7; i++ )
			{
				if ( i == 3 ) continue;
				Settings::aimKey[ i ] = 0;
			}
		}
		if ( ImGui::Selectable( "LEFT SHIFT", &Settings::aimKey[ 4 ] ) )
		{
			for ( int i = 0; i < 7; i++ )
			{
				if ( i == 4 ) continue;
				Settings::aimKey[ i ] = 0;
			}
		}
		if ( ImGui::Selectable( "MOUSE 4", &Settings::aimKey[ 5 ] ) )
		{
			for ( int i = 0; i < 7; i++ )
			{
				if ( i == 5 ) continue;
				Settings::aimKey[ i ] = 0;
			}
		}
		if ( ImGui::Selectable( "MOUSE 5", &Settings::aimKey[ 6 ] ) )
		{
			for ( int i = 0; i < 7; i++ )
			{
				if ( i == 6 ) continue;
				Settings::aimKey[ i ] = 0;
			}
		}

		ImGui::EndColumns( );
		ImGui::BeginColumns( "AimbotExtraColums", 1, ImGuiColumnsFlags_NoResize );
		ImGui::Separator( );

		ImGui::SliderInt( "FOV", &Settings::aimFov, 0, 1600 );
		ImGui::SameLine( ); HelpMarker( "Field of View. The radius from your crosshair the aimbot will detect enemies." );
		ImGui::SliderInt( "Aim Distance", &Settings::aimDist, 0, 300 );
		ImGui::SameLine( ); HelpMarker( "The maximum distance for aimbot to detect enemies." );
		ImGui::SliderInt( "Aim Smoothing", &Settings::aimSmooth, 0, 100 );
		ImGui::SameLine( ); HelpMarker( "Higher value = less snappy (more legit looking)." );

		ImGui::Separator( );
		ImGui::EndColumns( );

		ImGui::End( );
	}

	if ( espMenu )
	{
		ImGui::Begin( "                               ESP Menu", nullptr, ImGuiWindowFlags_NoResize );
		ImGui::SetWindowSize( ImVec2( 550, 240 ) );

		ImGui::BeginColumns( "EspColumns", 3, ImGuiColumnsFlags_NoResize );
		ImGui::Separator( );

		ImGui::Checkbox( "Overall ESP Enabled", &Settings::bESPEnable );
		ImGui::Checkbox( "2D Box", &Settings::bESPBoxes );
		ImGui::SameLine( ); HelpMarker( "Draws a 2D box around players." );
		ImGui::Checkbox( "Head ESP", &Settings::bESPHead );
		ImGui::SameLine( ); HelpMarker( "Places a little dot on heads." );

		ImGui::NextColumn( );

		ImGui::Checkbox( "Team ESP Enabled", &Settings::bESPTeam );
		ImGui::ColorEdit3( "Team Box Color", ( float* )&Settings::fESPBoxColorTeam, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoDragDrop );
		ImGui::ColorEdit3( "Team Head Color", ( float* )&Settings::fESPHeadColorTeam, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoDragDrop );

		ImGui::NextColumn( );

		ImGui::Checkbox( "Enemy ESP Enabled", &Settings::bESPEnemy );
		ImGui::ColorEdit3( "Enemy Box Color", ( float* )&Settings::fESPBoxColor, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoDragDrop );
		ImGui::ColorEdit3( "Enemy Head Color", ( float* )&Settings::fESPHeadColor, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoDragDrop );

		ImGui::EndColumns( );
		ImGui::BeginColumns( "ESPColumsTw", 1, ImGuiColumnsFlags_NoResize );
		ImGui::Separator( );

		ImGui::SliderFloat( " 2D Box Thickness", &Settings::fESPBoxesThickness, 1.000, 10.000 );
		ImGui::SameLine( ); HelpMarker( "Set the thickness for the 2D Box ESP." );

		ImGui::EndColumns( );
		ImGui::BeginColumns( "ESPColumsThr", 2, ImGuiColumnsFlags_NoResize );
		ImGui::Separator( );

		ImGui::Checkbox( "Distance ESP", &Settings::bESPDistance );
		ImGui::SameLine( ); HelpMarker( "View distance between you and other players." );
		ImGui::Checkbox( "Cav ESP", &Settings::bCavESP );
		ImGui::SameLine( ); HelpMarker( "Toggle Caviera ESP." );
		ImGui::Checkbox( "Health ESP", &Settings::bESPHealth );
		ImGui::SameLine( ); HelpMarker( "View health of players." );
		ImGui::Checkbox( "Snaplines", &Settings::bESPSnapline );
		ImGui::SameLine( ); HelpMarker( "Draws lines from the bottom-center of your screen\ndirectly to enemies." );

		ImGui::NextColumn( );

		ImGui::Checkbox( "Glow Enabled", &GlowSettings::bGlowEnable );
		ImGui::SameLine( ); HelpMarker( "Draw a glowing outline of objects and players through walls." );
		ImGui::SameLine( ImGui::GetItemRectSize( ).x + 139.0f ); HelpMarker( "Click on the colored square to open a color picker.\nCTRL+Click or Double-Click on the individual component to input a value.\n" );
		ImGui::ColorEdit3( "Glow Color", ( float* )&GlowSettings::fGlowColor, ImGuiColorEditFlags_HDR | ImGuiColorEditFlags_NoDragDrop );
		ImGui::NewLine( ); ImGui::NewLine( ); ImGui::NewLine( );

		ImGui::Separator( );
		ImGui::EndColumns( );

		ImGui::End( );
	}

	if ( miscMenu )
	{
		ImGui::Begin( "  Misc Menu", nullptr, ImGuiWindowFlags_NoResize );
		ImGui::SetWindowSize( ImVec2( 125, 85 ) );

		ImGui::BeginColumns( "MiscColums", 1, ImGuiColumnsFlags_NoResize );
		ImGui::Separator( );

		if ( ImGui::Button( "Unlock All", ImVec2( ImGui::GetColumnWidth( ) * 0.90f, 40.0f ) ) )
		{
			pcm->virtual_protect( pcm->r6base + ADDRESS_UNLOCKALL, 0x300, 0x40 );

			BYTE ass1 = 0x19;
			pcm->wvm<BYTE>( pcm->r6base + ADDRESS_UNLOCKALL + 0x23C, ass1 );

			BYTE ass2 = 0x0;
			pcm->wvm<BYTE>( pcm->r6base + ADDRESS_UNLOCKALL + 0x259, ass2 );
		}

		ImGui::Separator( );
		ImGui::EndColumns( );

		ImGui::End( );
	}
}