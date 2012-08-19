/*
 * Appcelerator Kroll - licensed under the Apache Public License 2
 * see LICENSE in the root folder for details on the license.
 * Copyright (c) 2008 Appcelerator, Inc. All Rights Reserved.
 */
/**
 * This file is the easiest way to gain access to the full TIDE API
 * To use it, just do the following:
 * \code
 * #include <tide/tide.h>
 * \endcode
 */

#ifndef _TIDE_H_
#define _TIDE_H_

#include "base.h"
#include <Poco/SharedPtr.h>
#include <Poco/AutoPtr.h>
#include <vector>

using Poco::SharedPtr;
using Poco::AutoPtr;

#ifndef OS_WIN32
	// this is important which essentially marks all of
	// these classes below and the typedef/templates to be
	// visible outside of the library.  if you don't do this
	// you won't be able to catch exceptions of ValueRef for
	// example
	#pragma GCC visibility push(default)
#endif

namespace tide
{
	class Value;
	class Object;
	class Method;
	class List;

	class StaticBoundObject;
	class StaticBoundMethod;
	class StaticBoundList;

	class GlobalObject;
	class ScopeMethodDelegate;
	class Bytes;
	class VoidPtr;
	class ValueReleasePolicy;
	class Logger;
	class ArgList;

	typedef AutoPtr<Value> ValueRef;
	typedef AutoPtr<Object> KObjectRef;
	typedef AutoPtr<Method> MethodRef;
	typedef AutoPtr<List> ListRef;
	typedef AutoPtr<Bytes> BytesRef;

	typedef SharedPtr<std::string> SharedString;
	typedef std::vector<SharedString> StringList;
	typedef SharedPtr<StringList> SharedStringList;

	typedef ArgList ValueList;

	class Module;
	class Application;
	class KComponent;
	class Dependency;

	typedef SharedPtr<KComponent> SharedComponent;
	typedef SharedPtr<Application> SharedApplication;
	typedef SharedPtr<Dependency> SharedDependency;
}

#ifndef OS_WIN32
	#pragma GCC visibility pop
#endif

#include "utils/utils.h"
#include "net/net.h"
#include "reference_counted.h"
#include "logger.h"

#include "binding/binding.h"
#include "module_provider.h"
#include "module.h"
#include "async_job.h"
#include "main_thread_job.h"
#include "ScriptController.h"

#ifdef OS_OSX
#include "osx/osx.h"
#elif defined(OS_WIN32)
#include "win32/win32.h"
#endif

#include "host.h"

#endif
