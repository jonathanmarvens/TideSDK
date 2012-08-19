/*
 * Appcelerator Kroll - licensed under the Apache Public License 2
 * see LICENSE in the root folder for details on the license.
 * Copyright (c) 2008 Appcelerator, Inc. All Rights Reserved.
 */

#include "../tide.h"
#include <sstream>

namespace tide
{

	bool Object::Equals(KObjectRef other)
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
			KValueRef prop = this->Get(props->at(i));
			SharedString disp_string = prop->DisplayString(levels);

			ss << " " << *(props->at(i))
			    << " : " << *disp_string << ",";
		}

		if (props->size() > 0) // Erase last comma
			ss.seekp((int)ss.tellp() - 1);

		ss << "}";

		return new std::string(ss.str());
	}

	void Object::Set(SharedString name, KValueRef value)
	{
		this->Set(name->c_str(), value);
	}

	KValueRef Object::Get(SharedString name)
	{
		return this->Get(name->c_str());
	}

	int Object::GetInt(const char* name, int defaultValue)
	{
		KValueRef prop = this->Get(name);
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
		KValueRef prop = this->Get(name);
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
		KValueRef prop = this->Get(name);
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
		KValueRef prop = this->Get(name);
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
		KValueRef prop = this->Get(name);
		if(prop->IsString())
		{
			return prop->ToString();
		}
		else
		{
			return defaultValue;
		}
	}

	KObjectRef Object::GetObject(const char* name, KObjectRef defaultValue)
	{
		KValueRef prop = this->Get(name);
		if (prop->IsObject())
		{
			return prop->ToObject();
		}
		else
		{
			return defaultValue;
		}
	}

	KMethodRef Object::GetMethod(const char* name, KMethodRef defaultValue)
	{
		KValueRef prop = this->Get(name);
		if (prop->IsMethod())
		{
			return prop->ToMethod();
		}
		else
		{
			return defaultValue;
		}
	}

	KListRef Object::GetList(const char* name, KListRef defaultValue)
	{
		KValueRef prop = this->Get(name);
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
		KValueRef val = Value::NewInt(v);
		this->Set(name, val);
	}

	void Object::SetDouble(const char *name, double v)
	{
		KValueRef val = Value::NewDouble(v);
		this->Set(name, val);
	}

	void Object::SetNumber(const char *name, double v)
	{
		KValueRef val = Value::NewDouble(v);
		this->Set(name, val);
	}

	void Object::SetBool(const char *name, bool v)
	{
		KValueRef val = Value::NewBool(v);
		this->Set(name, val);
	}

	void Object::SetString(const char *name, std::string v)
	{
		KValueRef val = Value::NewString(v);
		this->Set(name, val);
	}

	void Object::SetObject(const char *name, KObjectRef object)
	{
		KValueRef obj_val = Value::NewObject(object);
		this->Set(name, obj_val);
	}

	void Object::SetMethod(const char *name, KMethodRef object)
	{
		KValueRef obj_val = Value::NewMethod(object);
		this->Set(name, obj_val);
	}

	void Object::SetList(const char *name, KListRef object)
	{
		KValueRef obj_val = Value::NewList(object);
		this->Set(name, obj_val);
	}

	void Object::GetStringList(const char *name, std::vector<std::string> &list)
	{
		KValueRef prop = this->Get(name);
		if(!prop->IsUndefined() && prop->IsList())
		{
			KListRef values = prop->ToList();
			if (values->Size() > 0)
			{
				for (unsigned int c = 0; c < values->Size(); c++)
				{
					KValueRef v = values->At(c);
					if (v->IsString())
					{
						const char *s = v->ToString();
						list.push_back(s);
					}
				}
			}
		}
	}

	void Object::SetNS(const char *name, KValueRef value)
	{
		std::vector<std::string> tokens;
		FileUtils::Tokenize(std::string(name), tokens, ".");

		Object *scope = this;
		for (size_t i = 0; i < tokens.size() - 1; i++)
		{
			const char* token = tokens[i].c_str();
			StaticBoundObject *next;
			KValueRef next_val = scope->Get(token);

			if (next_val->IsUndefined())
			{
				next = new StaticBoundObject();
				KObjectRef so = next;
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

	KValueRef Object::GetNS(const char *name)
	{
		std::string s(name);
		std::string::size_type last = 0;
		std::string::size_type pos = s.find_first_of(".");
		KValueRef current;
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

	KValueRef Object::CallNS(const char *name)
	{
		ValueList args;
		return CallNS(name, args);
	}
	
	KValueRef Object::CallNS(const char *name, KValueRef val1)
	{
		ValueList args;
		args.push_back(val1);
		return CallNS(name, args);
	}

	KValueRef Object::CallNS(const char *name, KValueRef val1, KValueRef val2)
	{
		ValueList args;
		args.push_back(val1);
		args.push_back(val2);
		return CallNS(name, args);
	}

	KValueRef Object::CallNS(const char *name, KValueRef val1, KValueRef val2, KValueRef val3)
	{
		ValueList args;
		args.push_back(val1);
		args.push_back(val2);
		args.push_back(val3);
		return CallNS(name, args);
	}

	KValueRef Object::CallNS(const char *name, const ValueList& args)
	{
		KValueRef callable_value = GetNS(name);
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

	KObjectRef Object::Unwrap(KObjectRef o)
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

