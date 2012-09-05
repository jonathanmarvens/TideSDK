/**
 * Appcelerator Kroll - licensed under the Apache Public License 2
 * see LICENSE in the root folder for details on the license.
 * Copyright (c) 2009 Appcelerator, Inc. All Rights Reserved.
 */
#ifndef _PHP_METHOD_H_
#define _PHP_METHOD_H_

namespace tide
{
	class KPHPMethod : public Method
	{
		public:
		KPHPMethod(zval* object, const char* methodName);
		KPHPMethod(const char *functionName);

		virtual ~KPHPMethod();
		ValueRef Call(const ValueList& args);
		virtual void Set(const char *name, ValueRef value);
		virtual ValueRef Get(const char *name);
		virtual SharedStringList GetPropertyNames();
		virtual SharedString DisplayString(int);
		virtual bool Equals(ObjectRef);
		bool PropertyExists(const char* property);
		zval* ToPHP();

		private:
		zval* object;
		char* methodName;
		zval* zMethodName;
		ObjectRef globalObject;
	};
}
#endif
