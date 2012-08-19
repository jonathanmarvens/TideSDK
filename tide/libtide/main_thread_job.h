/**
 * Appcelerator Kroll - licensed under the Apache Public License 2
 * see LICENSE in the root folder for details on the license.
 * Copyright (c) 2008, 2009 Appcelerator, Inc. All Rights Reserved.
 */
#ifndef _MAIN_THREAD_JOB_H
#define _MAIN_THREAD_JOB_H

#include <Poco/Semaphore.h>

namespace tide
{
	class TIDE_API MainThreadJob
	{
	public:
		MainThreadJob(MethodRef method, KObjectRef thisObject,
			const ValueList& args, bool waitForCompletion);
		void Lock();
		void Wait();
		void Execute();
		ValueRef GetResult();
		ValueException GetException();
		bool ShouldWaitForCompletion();
		void PrintException();

	private:
		MethodRef method;
		KObjectRef thisObject;
		const ValueList args;
		bool waitForCompletion;
		ValueRef returnValue;
		ValueException exception;
		Poco::Semaphore semaphore;
	};
}

#endif
