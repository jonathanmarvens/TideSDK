/**
 * Appcelerator Kroll - licensed under the Apache Public License 2
 * see LICENSE in the root folder for details on the license.
 * Copyright (c) 2008 Appcelerator, Inc. All Rights Reserved.
 */

#ifndef _JS_UTIL_H_
#define _JS_UTIL_H_

namespace tide
{
namespace JSUtil
{

TIDE_API ValueRef ToTideValue(JSValueRef, JSContextRef, JSObjectRef);
TIDE_API JSValueRef ToJSValue(ValueRef, JSContextRef);
TIDE_API JSValueRef ObjectToJSValue(ValueRef, JSContextRef);
TIDE_API JSValueRef MethodToJSValue(ValueRef, JSContextRef);
TIDE_API JSValueRef ListToJSValue(ValueRef, JSContextRef);
TIDE_API std::string ToChars(JSStringRef);
TIDE_API bool IsArrayLike(JSObjectRef, JSContextRef);
TIDE_API JSGlobalContextRef CreateGlobalContext();
TIDE_API void RegisterGlobalContext(JSObjectRef, JSGlobalContextRef);
TIDE_API void UnregisterGlobalContext(JSGlobalContextRef);
TIDE_API JSGlobalContextRef GetGlobalContext(JSObjectRef);
TIDE_API void ProtectGlobalContext(JSGlobalContextRef);
TIDE_API void UnprotectGlobalContext(JSGlobalContextRef);
TIDE_API ValueRef Evaluate(JSContextRef context, const char* script,
	 const char* url = "string");
TIDE_API ValueRef EvaluateFile(JSContextRef context,
	const std::string& fullPath);
TIDE_API ValueRef GetProperty(JSObjectRef, std::string name);

};
}

#endif
