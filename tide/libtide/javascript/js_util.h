/**
 * Appcelerator Kroll - licensed under the Apache Public License 2
 * see LICENSE in the root folder for details on the license.
 * Copyright (c) 2008 Appcelerator, Inc. All Rights Reserved.
 */

#ifndef _KJS_UTIL_H_
#define _KJS_UTIL_H_

namespace tide
{
namespace JSUtil
{

TIDE_API KValueRef ToTideValue(JSValueRef, JSContextRef, JSObjectRef);
TIDE_API JSValueRef ToJSValue(KValueRef, JSContextRef);
TIDE_API JSValueRef KObjectToJSValue(KValueRef, JSContextRef);
TIDE_API JSValueRef KMethodToJSValue(KValueRef, JSContextRef);
TIDE_API JSValueRef KListToJSValue(KValueRef, JSContextRef);
TIDE_API std::string ToChars(JSStringRef);
TIDE_API bool IsArrayLike(JSObjectRef, JSContextRef);
TIDE_API JSGlobalContextRef CreateGlobalContext();
TIDE_API void RegisterGlobalContext(JSObjectRef, JSGlobalContextRef);
TIDE_API void UnregisterGlobalContext(JSGlobalContextRef);
TIDE_API JSGlobalContextRef GetGlobalContext(JSObjectRef);
TIDE_API void ProtectGlobalContext(JSGlobalContextRef);
TIDE_API void UnprotectGlobalContext(JSGlobalContextRef);
TIDE_API KValueRef Evaluate(JSContextRef context, const char* script,
	 const char* url = "string");
TIDE_API KValueRef EvaluateFile(JSContextRef context,
	const std::string& fullPath);
TIDE_API KValueRef GetProperty(JSObjectRef, std::string name);

};
}

#endif
