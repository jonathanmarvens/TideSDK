/**
 * Appcelerator Kroll - licensed under the Apache Public License 2
 * see LICENSE in the root folder for details on the license.
 * Copyright (c) 2008 Appcelerator, Inc. All Rights Reserved.
 */
#include "javascript_module.h"

namespace tide
{
	KKJSList::KKJSList(JSContextRef context, JSObjectRef jsobject) :
		List("JavaScript.KKJSList"),
		context(NULL),
		jsobject(jsobject)
	{
		/* KJS methods run in the global context that they originated from
		 * this seems to prevent nasty crashes from trying to access invalid
		 * contexts later. Global contexts need to be registered by all modules
		 * that use a KJS context. */
		JSObjectRef globalObject = JSContextGetGlobalObject(context);
		JSGlobalContextRef globalContext = JSUtil::GetGlobalContext(globalObject);

		// This context hasn't been registered. Something has gone pretty
		// terribly wrong and Tide will likely crash soon. Nonetheless, keep
		// the user up-to-date to keep their hopes up.
		if (globalContext == NULL)
			std::cerr << "Could not locate global context for a KJS method."  <<
				" One of the modules is misbehaving." << std::endl;
		this->context = globalContext;

		JSUtil::ProtectGlobalContext(this->context);
		JSValueProtect(this->context, this->jsobject);

		this->object = new KKJSObject(this->context, this->jsobject);
	}

	KKJSList::~KKJSList()
	{
		JSValueUnprotect(this->context, this->jsobject);
		JSUtil::UnprotectGlobalContext(this->context);
	}

	unsigned int KKJSList::Size()
	{
		ValueRef length_val = this->object->Get("length");
		if (length_val->IsInt())
			return (unsigned int) length_val->ToInt();
		else
			return 0;
	}

	ValueRef KKJSList::At(unsigned int index)
	{
		std::string name = List::IntToChars(index);
		ValueRef value = this->object->Get(name.c_str());
		return value;
	}

	void KKJSList::SetAt(unsigned int index, ValueRef value)
	{
		std::string name = List::IntToChars(index);
		this->object->Set(name.c_str(), value);
	}

	void KKJSList::Append(ValueRef value)
	{
		ValueRef push_method = this->object->Get("push");

		if (push_method->IsMethod())
		{
			ValueList list;
			list.push_back(value);
			push_method->ToMethod()->Call(list);
		}
		else
		{
			throw ValueException::FromString("Could not find push method on KJS array.");
		}
	}

	bool KKJSList::Remove(unsigned int index)
	{
		if (index >= 0 && index < this->Size())
		{
			ValueRef spliceMethod = this->object->Get("splice");
			spliceMethod->ToMethod()->Call(
				Value::NewInt(index),
				Value::NewInt(1));
			return true;
		}
		return false;
	}


	ValueRef KKJSList::Get(const char* name)
	{
		return object->Get(name);
	}

	void KKJSList::Set(const char* name, ValueRef value)
	{
		return object->Set(name, value);
	}

	bool KKJSList::Equals(ObjectRef other)
	{
		return this->object->Equals(other);
	}

	SharedStringList KKJSList::GetPropertyNames()
	{
		 return object->GetPropertyNames();
	}

	bool KKJSList::HasProperty(const char* name)
	{
		return object->HasProperty(name);
	}

	bool KKJSList::SameContextGroup(JSContextRef c)
	{
		return object->SameContextGroup(c);
	}

	JSObjectRef KKJSList::GetJSObject()
	{
		return this->jsobject;
	}
}
