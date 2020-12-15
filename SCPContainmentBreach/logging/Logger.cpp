#include "Logger.h"

void Logger::Log(wstring_t message)
{
	std::wcout << message;
}

void Logger::LogLine(wstring_t message)
{
	std::wcout << message << L'\n';
}

void Logger::LogLineWindow(wstring_t title, wstring_t message)
{
	wstring_t msg = L"[Window '" + wstring_t(title) + L"'] -- " + message;
	LogLine(msg);
}

void Logger::LogError(wstring_t exception, wstring_t message)
{
	wstring_t msg = exception + L" exception: " + message;
	LogLine(msg);
}

void Logger::LogWindow(wstring_t title, wstring_t message)
{
	wstring_t msg = L"[Window '" + wstring_t(title) + L"'] -- " + message;
	Log(msg);
}

void Logger::LogLineFormat(wstring_t title, wstring_t info)
{
	Logger::LogLine(Logger::FormatSenderInfo(title, info));
}

void Logger::LogLineFormat1(wstring_t info1, wstring_t value1)
{
	wstring_t str =
		info1 + (value1);
	LogLine(str.c_str());
}

void Logger::LogLineFormat2(wstring_t info1, wstring_t value1, wstring_t info2, wstring_t value2)
{
	wstring_t str =
		info1 + (value1)+L" | " +
		info2 + (value2);
	LogLine(str.c_str());
}

void Logger::LogLineFormat3(wstring_t info1, wstring_t value1, wstring_t info2, wstring_t value2, wstring_t info3, wstring_t value3)
{
	wstring_t str =
		info1 + (value1)+L" | " +
		info2 + (value2)+L" | " +
		info3 + (value3);
	LogLine(str.c_str());
}

void Logger::LogLineFormat4(wstring_t info1, wstring_t value1, wstring_t info2, wstring_t value2, wstring_t info3, wstring_t value3, wstring_t info4, wstring_t value4)
{
	wstring_t str =
		info1 + (value1)+L" | " +
		info2 + (value2)+L" | " +
		info3 + (value3)+L" | " +
		info4 + (value4);
	LogLine(str.c_str());
}

void Logger::ClearLogs()
{
	system("cls");
}