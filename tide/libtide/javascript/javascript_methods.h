/**
 * Appcelerator Kroll - licensed under the Apache Public License 2
 * see LICENSE in the root folder for details on the license.
 * Copyright (c) 2008-2010 Appcelerator, Inc. All Rights Reserved.
 */

#ifndef _JAVASCRIPT_METHODS_H_
#define _JAVASCRIPT_METHODS_H_

namespace tide
{
namespace JavaScriptMethods
{

void Bind(ObjectRef global);
ValueRef SetTimeout(const ValueList& args);
ValueRef SetInterval(const ValueList& args);
ValueRef ClearTimeout(const ValueList& args);
ValueRef ClearInterval(const ValueList& args);

}
}
#endif
