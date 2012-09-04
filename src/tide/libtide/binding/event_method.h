/*
 * Appcelerator Kroll - licensed under the Apache Public License 2
 * see LICENSE in the root folder for details on the license.
 * Copyright (c) 2009 Appcelerator, Inc. All Rights Reserved.
 */

#ifndef _EVENT_METHOD_H_
#define _EVENT_METHOD_H_


namespace tide
{
	class TIDE_API KEventMethod : public KEventObject, public Method
	{
		public:
		KEventMethod(const char* name = "") :
			KEventObject(name),
			count(1) {}

		// @see Method::Call
		virtual ValueRef Call(const ValueList& args) = 0;

		// @see Method::Set
		virtual void Set(const char *name, ValueRef value)
		{
			KEventObject::Set(name, value);
		}

		// @see Method::Get
		virtual ValueRef Get(const char *name)
		{
			return KEventObject::Get(name);
		}

		// @see Method::GetPropertyNames
		virtual SharedStringList GetPropertyNames()
		{
			return KEventObject::GetPropertyNames();
		}

		// @see Method::HasProperty
		virtual bool HasProperty(const char *name)
		{
			return KEventObject::HasProperty(name);
		}
		
		// @see Method::DisplayString
		SharedString DisplayString(int levels)
		{
			return KEventObject::DisplayString(levels);
		}

		/**
		 * Set a property on this object to the given method. When an error
		 * occurs will throw an exception of type ValueException.
		 */
		template <typename T>
		void SetMethod(const char *name, void (T::*method)(const ValueList&, ValueRef))
		{
			MethodCallback* callback = NewCallback<T, const ValueList&, ValueRef>(static_cast<T*>(this), method);

			MethodRef bound_method = new StaticBoundMethod(callback);
			ValueRef method_value = Value::NewMethod(bound_method);
			KEventObject::Set(name, method_value);
		}

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
		Poco::AtomicCounter count;

	};

}

#endif
