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

#ifndef Codec_h
#define Codec_h

#include <tide/tide.h>

#include <Poco/Zip/Zip.h>
#include <Poco/Zip/Compress.h>
#include <Poco/Zip/Decompress.h>
#include <Poco/Path.h>

namespace ti {

class Codec : public StaticBoundObject
{
public:
    Codec(ObjectRef);
    virtual ~Codec();

private:
    void EncodeBase64(const ValueList& args, ValueRef result);
    void DecodeBase64(const ValueList& args, ValueRef result);
    void DigestToHex(const ValueList& args, ValueRef result);
    void DigestHMACToHex(const ValueList& args, ValueRef result);
    void EncodeHexBinary(const ValueList& args, ValueRef result);
    void DecodeHexBinary(const ValueList& args, ValueRef result);
    void Checksum(const ValueList& args, ValueRef result);
    void CreateZip(const ValueList& args, ValueRef result);
    void ExtractZip(const ValueList& args, ValueRef result);
    
    static ValueRef CreateZipAsync(const ValueList& args);
    static ValueRef ExtractZipAsync(const ValueList& args);

    ObjectRef global;
};

} // namespace ti

#endif
