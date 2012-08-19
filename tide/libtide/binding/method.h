/*
 * Appcelerator Kroll - licensed under the Apache Public License 2
 * see LICENSE in the root folder for details on the license.
 * Copyright (c) 2008 Appcelerator, Inc. All Rights Reserved.
 */

#ifndef _METHOD_H_
#define _METHOD_H_
#include <cstdarg>

namespace tide
{
	typedef Callback2<const ValueList&, ValueRef>::Type MethodCallback;

	/**
	 * An abstract representation of a method
	 */
	class TIDE_API Method : public Object
	{

	public:

		Method(const char *type = "Method") : Object(type) {}
		virtual ~Method() {}

		/**
		 * Call this method with the given arguments.
		 * Errors will result in a thrown ValueException
		 * @return the return value of this method
		 */
		virtual ValueRef Call(const ValueList& args) = 0;

		/**
		 * Call this method with the given 'this' object and arguments.
		 * Errors will result in a thrown ValueException
		 * @return the return value of this method
		 */
		virtual ValueRef Call(KObjectRef thisObject, const ValueList& args);

		/**
		 * Set a property on this object to the given value
		 * Errors will result in a thrown ValueException
		 */
		virtual void Set(const char* name, ValueRef value) = 0;

		/**
		 * @return the property with the given name or Value::Undefined
		 * if the property is not found.
		 * Errors will result in a thrown ValueException
		 */
		virtual ValueRef Get(const char* name) = 0;

		/**
		 * @return a list of this object's property names.
		 */
		virtual SharedStringList GetPropertyNames() = 0;

		/**
		 * @return a string representation of this object
		 */
		SharedString DisplayString(int levels);

		/**
		 * Return the unwrapped version of this object
		 */
		static MethodRef Unwrap(MethodRef);

		/* Convenience methods below */
		ValueRef Call(ValueRef one);
		ValueRef Call(ValueRef one, ValueRef two);
		ValueRef Call(ValueRef one, ValueRef two, ValueRef three);
		ValueRef Call();
		ValueRef Call(const char* one);
		ValueRef Call(const char* one, ValueRef two);
		ValueRef Call(const char* one, ValueRef two, ValueRef three);
		ValueRef Call(const char* one, ValueRef two, ValueRef three,
			ValueRef four);

	private:
		DISALLOW_EVIL_CONSTRUCTORS(Method);
	};
}

#endif

