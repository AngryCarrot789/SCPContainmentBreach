#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <cstdio>
#include "SCPContainmentBreach.h"
#include "logging/logger.h"

HINSTANCE hMainInstance;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
	//Open console in debug mode
#ifdef _DEBUG
	AllocConsole();
	//SetWindowPos(GetConsoleWindow(), 0, 1920, 200, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	AttachConsole(GetCurrentProcessId());
	FILE* std_out = freopen("CON", "w", stdout);
#endif

	Logger::LogLine(Logger::FormatSenderInfo(L"WinMain", L"Starting game"));

	hMainInstance = hInstance;

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