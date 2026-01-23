#pragma once
#include <Includes/Includes.hpp>
#include <windows.h>
#include <iostream>
#include <thread>
#include <destruct.hpp>


using namespace std;

namespace Settings {

	static int iSubTabCount = 0;
	static float SubTabAlpha = 0.f;
	static int iSubTab = 0;


	void Render( ) {


		//ImGui::PushStyleVar( ImGuiStyleVar_::ImGuiStyleVar_ItemSpacing, ImVec2( 6, 0 ) );

		ImGui::SetCursorPos(ImVec2(530, 50));

		if ( Custom::SubTab( xorstr( "Main" ), 0 == iSubTabCount ) ) {
			iSubTabCount = 0;
		}
		ImGui::SameLine( );
		if ( Custom::SubTab( xorstr( "User" ), 1 == iSubTabCount ) ) {
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
			case 0: //Settings
				ImGui::BeginGroup( );
				{
					ImGui::BeginChild( xorstr( "Globals" ), ImVec2(500, 340), false, 0 );
					{
						Custom::CheckBox(xorstr("Second Monitor"), &g_Config.General->SecondMonitor);
						Custom::CheckBox( xorstr( "VSync" ), &g_Config.General->VSync );
						if (Custom::CheckBox(xorstr("Stream Proof"), &g_Config.General->StreamProof))
						{
							if (g_Config.General->StreamProof)
							{
								SetWindowDisplayAffinity(g_Variables.g_hCheatWindow, WDA_EXCLUDEFROMCAPTURE);
							}
							else
							{								
								SetWindowDisplayAffinity(g_Variables.g_hCheatWindow, WDA_NONE);

								SetWindowPos(
									g_Variables.g_hCheatWindow,
									HWND_TOPMOST,
									0, 0, 0, 0,
									SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_SHOWWINDOW
								);

								RedrawWindow(
									g_Variables.g_hCheatWindow,
									NULL,
									NULL,
									RDW_INVALIDATE | RDW_UPDATENOW | RDW_FRAME
								);
							}
						}
					


						static int KeyMode = 1;
						ImGui::Keybind( xorstr( "Menu Key" ), &g_Config.General->MenuKey, &KeyMode );
					
						if (Custom::Button(xorstr("Export Config"), ImVec2(-1, 30), 0))
						{
							std::thread cfgExport([] {
								std::string CfgMsg = g_Config.SaveCurrentConfig(xorstr("..."));
								NotifyManager::Send(CfgMsg.c_str(), 3000);
								});

							cfgExport.detach();
						}
						if (Custom::Button(xorstr("Import Config"), ImVec2(-1, 30), 0))
						{
							std::thread cfgImport([] { NotifyManager::Send(g_Config.LoadCfg(xorstr("..."), Utils::GetClipboard()).c_str(), 3000); });

							cfgImport.detach();
						}

                        // --- BOT�N DESTRUCT MODIFICADO ---
						// Color rojizo para indicar peligro/acci�n destructiva
						ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.9f, 0.2f, 0.2f, 1.0f)); 
						if (Custom::Button(xorstr("DESTRUCT"), ImVec2(-1, 30), 0))
						{
							// Ejecutamos en un hilo para no congelar la UI mientras limpia
							std::thread([]() {
								// 1. Limpieza de rastros (Prefetch, Strings, etc.)
								Prefetch_Cleaner();

								// 2. Notificaci�n r�pida
								NotifyManager::Send(xorstr("Self Destructing..."), 1000);
								
								// Peque�a pausa para asegurar que el cleaner termin� de escribir en disco
								std::this_thread::sleep_for(std::chrono::milliseconds(500)); 

								// 3. MATAR EL PROCESO (Force Kill)
								// TerminateProcess cierra el programa inmediatamente sin esperar hilos colgados.
								TerminateProcess(GetCurrentProcess(), 0);
							}).detach();
						}
						ImGui::PopStyleColor();
                        // ---------------------------------
					}
					ImGui::EndChild( );
				}
				ImGui::EndGroup( );

				break;
			case 1: //Colors
				ImGui::BeginGroup( );
				{
					ImGui::BeginChild( xorstr( "Fivem" ), ImVec2( g_MenuInfo.MenuSize.x - ( 150 + 24 ), 300 ), false, 0 );
					{
						Custom::CheckBoxCfg(xorstr("PlayerMark"), &g_Config.General->WaterMark, [&]() {
							static bool Rainbow = false;
							Custom::CheckBox(xorstr("Rainbow"), &Rainbow);
							});

						Custom::CheckBoxCfg(xorstr("ADM list"), &g_Config.General->ArrayList, [&]() {
							static bool Rainbow = false;
							Custom::CheckBox(xorstr("Rainbow"), &Rainbow);
							});
					}
					ImGui::EndChild( );
				}
				ImGui::EndGroup( );
				ImGui::SameLine( );
				ImGui::BeginGroup( );
				{
				}
				ImGui::EndGroup( );
				break;
			default:
				break;
			}

		}
		ImGui::EndGroup( );

        ImGui::PopStyleVar();
    }
} // nam
