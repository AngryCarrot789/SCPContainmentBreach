#ifndef HF_LOGGER
#define HF_LOGGER

#include <iostream>
#include "../standard.h"
#include "ErrorCodes.h"

class Logger
{
public:
	Logger() { }
	~Logger() { }

	static wstring_t FormatSenderInfo(wstring_t sender, wstring_t info) {
		return sender + L": " + info;
	}

	static wstring_t EncaseBrackets(wstring_t info) {
		return Encase(info, L"[", L"]");
	}

	static wstring_t Encase(wstring_t info, wstring_t start, wstring_t end) {
		return start + info + end;
	}

	static wstring_t ToInt(int a) {
		return std::to_wstring(a);
	}

	static void Log(wstring_t message);
	static void LogLine(wstring_t message);
	static void LogWindow(wstring_t title, wstring_t message);
	static void LogLineWindow(wstring_t title, wstring_t message);
	static void LogError(wstring_t exception, wstring_t message);

	static void LogLineFormat1(wstring_t info1, wstring_t value1);
	static void LogLineFormat2(wstring_t info1, wstring_t value1, wstring_t info2, wstring_t value2);
	static void LogLineFormat3(wstring_t info1, wstring_t value1, wstring_t info2, wstring_t value2, wstring_t info3, wstring_t value3);
	static void LogLineFormat4(wstring_t info1, wstring_t value1, wstring_t info2, wstring_t value2, wstring_t info3, wstring_t value3, wstring_t info4, wstring_t value4);

	static void ClearLogs();
private:

};

#endif
