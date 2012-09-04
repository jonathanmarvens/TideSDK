/**
 * Appcelerator Kroll - licensed under the Apache Public License 2
 * see LICENSE in the root folder for details on the license.
 * Copyright (c) 2009 Appcelerator, Inc. All Rights Reserved.
 */

#ifndef _APPLICATION_BINDING_H_
#define _APPLICATION_BINDING_H_

#include <tide/tide.h>
#include <map>
#include <vector>
#include <string>

namespace tide
{
	class ApplicationBinding : public KAccessorObject
	{
		public:
		ApplicationBinding(SharedApplication application, bool current = false);

		private:
		SharedApplication application;
		bool current;

		void _GetID(const ValueList& args, ValueRef value);
		void _GetGUID(const ValueList& args, ValueRef value);
		void _GetName(const ValueList& args, ValueRef result);
		void _GetVersion(const ValueList& args, ValueRef value);
		void _GetPath(const ValueList& args, ValueRef value);
		void _GetExecutablePath(const ValueList& args, ValueRef value);
		void _GetResourcesPath(const ValueList& args, ValueRef value);
		void _GetDataPath(const ValueList& args, ValueRef value);
		void _GetManifestPath(const ValueList& args, ValueRef value);
		void _GetManifest(const ValueList& args, ValueRef value);
		void _GetProperties(const ValueList& args, ValueRef value);
		void _IsCurrent(const ValueList& args, ValueRef value);
		void _GetPID(const ValueList& args, ValueRef value);
		void _GetArguments(const ValueList& args, ValueRef value);
		void _HasArgument(const ValueList& args, ValueRef value);
		void _GetArgumentValue(const ValueList& args, ValueRef value);
		void _GetDependencies(const ValueList& args, ValueRef value);
		void _ResolveDependencies(const ValueList& args, ValueRef value);
		void _GetComponents(const ValueList& args, ValueRef value);
		void _GetModules(const ValueList& args, ValueRef value);
		void _GetRuntime(const ValueList& args, ValueRef value);
		void _GetAvailableComponents(const ValueList& args, ValueRef value);
		void _GetAvailableModules(const ValueList& args, ValueRef value);
		void _GetAvailableRuntimes(const ValueList& args, ValueRef value);
		void _GetBundledComponents(const ValueList& args, ValueRef value);
		void _GetBundledModules(const ValueList& args, ValueRef value);
		void _GetBundledRuntimes(const ValueList& args, ValueRef value);
	};
}

#endif
