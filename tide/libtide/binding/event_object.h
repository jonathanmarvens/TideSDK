/*
 * Appcelerator Kroll - licensed under the Apache Public License 2
 * see LICENSE in the root folder for details on the license.
 * Copyright (c) 2009-2010 Appcelerator, Inc. All Rights Reserved.
 */

#ifndef _EVENT_OBJECT_H_
#define _EVENT_OBJECT_H_

#include <list>
#include <Poco/Mutex.h>

namespace tide
{
	class EventListener;
	typedef std::list<EventListener*> EventListenerList;

	class TIDE_API KEventObject : public KAccessorObject
	{
	public:
		KEventObject(const char* name = "KEventObject");
		virtual ~KEventObject();

		AutoPtr<Event> CreateEvent(const std::string& eventName);

		virtual void AddEventListener(const char* event, MethodRef listener);
		virtual void AddEventListener(std::string& event, MethodRef listener);
		virtual void RemoveEventListener(std::string& event, MethodRef listener);
		virtual void RemoveAllEventListeners();

		void FireEvent(const char* event);
		virtual void FireEvent(const char* event, const ValueList& args);
		virtual bool FireEvent(std::string& event, bool synchronous=true);
		virtual bool FireEvent(AutoPtr<Event>, bool synchronous=true);
		void FireErrorEvent(std::exception& e);

		void _AddEventListener(const ValueList&, ValueRef result);
		void _RemoveEventListener(const ValueList&, ValueRef result);
		void _RemoveAllEventListeners(const ValueList&, ValueRef result);

	private:
		void ReportDispatchError(std::string& reason);

		EventListenerList listeners;
		Poco::FastMutex listenersMutex;
	};

	class EventListener
	{
	public:
		EventListener(std::string& targetedEvent, MethodRef callback);
		EventListener(const char* targetedEvent, MethodRef callback);

		bool Handles(const char* event);
		bool Dispatch(ObjectRef thisObject, const ValueList& args, bool synchronous);
		MethodRef Callback();

	private:
		std::string targetedEvent;
		MethodRef callback;
	};
}

#endif
