/*
 * Appcelerator Kroll - licensed under the Apache Public License 2
 * see LICENSE in the root folder for details on the license.
 * Copyright (c) 2009 Appcelerator, Inc. All Rights Reserved.
 */

#include "../tide.h"
namespace tide
{
	ReadEvent::ReadEvent(AutoPtr<KEventObject> target, BytesRef data) :
		Event(target, Event::READ),
		data(data)
	{
		this->SetMethod("getData", &ReadEvent::_GetData);
	}

	void ReadEvent::_GetData(const ValueList&, ValueRef result)
	{
		result->SetObject(this->data);
	}
}

