#pragma once
#include <Includes/Includes.hpp>

#include <d3dx11.h>
#include <d3d11.h>
#include <D3DX11tex.h>
#pragma comment( lib, "d3d11.lib" )
#pragma comment( lib, "D3DX11.lib" )

class cColors {
public:
	// -- ACENTOS VIOLETAS (Principales) --
	// Color principal (Checkboxes activos, Sliders, etc.) - Violeta Neón
	ImVec4 Base = ImColor(138, 43, 226); 
	// Color de Pestañas activas - Mismo violeta o ligeramente más claro
	ImVec4 Tabs = ImColor(147, 112, 219); 

	// -- TEXTO --
	ImVec4 PrimaryText = ImColor( 240, 240, 255 ); // Blanco con tinte lavanda
	ImVec4 SecundaryText = ImColor( 160, 140, 180 ); // Gris violáceo

	ImVec4 FeaturesText = ImColor( 230, 230, 250 ); // Lavanda claro
	ImVec4 SecundaryFeaturesText = ImColor( 130, 120, 150 );

	// -- BORDES Y LINEAS --
	ImVec4 BorderCol = ImColor( 60, 40, 80 ); // Violeta muy oscuro para bordes sutiles
	ImVec4 LinesCol = ImColor( 50, 35, 70 );

	// -- FONDOS (Violeta Oscuro / Deep Purple) --
	// Fondo principal del menú
	ImVec4 BackgroundCol = ImColor( 15, 12, 20, 255 ); 

	// Fondo de secciones internas (Child windows)
	ImVec4 ChildCol = ImColor( 20, 16, 28 );
	ImVec4 ChildBorderCol = ImColor( 45, 30, 60 );

	// Barra de Título
	ImVec4 TitleBar = ImColor( 20, 16, 28 );
	ImVec4 TitleBarBorder = ImColor( 45, 30, 60 );

	// Barra Lateral
	ImVec4 SideBar = ImColor( 18, 14, 24 );
	ImVec4 SideBarBorder = ImColor( 50, 35, 75 );

	// -- INTERACCIÓN --
	// Color al pasar el mouse por encima
	ImVec4 ButtonHovered = ImColor( 160, 100, 240, 150 );
	ImVec4 TestingTest = ImColor( 138, 43, 226 );

	// Inputs (Cajas de texto)
	ImVec4 InputBackground = ImColor( 25, 20, 35, 255 );
	ImVec4 InputBorder = ImColor( 60, 45, 90, 255 );
};

inline cColors g_Col;

class c_globals {
public:
	std::string id;
	std::string version;
	DWORD ProcIdFiveM = 0;
	int Pid;

	bool g_bPassedByThisVerify;
	uintptr_t g_VerifyLogin;
	bool done;
	bool IsOpen;

	std::string ServerIp = "192.168.0.25";
	std::string UserName = " ";
	std::string Role = " ";


	ImVec2 TestePos;

	char m_Config[ 6000 ];
	HWND g_hCheatWindow;
	HWND g_hGameWindow;
	ImVec2 g_vGameWindowSize;
	ImVec2 g_vGameWindowPos;
	ImVec2 g_vGameWindowCenter;

	ImFont * m_FontBig;
	ImFont * m_FontBigSmall;
	ImFont * m_FontNormal;
	ImFont * m_FontSecundary;
	ImFont * m_FontSmaller;
	ImFont * m_DrawFont;
	ImFont * m_Expand;

	ImFont * FontAwesomeSolid;
	ImFont * FontAwesomeSolidSmall;
	ImFont * FontAwesomeRegular;
	ImFont * FontAwesomeBrands;

	ID3D11ShaderResourceView* backgroud = nullptr;
	ID3D11ShaderResourceView * Logo = nullptr;

	struct FiveM_Peds_t {
		ID3D11ShaderResourceView * A_C_Chimp = nullptr;
		ID3D11ShaderResourceView* a_m_y_skater_01 = nullptr;
	}FiveM_PedsPic;
	
};

inline c_globals g_Variables;

class c_menu {
public:

	enum PAGES {
		Combat,
		Visuals,
		Local,
		Settings,
		Login
	};

	bool IsOpen;

	int iTabCount = 0;
	float TabAlpha = 0.f;
	int iCurrentPage = 6;
	float TabAdd = 0.f;
	bool IsLogged = true;
	char cDiscordId[ 200 ] ;
	char user[30] = ""; 
	char pass[30] = ""; 
	bool login_success = false;
	std::string server_response;

	ImVec2 MenuSize{ 680, 500 };
	bool particles = true;


};

inline c_menu g_MenuInfo;
