/**
 * Appcelerator Kroll - licensed under the Apache Public License 2
 * see LICENSE in the root folder for details on the license.
 * Copyright (c) 2009 Appcelerator, Inc. All Rights Reserved.
 */
#ifndef _WIN32_UTILS_H_
#define _WIN32_UTILS_H_
#include <string>
namespace UTILS_NS
{
	namespace Win32Utils
	{
		/*
		 * Easily get the result of a FormatMessage
		 * @param errorCode the error code to get the message for
		 * @returns a normal, all-American std::string for once
		 */
		TIDE_API std::string QuickFormatMessage(
			DWORD errorCode,
			DWORD flags=FORMAT_MESSAGE_FROM_SYSTEM |
				FORMAT_MESSAGE_ALLOCATE_BUFFER |
				FORMAT_MESSAGE_IGNORE_INSERTS);
	};

	namespace FileUtils
	{
		TIDE_API void CopyRecursive(const std::string &dir,
			const std::string &dest, const std::string& exclude = "");

		/* Some wchar versions of popular FileUtils functions */
		TIDE_API bool IsFile(const std::wstring& path);
		TIDE_API std::string ReadFile(const std::wstring& path);

		/**
		 * Delete the file at the given path
		 */
		TIDE_API bool DeleteFile(const std::string &path);
	}

	TIDE_API std::wstring UTF8ToWide(const std::string& in);
	TIDE_API std::wstring UTF8ToWide(const char* in);
	TIDE_API std::string WideToUTF8(const std::wstring& in);
	TIDE_API std::string WideToUTF8(const wchar_t* in);
	TIDE_API std::string UTF8ToSystem(const std::string& in);
	TIDE_API std::string UTF8ToSystem(const char* in);
	TIDE_API std::string WideToSystem(const std::wstring& in);
	TIDE_API std::string WideToSystem(const wchar_t* in);

	TIDE_API std::wstring MultiByteToWide(const std::string& in, UINT codePage);
	TIDE_API std::wstring MultiByteToWide(const char* in, size_t length, UINT codePage);
	TIDE_API std::string WideToMultiByte(const std::wstring& in, UINT codePage);
	TIDE_API std::string WideToMultiByte(const wchar_t* in, size_t length, UINT codePage);
	TIDE_API std::string MultiByteToMultiByte(const std::string& in, UINT codePageIn,
		UINT codePageOut);
}
#endif
