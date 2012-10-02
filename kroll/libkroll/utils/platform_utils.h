/**
 * Appcelerator Kroll - licensed under the Apache Public License 2
 * see LICENSE in the root folder for details on the license.
 * Copyright (c) 2009 Appcelerator, Inc. All Rights Reserved.
 */
#ifndef _KR_PLATFORM_UTILS_H_
#define _KR_PLATFORM_UTILS_H_
#include <string>
#include "poco/KTypes.h"
#define MAC_ADDRESS_SIZE 6

namespace UTILS_NS
{
	typedef KPoco::KUInt8 MACAddress[MAC_ADDRESS_SIZE]; /// Ethernet address.

	namespace PlatformUtils
	{
		/*
		 * Get the first MAC address of this computer
		 * @returns the first MAC address in standard dotted format
		 */
		KROLL_API std::string GetFirstMACAddress();

		/*
		 * Get the first MAC address of this computer
		 * @returns the first MAC address in standard dotted format
		 */
		KROLL_API void GetFirstMACAddressImpl(MACAddress&);

		/**
		 * Generate an ID for this machine based on it's MAC Address.
		 */
		KROLL_API std::string GetMachineId();

		/**
		 * Get the username of the current user.
		 */
		KROLL_API std::string GetUsername();

		/**
		 * Get the number of processors on this machine.
		 */
		KROLL_API int GetProcessorCount();
	};
}
#endif
