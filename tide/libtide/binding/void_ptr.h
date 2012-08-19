/*
 * Appcelerator Kroll - licensed under the Apache Public License 2
 * see LICENSE in the root folder for details on the license.
 * Copyright (c) 2009 Appcelerator, Inc. All Rights Reserved.
 */

#ifndef _VOID_PTR_OBJECT_H_
#define _VOID_PTR_OBJECT_H_

#include "../tide.h"

namespace tide
{
	/**
	 * An object that represents an arbitrary amount of binary data§
	 */
	class TIDE_API VoidPtr : public StaticBoundObject
	{
	public:
		VoidPtr(void* pointer) :
			StaticBoundObject("VoidPtr"),
			pointer(pointer) {}
		void* GetPtr() { return pointer; }

	private:
		void* pointer;
	};
}

#endif
