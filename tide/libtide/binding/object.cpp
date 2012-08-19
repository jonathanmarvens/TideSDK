/*
 * Appcelerator Kroll - licensed under the Apache Public License 2
 * see LICENSE in the root folder for details on the license.
 * Copyright (c) 2008 Appcelerator, Inc. All Rights Reserved.
 */

#include "../tide.h"
#include <sstream>

namespace tide
{

	bool Object::Equals(ObjectRef other)
	{
		return other.get() == this;
	}

	bool Object::HasProperty(const char* name)
	{
		SharedStringList names = this->GetPropertyNames();
		for (size_t i = 0; i < names->size(); i++)
		{
			if (!strcmp(name, names->at(i)->c_str()))
				return true;
		}
		return false;
	}

	SharedString Object::DisplayString(int levels)
	{
		std::stringstream ss;

		SharedStringList props = this->GetPropertyNames();
		ss << "(" << this->GetType() << ")" << " {";
		for (size_t i = 0; i < props->size(); i++)
		{
			ValueRef prop = this->Get(props->at(i));
			SharedString disp_string = prop->DisplayString(levels);

			ss << " " << *(props->at(i))
			    << " : " << *disp_string << ",";
		}

		if (props->size() > 0) // Erase last comma
			ss.seekp((int)ss.tellp() - 1);

		ss << "}";

		return new std::string(ss.str());
	}

	void Object::Set(SharedString name, ValueRef value)
	{
		this->Set(name->c_str(), value);
	}

	ValueRef Object::Get(SharedString name)
	{
		return this->Get(name->c_str());
	}

	int Object::GetInt(const char* name, int defaultValue)
	{
		ValueRef prop = this->Get(name);
		if (prop->IsInt())
		{
			return prop->ToInt();
		}
		else
		{
			return defaultValue;
		}
	}

	double Object::GetDouble(const char* name, double defaultValue)
	{
		ValueRef prop = this->Get(name);
		if (prop->IsDouble())
		{
			return prop->ToDouble();
		}
		else
		{
			return defaultValue;
		}
	}

	double Object::GetNumber(const char* name, double defaultValue)
	{
		ValueRef prop = this->Get(name);
		if (prop->IsNumber())
		{
			return prop->ToNumber();
		}
		else
		{
			return defaultValue;
		}
	}

	bool Object::GetBool(const char* name, bool defaultValue)
	{
		ValueRef prop = this->Get(name);
		if (prop->IsBool())
		{
			return prop->ToBool();
		}
		else
		{
			return defaultValue;
		}
	}

	std::string Object::GetString(const char* name, std::string defaultValue)
	{
		ValueRef prop = this->Get(name);
		if(prop->IsString())
		{
			return prop->ToString();
		}
		else
		{
			return defaultValue;
		}
	}

	ObjectRef Object::GetObject(const char* name, ObjectRef defaultValue)
	{
		ValueRef prop = this->Get(name);
		if (prop->IsObject())
		{
			return prop->ToObject();
		}
		else
		{
			return defaultValue;
		}
	}

	MethodRef Object::GetMethod(const char* name, MethodRef defaultValue)
	{
		ValueRef prop = this->Get(name);
		if (prop->IsMethod())
		{
			return prop->ToMethod();
		}
		else
		{
			return defaultValue;
		}
	}

	ListRef Object::GetList(const char* name, ListRef defaultValue)
	{
		ValueRef prop = this->Get(name);
		if (prop->IsList())
		{
			return prop->ToList();
		}
		else
		{
			return defaultValue;
		}
	}

	void Object::SetUndefined(const char *name)
	{
		this->Set(name, Value::Undefined);
	}

	void Object::SetNull(const char *name)
	{
		this->Set(name, Value::Null);
	}

	void Object::SetInt(const char *name, int v)
	{
		ValueRef val = Value::NewInt(v);
		this->Set(name, val);
	}

	void Object::SetDouble(const char *name, double v)
	{
		ValueRef val = Value::NewDouble(v);
		this->Set(name, val);
	}

	void Object::SetNumber(const char *name, double v)
	{
		ValueRef val = Value::NewDouble(v);
		this->Set(name, val);
	}

	void Object::SetBool(const char *name, bool v)
	{
		ValueRef val = Value::NewBool(v);
		this->Set(name, val);
	}

	void Object::SetString(const char *name, std::string v)
	{
		ValueRef val = Value::NewString(v);
		this->Set(name, val);
	}

	void Object::SetObject(const char *name, ObjectRef object)
	{
		ValueRef obj_val = Value::NewObject(object);
		this->Set(name, obj_val);
	}

	void Object::SetMethod(const char *name, MethodRef object)
	{
		ValueRef obj_val = Value::NewMethod(object);
		this->Set(name, obj_val);
	}

	void Object::SetList(const char *name, ListRef object)
	{
		ValueRef obj_val = Value::NewList(object);
		this->Set(name, obj_val);
	}

	void Object::GetStringList(const char *name, std::vector<std::string> &list)
	{
		ValueRef prop = this->Get(name);
		if(!prop->IsUndefined() && prop->IsList())
		{
			ListRef values = prop->ToList();
			if (values->Size() > 0)
			{
				for (unsigned int c = 0; c < values->Size(); c++)
				{
					ValueRef v = values->At(c);
					if (v->IsString())
					{
						const char *s = v->ToString();
						list.push_back(s);
					}
				}
			}
		}
	}

	void Object::SetNS(const char *name, ValueRef value)
	{
		std::vector<std::string> tokens;
		FileUtils::Tokenize(std::string(name), tokens, ".");

		Object *scope = this;
		for (size_t i = 0; i < tokens.size() - 1; i++)
		{
			const char* token = tokens[i].c_str();
			StaticBoundObject *next;
			ValueRef next_val = scope->Get(token);

			if (next_val->IsUndefined())
			{
				next = new StaticBoundObject();
				ObjectRef so = next;
				next_val = Value::NewObject(so);
				scope->Set(token, next_val);
				scope = next;
			}
			else if (!next_val->IsObject()
			         && !next_val->IsMethod()
			         && !next_val->IsList())
			{
				std::cerr << "invalid namespace for " << name << ", token: " << token << " was " << next_val->GetType() << std::endl;
				throw Value::NewString("Invalid namespace on setNS");
			}
			else
			{
				scope = next_val->ToObject().get();
			}
		}

		const char *prop_name = tokens[tokens.size()-1].c_str();
		scope->Set(prop_name, value);

#ifdef DEBUG_BINDING
		std::cout << "BOUND: " << value->GetType() << " to: " << name << std::endl;
#endif
	}

	ValueRef Object::GetNS(const char *name)
	{
		std::string s(name);
		std::string::size_type last = 0;
		std::string::size_type pos = s.find_first_of(".");
		ValueRef current;
		Object* scope = this;
		while (pos != std::string::npos)
		{
			std::string token = s.substr(last,pos-last);
			current = scope->Get(token.c_str());
			if (current->IsObject())
			{
				scope = current->ToObject().get();
			}
			else
			{
				return Value::Undefined;
			}
			last = pos + 1;
		    pos = s.find_first_of(".", last);
		}
		if (pos!=s.length())
		{
			std::string token = s.substr(last);
			current = scope->Get(token.c_str());
		}

		return current;
	}

	ValueRef Object::CallNS(const char *name)
	{
		ValueList args;
		return CallNS(name, args);
	}
	
	ValueRef Object::CallNS(const char *name, ValueRef val1)
	{
		ValueList args;
		args.push_back(val1);
		return CallNS(name, args);
	}

	ValueRef Object::CallNS(const char *name, ValueRef val1, ValueRef val2)
	{
		ValueList args;
		args.push_back(val1);
		args.push_back(val2);
		return CallNS(name, args);
	}

	ValueRef Object::CallNS(const char *name, ValueRef val1, ValueRef val2, ValueRef val3)
	{
		ValueList args;
		args.push_back(val1);
		args.push_back(val2);
		args.push_back(val3);
		return CallNS(name, args);
	}

	ValueRef Object::CallNS(const char *name, const ValueList& args)
	{
		ValueRef callable_value = GetNS(name);
		if (callable_value->IsUndefined()) {
			return callable_value;
		}

		if (!callable_value->IsMethod()) {
			return Value::Undefined;
		}

		return callable_value->ToMethod()->Call(args);
	}

	std::string& Object::GetType()
	{
		return type;
	}

	ObjectRef Object::Unwrap(ObjectRef o)
	{
		AutoPtr<ProfiledBoundObject> pobj = o.cast<ProfiledBoundObject>();
		if (pobj.isNull())
		{
			return o;
		}
		else
		{
			return pobj->GetDelegate();
		}
	}

}

