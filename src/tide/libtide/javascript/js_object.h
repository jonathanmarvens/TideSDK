/**
 * Appcelerator Kroll - licensed under the Apache Public License 2
 * see LICENSE in the root folder for details on the license.
 * Copyright (c) 2008 Appcelerator, Inc. All Rights Reserved.
 */

#ifndef _JS_OBJECT_H_
#define _JS_OBJECT_H_

#include "javascript_module.h"

#include <vector>
#include <string>
#include <map>

namespace tide
{
	class TIDE_API KKJSObject : public Object
	{
		public:
		KKJSObject(JSContextRef context, JSObjectRef js_object);
		~KKJSObject();

		virtual void Set(const char *name, ValueRef value);
		virtual ValueRef Get(const char *name);
		virtual SharedStringList GetPropertyNames();
		virtual bool HasProperty(const char* name);
		virtual bool Equals(ObjectRef);

		bool SameContextGroup(JSContextRef c);
		JSObjectRef GetJSObject();

		protected:
		JSGlobalContextRef context;
		JSObjectRef jsobject;

		private:
		DISALLOW_EVIL_CONSTRUCTORS(KKJSObject);
	};
}

#endif
