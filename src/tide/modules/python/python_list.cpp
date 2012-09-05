/**
 * Appcelerator Kroll - licensed under the Apache Public License 2
 * see LICENSE in the root folder for details on the license.
 * Copyright (c) 2008 Appcelerator, Inc. All Rights Reserved.
 */
#include "python_list.h"

namespace tide
{
	KPythonList::KPythonList(PyObject *list) :
		List("Python.KPythonList"),
		list(list),
		object(new KPythonObject(list, true))
	{
		PyLockGIL lock;
		Py_INCREF(this->list);
	}

	KPythonList::~KPythonList()
	{
		PyLockGIL lock;
		Py_DECREF(this->list);
	}

	void KPythonList::Append(ValueRef value)
	{
		PyLockGIL lock;
		PyObject* py_value = PythonUtils::ToPyObject(value);
		PyList_Append(this->list, py_value);
	}

	unsigned int KPythonList::Size()
	{
		PyLockGIL lock;
		return PyList_Size(this->list);
	}

	bool KPythonList::Remove(unsigned int index)
	{
		PyLockGIL lock;
		if (index < this->Size())
		{
			PyObject* emptyList = PyList_New(0);
			PyList_SetSlice(this->list, index, index + 1, emptyList);
			Py_DECREF(emptyList);
			return true;
		}
		else
		{
			return false;
		}
	}

	ValueRef KPythonList::At(unsigned int index)
	{
		PyLockGIL lock;
		if (index >= 0 && index < this->Size())
		{
			PyObject *p = PyList_GetItem(this->list, index);
			ValueRef v = PythonUtils::ToTideValue(p);
			return v;
		}
		else
		{
			return Value::Undefined;
		}
	}

	void KPythonList::Set(const char* name, ValueRef value)
	{
		if (List::IsInt(name))
		{
			this->SetAt(List::ToIndex(name), value);
		}
		else
		{
			this->object->Set(name, value);
		}
	}

	void KPythonList::SetAt(unsigned int index, ValueRef value)
	{
		PyLockGIL lock;
		while (index >= this->Size())
		{
			// Now we need to create entries between current size
			// and new size and make the entries undefined.
			Py_INCREF(Py_None);
			PyList_Append(this->list, Py_None);
		}
		PyObject* py_value = PythonUtils::ToPyObject(value);
		PyList_SetItem(this->list, index, py_value);
		return;
	}

	ValueRef KPythonList::Get(const char* name)
	{
		if (List::IsInt(name))
		{
			return this->At(List::ToIndex(name));
		}
		else
		{
			return object->Get(name);
		}
	}

	SharedStringList KPythonList::GetPropertyNames()
	{
		SharedStringList property_names = object->GetPropertyNames();
		for (size_t i = 0; i < this->Size(); i++)
		{
			std::string name = List::IntToChars(i);
			property_names->push_back(new std::string(name));
		}

		return property_names;
	}

	PyObject* KPythonList::ToPython()
	{
		return this->object->ToPython();
	}

	bool KPythonList::Equals(ObjectRef other)
	{
		AutoPtr<KPythonList> pyOther = other.cast<KPythonList>();

		// This is not a Python object
		if (pyOther.isNull())
			return false;

		return pyOther->ToPython() == this->ToPython();
	}
}
