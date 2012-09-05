/*
 * Appcelerator Kroll - licensed under the Apache Public License 2
 * see LICENSE in the root folder for details on the license.
 * Copyright (c) 2008, 2009 Appcelerator, Inc. All Rights Reserved.
 */

#ifndef _ACCESSOR_BOUND_LIST_H_
#define _ACCESSOR_BOUND_LIST_H_

namespace tide
{
	/**
	 * The KAccessorList allows you to expose getters and setters as property access.
	 * @see KAccessorObject
	 */
	class TIDE_API KAccessorList : public StaticBoundList, public KAccessor
	{
	public:
		KAccessorList(const char* type = "KAccessorList");
		virtual void Set(const char* name, ValueRef value);
		virtual ValueRef Get(const char* name);
		virtual bool HasProperty(const char* name);

	private:
		DISALLOW_EVIL_CONSTRUCTORS(KAccessorList);
	};
}

#endif
