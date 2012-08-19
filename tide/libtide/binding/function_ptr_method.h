/*
 * Appcelerator Kroll - licensed under the Apache Public License 2
 * see LICENSE in the root folder for details on the license.
 * Copyright (c) 2008 Appcelerator, Inc. All Rights Reserved.
 */

#ifndef _FUNCTION_PTR_METHOD_H_
#define _FUNCTION_PTR_METHOD_H_

namespace tide
{

	typedef ValueRef (*KFunctionPtrCallback) (const ValueList& args);
	class TIDE_API KFunctionPtrMethod : public Method
	{
		public:
		KFunctionPtrMethod(KFunctionPtrCallback);
		virtual ~KFunctionPtrMethod();

		/**
		 * @see Method::Call
		 */
		virtual ValueRef Call(const ValueList& args);

		/**
		 * @see Object::Set
		 */
		virtual void Set(const char *name, ValueRef value);

		/**
		 * @see Object::Get
		 */
		virtual ValueRef Get(const char *name);

		/**
		 * @see Object::GetPropertyNames
		 */
		virtual SharedStringList GetPropertyNames();
		

		protected:
		KFunctionPtrCallback callback;
		KObjectRef object;

		private:
		DISALLOW_EVIL_CONSTRUCTORS(KFunctionPtrMethod);
	};
}

#endif
