/**
 * Appcelerator Kroll - licensed under the Apache Public License 2
 * see LICENSE in the root folder for details on the license.
 * Copyright (c) 2008 Appcelerator, Inc. All Rights Reserved.
 */

#ifndef _PYTHON_METHOD_H_
#define _PYTHON_METHOD_H_

#include "python_module.h"

namespace tide
{
	class KPythonObject;
	class KPythonMethod : public Method
	{
	public:
		KPythonMethod(PyObject *obj);
		virtual ~KPythonMethod();

		ValueRef Call(const ValueList& args);
		virtual void Set(const char *name, ValueRef value);
		virtual ValueRef Get(const char *name);
		virtual bool Equals(ObjectRef);
		virtual SharedStringList GetPropertyNames();
		PyObject* ToPython();

	private:
		PyObject* method;
		AutoPtr<KPythonObject> object;
		DISALLOW_EVIL_CONSTRUCTORS(KPythonMethod);
	};
}

#endif
