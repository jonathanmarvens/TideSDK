/*
 * Copyright (c) 2009-2010 Appcelerator, Inc. All Rights Reserved.
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

#ifndef ResultSet_h
#define ResultSet_h

#include <tide/tide.h>
#include <Poco/Data/RecordSet.h>

namespace ti {

class ResultSet : public StaticBoundObject {
public:
    ResultSet();
    ResultSet(Poco::Data::RecordSet& rs);
    virtual ~ResultSet();

private:    
    void Bind();
    void TransformValue(size_t index, ValueRef result);
    

    void IsValidRow(const ValueList& args, ValueRef result);
    void Next(const ValueList& args, ValueRef result);
    void Close(const ValueList& args, ValueRef result);
    void RowCount(const ValueList& args, ValueRef result);
    void FieldCount(const ValueList& args, ValueRef result);
    void FieldName(const ValueList& args, ValueRef result);
    void Field(const ValueList& args, ValueRef result);
    void FieldByName(const ValueList& args, ValueRef result);

    SharedPtr<Poco::Data::RecordSet> rs;
    bool eof;
};

} // namespace ti

#endif
