/*
 * Appcelerator Kroll - licensed under the Apache Public License 2
 * see LICENSE in the root folder for details on the license.
 * Copyright (c) 2009 Appcelerator, Inc. All Rights Reserved.
 */

#ifndef _PROFILED_BOUND_LIST_H_
#define _PROFILED_BOUND_LIST_H_

namespace tide
{
	/**
	 * The ProfiledBoundList is a wrapped List that does profiling
	 */
	class ProfiledBoundList : public ProfiledBoundObject, public List
	{
	public:
		ProfiledBoundList(ListRef delegate);
		virtual ~ProfiledBoundList();

		// @see List::Append
		virtual void Append(ValueRef value);
		// @see List::Size
		virtual unsigned int Size();
		// @see List::At
		virtual ValueRef At(unsigned int index);
		// @see List::SetAt
		virtual void SetAt(unsigned int index, ValueRef value);
		// @see List::Remove
		virtual bool Remove(unsigned int index);
		// @See List::Set
		virtual void Set(const char *name, ValueRef value);
		// @see List::Get
		virtual ValueRef Get(const char *name);
		// @see List::GetPropertyNames
		virtual SharedStringList GetPropertyNames();

		bool HasProperty(const char* name);

		/**
		 * @return the delegate of this profiled bound object
		 */
		ListRef GetDelegate() { return list; }
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
		ListRef list;
		Poco::AtomicCounter count;

	};
}

#endif
