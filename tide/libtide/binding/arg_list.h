/*
 * Appcelerator Kroll - licensed under the Apache Public License 2
 * see LICENSE in the root folder for details on the license.
 * Copyright (c) 2009 Appcelerator, Inc. All Rights Reserved.
 */

#ifndef _ARG_LISTT_H_
#define _ARG_LISTT_H_

#include <vector>
#include <string>
#include <map>
#include "callback.h"

namespace tide
{
	/**
	 * An argument list
	 *
	 * This class is only used for argument lists. For a list implementation to be
	 *  used as a value in the binding layer, take a look at KList and StaticBoundList.
	 */
	class TIDE_API ArgList
	{
		public:
		ArgList();
		ArgList(ValueRef);
		ArgList(ValueRef, ValueRef);
		ArgList(ValueRef, ValueRef, ValueRef);
		ArgList(ValueRef, ValueRef, ValueRef, ValueRef);
		ArgList(const ArgList&);
		~ArgList() {};

		bool Verify(std::string& argSpec) const;
		void VerifyException(const char* name, std::string argSpec) const;

		public:
		void push_back(ValueRef value);
		size_t size() const;
		const ValueRef& at(size_t) const;
		const ValueRef& operator[](size_t) const;

		ValueRef GetValue(size_t index, ValueRef defaultValue=Value::Undefined) const;
		int GetInt(size_t index, int defaultValue=0) const;
		double GetDouble(size_t index, double defaultValue=0.0) const;
		double GetNumber(size_t index, double defaultValue=0.0) const;
		bool GetBool(size_t index, bool defaultValue=false) const;
		std::string GetString(size_t index, std::string defaultValue="") const;
		KObjectRef GetObject(size_t index, KObjectRef defaultValue=NULL) const;
		KMethodRef GetMethod(size_t index, KMethodRef defaultValue=NULL) const;
		KListRef GetList(size_t index, KListRef defaultValue=NULL) const;

		private:
		SharedPtr<std::vector<ValueRef> > args;

		static inline bool VerifyArg(ValueRef arg, char t);
		static std::string GenerateSignature(const char* name, std::string& argSpec);
	};

}

#endif
