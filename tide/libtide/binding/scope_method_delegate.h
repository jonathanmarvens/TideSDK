/*
 * Appcelerator Kroll - licensed under the Apache Public License 2
 * see LICENSE in the root folder for details on the license.
 * Copyright (c) 2008 Appcelerator, Inc. All Rights Reserved.
 */

#ifndef _SCOPE_METHOD_DELEGATE_H_
#define _SCOPE_METHOD_DELEGATE_H_

namespace tide {

	enum MethodDelegateType
	{
		GET, /**< Getter method */
		SET /**< Setter method */
	};

	/**
	 * class that can be used to change the delegation of a method
	 * call's Get or Set method to first check to see if the key has
	 * namespace dots (such as ti.foo.bar) and if so, delegate to a
	 * differently supplied scope object for delegation.
	 */
	class TIDE_API ScopeMethodDelegate : public Method
	{
	public:

		ScopeMethodDelegate(MethodDelegateType type, ObjectRef global,
		                    ObjectRef scope, MethodRef delegate);
		virtual ~ScopeMethodDelegate();


		void Set(const char *name, ValueRef value);
		ValueRef Get(const char *name);
		SharedStringList GetPropertyNames();


		bool IsGlobalKey(std::string& key);
		ValueRef Call(const ValueList& args);

		/**
		 * create a delegate from a Object to a wrapped
		 * StaticBoundObject and delegate set/get to the new
		 * static bound object
		 */
		static AutoPtr<StaticBoundObject> CreateDelegate(ObjectRef global, ObjectRef bo);


	private:
		MethodDelegateType type;
		ObjectRef global;
		ObjectRef scope;
		MethodRef delegate;


	private:
		DISALLOW_EVIL_CONSTRUCTORS(ScopeMethodDelegate);
	};

}

#endif
