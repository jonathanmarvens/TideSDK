/**
 * Appcelerator Titanium - licensed under the Apache Public License 2
 * see LICENSE in the root folder for details on the license.
 * Copyright (c) 2008-2010 Appcelerator, Inc. All Rights Reserved.
 */

#ifndef _NETWORK_BINDING_H_
#define _NETWORK_BINDING_H_

#include <kroll/kroll.h>

namespace ti
{
	class NetworkBinding;
	class HostBinding;
}

namespace ti
{
	class NetworkBinding : public KAccessorObject
	{
	public:
		NetworkBinding(Host*);
		virtual ~NetworkBinding();

		Host* GetHost();
		static const std::string& GetFirstIPAddress();

	private:
		Host* host;
		KObjectRef global;

		AutoPtr<HostBinding> GetHostBinding(std::string host);

		void _GetFirstMACAddress(const ValueList& args, KValueRef result);
		void _GetFirstIPAddress(const ValueList& args, KValueRef result);
		void _GetInterfaces(const ValueList& args, KValueRef result);
		void _CreateIPAddress(const ValueList& args, KValueRef result);
		void _CreateTCPSocket(const ValueList& args, KValueRef result);
		void _CreateTCPServerSocket(const ValueList& args, KValueRef result);
		void _CreateIRCClient(const ValueList& args, KValueRef result);
		void _CreateHTTPClient(const ValueList& args, KValueRef result);
		void _CreateHTTPServer(const ValueList& args, KValueRef result);
		void _CreateHTTPCookie(const ValueList& args, KValueRef result);
		void _EncodeURIComponent(const ValueList &args, KValueRef result);
		void _DecodeURIComponent(const ValueList &args, KValueRef result);
		void _GetHostByName(const ValueList& args, KValueRef result);
		void _GetHostByAddress(const ValueList& args, KValueRef result);
		void _SetHTTPProxy(const ValueList& args, KValueRef result);
		void _SetHTTPSProxy(const ValueList& args, KValueRef result);
		void _GetHTTPProxy(const ValueList& args, KValueRef result);
		void _GetHTTPSProxy(const ValueList& args, KValueRef result);
	};
}

#endif
