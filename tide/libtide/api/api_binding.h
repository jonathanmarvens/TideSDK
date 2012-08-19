/**
 * Appcelerator Kroll - licensed under the Apache Public License 2
 * see LICENSE in the root folder for details on the license.
 * Copyright (c) 2008 Appcelerator, Inc. All Rights Reserved.
 */

#ifndef _API_BINDING_H_
#define _API_BINDING_H_

#include <tide/tide.h>
#include <map>
#include <vector>
#include <string>
#include <Poco/Thread.h>
#include <Poco/RunnableAdapter.h>

namespace tide
{
	class APIBinding : public KAccessorObject
	{
		public:
		APIBinding(Host* host);
		virtual ~APIBinding();

		void Log(int severity, ValueRef);
		static ListRef ComponentVectorToList(
			vector<SharedComponent>&,
			KComponentType filter = UNKNOWN);
		static ListRef DependencyVectorToList(
			std::vector<SharedDependency>&);
		static ListRef ManifestToList(
			vector<pair<string, string> >&);


		private:
		Host* host;
		KObjectRef global;
		Logger* logger;

		// Use a FastMutex to protect the installer, because we are
		// always trying to lock it in the same thread.
		Poco::FastMutex installerMutex;
		Poco::Thread* installerThread;
		Poco::RunnableAdapter<APIBinding>* installerThreadAdapter;
		vector<SharedDependency> installerDependencies;
		MethodRef installerCallback;

		void RunInstaller();

		void _Set(const ValueList& args, ValueRef result);
		void _Get(const ValueList& args, ValueRef result);
		void _AddEventListener(const ValueList& args, ValueRef result);
		void _RemoveEventListener(const ValueList& args, ValueRef result);
		void _FireEvent(const ValueList& args, ValueRef result);

		Logger::Level ValueToLevel(ValueRef v);
		void _SetLogLevel(const ValueList& args, ValueRef result);
		void _GetLogLevel(const ValueList& args, ValueRef result);
		void _RunOnMainThread(const ValueList& args, ValueRef result);
		void _RunOnMainThreadAsync(const ValueList& args, ValueRef result);

		void _Print(const ValueList& args, ValueRef result);
		void _Log(const ValueList& args, ValueRef result);
		void _LogTrace(const ValueList& args, ValueRef result);
		void _LogDebug(const ValueList& args, ValueRef result);
		void _LogInfo(const ValueList& args, ValueRef result);
		void _LogNotice(const ValueList& args, ValueRef result);
		void _LogWarn(const ValueList& args, ValueRef result);
		void _LogError(const ValueList& args, ValueRef result);
		void _LogCritical(const ValueList& args, ValueRef result);
		void _LogFatal(const ValueList& args, ValueRef result);

		void _GetInstalledComponentsImpl(KComponentType type, const ValueList& args, ValueRef result);
		void _GetApplication(const ValueList& args, ValueRef value);
		void _GetInstalledComponents(const ValueList& args, ValueRef value);
		void _GetInstalledModules(const ValueList& args, ValueRef value);
		void _GetInstalledSDKs(const ValueList& args, ValueRef value);
		void _GetInstalledMobileSDKs(const ValueList& args, ValueRef value);
		void _GetInstalledRuntimes(const ValueList& args, ValueRef value);
		void _GetComponentSearchPaths(const ValueList& args, ValueRef value);
		void _ReadApplicationManifest(const ValueList& args, ValueRef value);
		void _ComponentGUIDToComponentType(const ValueList& args, ValueRef value);
		void _GetEnvironment(const ValueList& args, ValueRef value);
		
		void _CreateDependency(const ValueList& args, ValueRef value);
		void _InstallDependencies(const ValueList& args, ValueRef value);

		void _CreateKObject(const ValueList& args, ValueRef result);
		void _CreateMethod(const ValueList& args, ValueRef result);
		void _CreateList(const ValueList& args, ValueRef result);
		void _CreateBytes(const ValueList& args, ValueRef result);
	};

	/**
	 * An wrapper for a Object which encapsulates another one for testing
	 */
	class KObjectWrapper : public Object
	{
	public:
		KObjectWrapper(KObjectRef object);
		void Set(const char *name, ValueRef value);
		ValueRef Get(const char *name);
		bool HasProperty(const char *name);
		SharedStringList GetPropertyNames();
		SharedString DisplayString(int levels);
		bool Equals(KObjectRef other);

	private:
		KObjectRef object;
	};

	/**
	 * An wrapper for a Method which encapsulates another one for testing
	 */
	class MethodWrapper : public Method
	{
	public:
		MethodWrapper(MethodRef method);
		ValueRef Call(const ValueList& args);
		void Set(const char *name, ValueRef value);
		ValueRef Get(const char *name);
		bool HasProperty(const char *name);
		SharedStringList GetPropertyNames();
		SharedString DisplayString(int levels);
		bool Equals(KObjectRef other);

	private:
		MethodRef method;
	};

	/**
	 * An wrapper for a List which encapsulates another one for testing
	 */
	class ListWrapper : public List
	{
	public:
		ListWrapper(ListRef list);
		void Append(ValueRef value);
		unsigned int Size();
		ValueRef At(unsigned int index);
		void SetAt(unsigned int index, ValueRef value);
		bool Remove(unsigned int index);
		void Set(const char *name, ValueRef value);
		ValueRef Get(const char *name);
		bool HasProperty(const char *name);
		SharedStringList GetPropertyNames();
		SharedString DisplayString(int levels=3);
		bool Equals(KObjectRef other);
	private:
		ListRef list;
	};
}

#endif
