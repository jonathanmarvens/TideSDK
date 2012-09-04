/*
 * Appcelerator Kroll - licensed under the Apache Public License 2
 * see LICENSE in the root folder for details on the license.
 * Copyright (c) 2009 Appcelerator, Inc. All Rights Reserved.
 */

#ifndef _PROFILED_BOUND_METHOD_H_
#define _PROFILED_BOUND_METHOD_H_

namespace tide
{
	/**
	 * The ProfiledBoundMethod is a wrapped Method that does profiling
	 */
	class ProfiledBoundMethod : public ProfiledBoundObject, public Method
	{
	public:
		ProfiledBoundMethod(MethodRef delegate, std::string& parentType);
		virtual ~ProfiledBoundMethod();

		// @see Method::Call
		virtual ValueRef Call(const ValueList& args);
		// @see Method::Set
		virtual void Set(const char *name, ValueRef value);
		// @see Method::Get
		virtual ValueRef Get(const char *name);
		// @see Method::GetPropertyNames
		virtual SharedStringList GetPropertyNames();
		// @see Object::GetType
		virtual std::string& GetType();

		bool HasProperty(const char* name);

		/**
		 * @return the delegate of this profiled bound method
		 */
		MethodRef GetDelegate() { return method; }
		virtual void duplicate()
		{
			++count;
		}

		virtual void release()
		{
			int value = --count;
			if (value <= 0) {
				delete this;
			}
		}

		virtual int referenceCount() const
		{
			return count.value();
		}

	private:
		MethodRef method;
		std::string fullType;
		Poco::AtomicCounter count;

	};
}

#endif
