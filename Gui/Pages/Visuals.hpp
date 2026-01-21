#pragma once
#include <Includes/includes.hpp>
#include <windows.h>
#include <iostream>
#include <thread>
#include <Includes/CustomWidgets/Preview.hpp>

#include <Core/Core.hpp>

using namespace std;

namespace Visuals {

	static int iSubTabCount = 0;
	static float SubTabAlpha = 0.f;
	static int iSubTab = 0;

	void Render( ) {


		ImGui::SetCursorPos(ImVec2(490, 50));

		if ( Custom::SubTab( xorstr( "Players" ), 0 == iSubTabCount ) ) {
			iSubTabCount = 0;
		}
		ImGui::SameLine( );
		if ( Custom::SubTab( xorstr( "Vehicles" ), 1 == iSubTabCount ) ) {
			iSubTabCount = 1;
		}


		SubTabAlpha = ImClamp( SubTabAlpha + ( 5.f * ImGui::GetIO( ).DeltaTime * ( iSubTabCount == iSubTab ? 1.f : -1.f ) ), 0.f, 1.f );

		if ( SubTabAlpha == 0.f )
			iSubTab = iSubTabCount;


		ImGui::PushStyleVar( ImGuiStyleVar_Alpha, SubTabAlpha * ImGui::GetStyle( ).Alpha );

		ImGui::SetCursorPos( ImVec2(140, 120) );
		ImGui::BeginGroup( );
		{
			switch ( iSubTab )
			{
			case 0: //Players
				ImGui::BeginGroup( );
				{
					ImGui::BeginChild( xorstr( "Globals#ESP" ), ImVec2(500, 340), false, 0 );
					{
						if (Custom::CheckBoxCfg(xorstr("Show"), &g_Config.ESP->Enabled, [&]() {
							static int KeyMode = 2;
							ImGui::Keybind(xorstr("Bind"), &g_Config.ESP->KeyBind, &KeyMode);

							
							Custom::CheckBox(xorstr("Friends"), &g_Config.ESP->FriendsMarker);

							}, false)) {
							g_Config.ESP->FriendsMarker = true;
						}

					
						Custom::CheckBox(xorstr("Show Preview"), &g_Config.ESP->ShowPreview);
						if ( Custom::CheckBox( xorstr( "Show Box" ), &g_Config.ESP->Box ) ) {}
						if ( Custom::CheckBox( xorstr( "Show FilledBox" ), &g_Config.ESP->FilledBox ) ) {}

						Custom::CheckBox( xorstr( "Show Names" ), &g_Config.ESP->UserNames );
						Custom::CheckBox( xorstr( "Show Weapon" ), &g_Config.ESP->WeaponName );
						Custom::CheckBox( xorstr( "Show Distance" ), &g_Config.ESP->DistanceFromMe );


						if (Custom::CheckBoxCfg(xorstr("Show Skeleton"), &g_Config.ESP->Skeleton, [&]() {
							ImGui::SliderFloat("Skeleton", &g_Config.ESP->SkeletonThickness, 0.5f, 3.0f, "%.1f");
							}, false))
						{
							Core::SDK::Pointers::pLocalPlayer->RemoveKinematics();
						}



						Custom::CheckBox( xorstr( "Show Head" ), &g_Config.ESP->HeadCircle );
						Custom::CheckBox( xorstr( "Show HealthBar" ), &g_Config.ESP->HealthBar );
						Custom::CheckBox( xorstr( "Show ArmorBar" ), &g_Config.ESP->ArmorBar );
						Custom::CheckBox( xorstr( "Show SnapLines" ), &g_Config.ESP->SnapLines );
						Custom::CheckBox( xorstr( "Show Highlight" ), &g_Config.ESP->HighlightVisible );
						
						Custom::CheckBox( xorstr( "Show LocalPlayer" ), &g_Config.ESP->ShowLocalPlayer );
						Custom::CheckBox( xorstr( "Ignore Dead" ), &g_Config.ESP->IgnoreDead );
						Custom::CheckBox( xorstr( "Ignore NPCs" ), &g_Config.ESP->IgnoreNPCs );

						ImGui::SliderInt( xorstr( "Max Distance" ), &g_Config.ESP->MaxDistance, 0, 1000, xorstr( "%dm" ), 0 );
					}
					ImGui::EndChild( );
				}
				ImGui::EndGroup( );
				break;
			case 1: //Vehicles
				ImGui::BeginGroup( );
				{
					ImGui::BeginChild( xorstr( "Globals" ), ImVec2(500, 340), false, 0 );
					{
						Custom::CheckBox( xorstr( "Show" ), &g_Config.VehicleESP->Enabled );
						Custom::CheckBox( xorstr( "Show Names" ), &g_Config.VehicleESP->VehName );
						Custom::CheckBox( xorstr( "Locked/Unlocked" ), &g_Config.VehicleESP->ShowLockUnlock );
						Custom::CheckBox( xorstr( "Show SnapLines" ), &g_Config.VehicleESP->SnapLines );
						Custom::CheckBox( xorstr( "Show Distance" ), &g_Config.VehicleESP->DistanceFromMe );
					    ImGui::SliderInt(xorstr("Max Distance"), &g_Config.VehicleESP->MaxDistance, 0, 1000, xorstr("%dm"), 0);
					}
					ImGui::EndChild( );
				}
				ImGui::EndGroup( );
				break;
			default:
				break;
			}

		}
		ImGui::EndGroup( );
		ImGui::PopStyleVar( );
	}
}