/*
 * Copyright (c) 2008-2010 Appcelerator, Inc. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef Application_h
#define Application_h

#include <tide/tide.h>

namespace ti {

class Application : public KAccessorObject {
public:
    Application(Host *host,KObjectRef);
    virtual ~Application();

private:
    void GetID(const ValueList& args, ValueRef result);
    void GetName(const ValueList& args, ValueRef result);
    void GetVersion(const ValueList& args, ValueRef result);
    void GetPublisher(const ValueList& args, ValueRef result);
    void GetCopyright(const ValueList& args, ValueRef result);
    void GetDescription(const ValueList& args, ValueRef result);
    void GetURL(const ValueList& args, ValueRef result);
    void GetGUID(const ValueList& args, ValueRef result);
    void GetIcon(const ValueList& args, ValueRef result);
    void GetStreamURL(const ValueList& args, ValueRef result);
    void GetPath(const ValueList& args, ValueRef result);
    void GetHome(const ValueList& args, ValueRef result);
    void GetArguments(const ValueList& args, ValueRef result);
    void AppURLToPath(const ValueList& args, ValueRef result);
    void SetMenu(const ValueList& args, ValueRef result);
    void Exit(const ValueList& args, ValueRef result);
    void Restart(const ValueList& args, ValueRef result);
    void StdOut(const ValueList& args, ValueRef result);
    void StdErr(const ValueList& args, ValueRef result);
    void StdIn(const ValueList& args, ValueRef result);

    void CreateProperties(const ValueList& args, ValueRef result);
    void LoadProperties(const ValueList& args, ValueRef result);
    void GetSystemProperties(const ValueList& args, ValueRef result);

    Host* host;
    KObjectRef global;

protected:
    void Setup();
};

} // namespace ti

#endif
