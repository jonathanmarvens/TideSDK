/*
 * Appcelerator Kroll - licensed under the Apache Public License 2
 * see LICENSE in the root folder for details on the license.
 * Copyright (c) 2009 Appcelerator, Inc. All Rights Reserved.
 */

#include "../tide.h"

namespace tide
{
	ProfiledGlobalObject::ProfiledGlobalObject(KObjectRef global) :
		profiledObject(new ProfiledBoundObject(global))
	{
	}

	ProfiledGlobalObject::~ProfiledGlobalObject()
	{
	}

	void ProfiledGlobalObject::Set(const char* name, ValueRef value)
	{
		profiledObject->Set(name, value);
	}

	ValueRef ProfiledGlobalObject::Get(const char* name)
	{
		return profiledObject->Get(name);
	}

	SharedStringList ProfiledGlobalObject::GetPropertyNames()
	{
		return profiledObject->GetPropertyNames();
	}

	SharedString ProfiledGlobalObject::DisplayString(int levels)
	{
		return profiledObject->DisplayString(levels);
	}

	bool ProfiledGlobalObject::HasProperty(const char* name)
	{
		return profiledObject->HasProperty(name);
	}

	bool ProfiledGlobalObject::Equals(KObjectRef other)
	{
		return profiledObject->Equals(other);
	}
}
