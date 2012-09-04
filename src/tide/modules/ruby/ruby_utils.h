/**
 * Appcelerator Kroll - licensed under the Apache Public License 2
 * see LICENSE in the root folder for details on the license.
 * Copyright (c) 2008 Appcelerator, Inc. All Rights Reserved.
 */
#ifndef RUBY_TYPES_H_
#define RUBY_TYPES_H_

#include <typeinfo>
#include "ruby_module.h"

namespace tide
{
	class RubyUtils
	{
	public:
		static ValueRef ToTideValue(VALUE value);
		static VALUE ToRubyValue(ValueRef value);
		static VALUE ObjectToRubyValue(ValueRef value);
		static VALUE MethodToRubyValue(ValueRef value);
		static VALUE ListToRubyValue(ValueRef value);
		static bool KindOf(VALUE value, VALUE klass);

		static ValueException GetException();
		static VALUE GenericMethodCall(MethodRef method, VALUE args);

	private:
		static VALUE ObjectClass;
		static VALUE MethodClass;
		static VALUE ListClass;
		RubyUtils(){}
		~RubyUtils(){}
	};
}

#endif
