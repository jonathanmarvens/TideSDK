/*
 * Appcelerator Kroll - licensed under the Apache Public License 2
 * see LICENSE in the root folder for details on the license.
 * Copyright (c) 2008 Appcelerator, Inc. All Rights Reserved.
 */

#include "../tide.h"
#include <sstream>
#include <cmath>

namespace tide
{

	SharedString KMethod::DisplayString(int levels)
	{
		std::ostringstream oss;
		oss << "<" << this->GetType() << " at " << this << ">";
		return new std::string(oss.str());
	}

	ValueRef KMethod::Call(KObjectRef thisObject, const ValueList& args)
	{
		return this->Call(args);
	}

	ValueRef KMethod::Call()
	{
		return this->Call(ValueList());
	}

	ValueRef KMethod::Call(const char* one, ValueRef two, ValueRef three,
		ValueRef four)
	{
		ValueList args;
		args.push_back(Value::NewString(one));
		args.push_back(two);
		args.push_back(three);
		args.push_back(four);
		return this->Call(args);
	}

	ValueRef KMethod::Call(ValueRef one)
	{
		ValueList args;
		args.push_back(one);
		return this->Call(args);
	}

	ValueRef KMethod::Call(ValueRef one, ValueRef two)
	{
		ValueList args;
		args.push_back(one);
		args.push_back(two);
		return this->Call(args);
	}

	ValueRef KMethod::Call(ValueRef one, ValueRef two, ValueRef three)
	{
		ValueList args;
		args.push_back(one);
		args.push_back(two);
		args.push_back(three);
		return this->Call(args);
	}

	ValueRef KMethod::Call(const char* one)
	{
		ValueList args;
		args.push_back(Value::NewString(one));
		return this->Call(args);
	}

	ValueRef KMethod::Call(const char* one, ValueRef two)
	{
		ValueList args;
		args.push_back(Value::NewString(one));
		args.push_back(two);
		return this->Call(args);
	}

	ValueRef KMethod::Call(const char* one, ValueRef two, ValueRef three)
	{
		ValueList args;
		args.push_back(Value::NewString(one));
		args.push_back(two);
		args.push_back(three);
		return this->Call(args);
	}

	KMethodRef KMethod::Unwrap(KMethodRef o)
	{
		AutoPtr<ProfiledBoundMethod> pmeth = o.cast<ProfiledBoundMethod>();
		if (pmeth.isNull())
		{
			return o;
		}
		else
		{
			return pmeth->GetDelegate();
		}
	}
}

