/**
 * Appcelerator Kroll - licensed under the Apache Public License 2
 * see LICENSE in the root folder for details on the license.
 * Copyright (c) 2009 Appcelerator, Inc. All Rights Reserved.
 */

#ifndef _PYTHON_TUPLE_H_
#define _PYTHON_TUPLE_H_

#include "python_module.h"

namespace tide
{
	class KPythonTuple : public KList
	{
	public:
		KPythonTuple(PyObject *obj);
		virtual ~KPythonTuple();

		ValueRef Get(const char *name);
		void Set(const char *name, ValueRef value);
		virtual bool Equals(KObjectRef);
		SharedStringList GetPropertyNames();

		unsigned int Size();
		void Append(ValueRef value);
		virtual void SetAt(unsigned int index, ValueRef value);
		bool Remove(unsigned int index);
		ValueRef At(unsigned int index);

		PyObject* ToPython();

	protected:
		PyObject *tuple;
		AutoPtr<KPythonObject> object;
		DISALLOW_EVIL_CONSTRUCTORS(KPythonTuple);
	};
}
#endif

