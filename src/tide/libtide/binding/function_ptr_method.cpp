/*
 * Appcelerator Kroll - licensed under the Apache Public License 2
 * see LICENSE in the root folder for details on the license.
 * Copyright (c) 2008 Appcelerator, Inc. All Rights Reserved.
 */

#include "../tide.h"

namespace tide
{
	KFunctionPtrMethod::KFunctionPtrMethod(KFunctionPtrCallback callback) :
		callback(callback)
	{
		this->object = new StaticBoundObject();
	}

	KFunctionPtrMethod::~KFunctionPtrMethod()
	{
	}

	ValueRef KFunctionPtrMethod::Call(const ValueList& args)
	{
		return this->callback(args);
	}

	void KFunctionPtrMethod::Set(const char *name, ValueRef value)
	{
		this->object->Set(name, value);
	}

	ValueRef KFunctionPtrMethod::Get(const char *name)
	{
		return this->object->Get(name);
	}

	SharedStringList KFunctionPtrMethod::GetPropertyNames()
	{
		return this->object->GetPropertyNames();
	}
}

