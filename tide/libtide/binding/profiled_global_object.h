/*
 * Appcelerator Kroll - licensed under the Apache Public License 2
 * see LICENSE in the root folder for details on the license.
 * Copyright (c) 2009 Appcelerator, Inc. All Rights Reserved.
 */

#ifndef _PROFILED_GLOBAL_OBJECT_H_
#define _PROFILED_GLOBAL_OBJECT_H_

namespace tide
{
	class TIDE_API ProfiledGlobalObject : public GlobalObject
	{
	public:
		ProfiledGlobalObject(ObjectRef delegate);
		virtual ~ProfiledGlobalObject();

		virtual void Set(const char *name, ValueRef value);
		virtual ValueRef Get(const char *name);
		virtual SharedStringList GetPropertyNames();
		virtual SharedString DisplayString(int levels=3);
		virtual bool Equals(ObjectRef other);
		bool HasProperty(const char* name);

	protected:
		AutoPtr<ProfiledBoundObject> profiledObject;
	};
}

#endif
