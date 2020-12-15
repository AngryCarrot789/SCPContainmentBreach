#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <cstdio>
#include "game/render/presets/Presets.h"
#include "SCPContainmentBreach.h"
#include "logging/logger.h"
#include "game/GameHeader.h"
#include "resources.h"

Mesh*    QUAD			;
Mesh*    CUBE			;
Mesh*    TUNNEL			;
Shader*  SKY			;
Shader*  PINK			;
Shader*  TEXTURE		;
Texture* ELECTROMAGNET  ;
Texture* CHECKER_GREY   ;
Texture* CHECKER_GREEN  ;
Texture* GOLD			;

HINSTANCE MAIN_INSTANCE;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
	//Open console in debug mode
#ifdef _DEBUG
	AllocConsole();
	//SetWindowPos(GetConsoleWindow(), 0, 1920, 200, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	AttachConsole(GetCurrentProcessId());
	FILE* std_out = freopen("CON", "w", stdout);
#endif

	QUAD = new Mesh("quad.obj");
	CUBE = new Mesh("cube.obj");
	TUNNEL = new Mesh("tunnel.obj");
	SKY = new Shader("sky");
	PINK = new Shader("pink");
	TEXTURE = new Shader("texture");
	ELECTROMAGNET = new Texture("electromagnet.bmp", 1, 1);
	CHECKER_GREY = new Texture("checker_grey.bmp", 1, 1);
	CHECKER_GREEN = new Texture("checker_green.bmp", 1, 1);
	GOLD = new Texture("gold.bmp", 1, 1);

	Logger::LogLine(Logger::FormatSenderInfo(L"WinMain", L"Starting game"));

	MAIN_INSTANCE = hInstance;

	SCPContainmentBreach* scp = new SCPContainmentBreach();
	scp->Initialise();

	int nErrorCode = scp->Run();

	switch (nErrorCode) {
		case ErrorCodes::ECGLOOP_EXITED_UNEXPECTED:
			Logger::LogLine(Logger::FormatSenderInfo(L"WinMain", L"Game exited unexpectedly..."));
			break;
		case ErrorCodes::ECGLOOP_FORCEEXITED:
			Logger::LogLine(Logger::FormatSenderInfo(L"WinMain", L"Forcefully exited game."));
			break;
		case ErrorCodes::EC_NOERROR:
			Logger::LogLine(Logger::FormatSenderInfo(L"WinMain", L"Exited game without errors."));
			break;
	}

	delete scp;

	Logger::LogLine(Logger::FormatSenderInfo(L"WinMain", L"Exited game and successfully shutdown. Bye :))"));

	return 0;
}