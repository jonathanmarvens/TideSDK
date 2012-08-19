/**
 * Appcelerator Kroll - licensed under the Apache Public License 2
 * see LICENSE in the root folder for details on the license.
 * Copyright (c) 2008 Appcelerator, Inc. All Rights Reserved.
 */
#ifndef PYTHON_TYPES_H_
#define PYTHON_TYPES_H_

#include <typeinfo>
#include "python_module.h"

namespace tide
{
	class PythonUtils
	{
	public:
		static void InitializePythonKClasses();
		static ValueRef ToTideValue(PyObject* value);
		static PyObject* ToPyObject(ValueRef value);
		static PyObject* ToPyObject(const ValueList& list);
		static const char* ToString(PyObject* value);
		static PyObject* KObjectToPyObject(ValueRef o);
		static PyObject* KMethodToPyObject(ValueRef o);
		static PyObject* KListToPyObject(ValueRef o);
		static std::string PythonErrorToString();

	private:
		PythonUtils() {}
		~PythonUtils () {}
	};
}

#endif
