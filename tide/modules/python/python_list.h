/**
 * Appcelerator Kroll - licensed under the Apache Public License 2
 * see LICENSE in the root folder for details on the license.
 * Copyright (c) 2008 Appcelerator, Inc. All Rights Reserved.
 */

#ifndef _PYTHON_LIST_H_
#define _PYTHON_LIST_H_

#include "python_module.h"

namespace tide
{
	class KPythonList : public List
	{
	public:
		KPythonList(PyObject *obj);
		virtual ~KPythonList();

		ValueRef Get(const char* name);
		void Set(const char* name, ValueRef value);
		virtual bool Equals(KObjectRef);
		SharedStringList GetPropertyNames();

		unsigned int Size();
		void Append(ValueRef value);
		virtual void SetAt(unsigned int index, ValueRef value);
		bool Remove(unsigned int index);
		ValueRef At(unsigned int index);

		PyObject* ToPython();

	protected:
		PyObject *list;
		AutoPtr<KPythonObject> object;
		DISALLOW_EVIL_CONSTRUCTORS(KPythonList);
	};
}
#endif

