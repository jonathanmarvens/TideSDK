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
		static VALUE KObjectToRubyValue(ValueRef value);
		static VALUE KMethodToRubyValue(ValueRef value);
		static VALUE KListToRubyValue(ValueRef value);
		static bool KindOf(VALUE value, VALUE klass);

		static ValueException GetException();
		static VALUE GenericKMethodCall(KMethodRef method, VALUE args);

	private:
		static VALUE KObjectClass;
		static VALUE KMethodClass;
		static VALUE KListClass;
		RubyUtils(){}
		~RubyUtils(){}
	};
}

#endif
