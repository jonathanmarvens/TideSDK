/**
 * Appcelerator Kroll - licensed under the Apache Public License 2
 * see LICENSE in the root folder for details on the license.
 * Copyright (c) 2009 Appcelerator, Inc. All Rights Reserved.
 */

#ifndef _PHP_INTERPRETER_H_
#define _PHP_INTERPRETER_H_

#include <tide/Interpreter.h>

namespace tide {

class PHPInterpreter : public Interpreter {
public:
	PHPInterpreter();

    ValueRef EvaluateFile(const char* filepath, KObjectRef context);
	
private:
	std::string CreateContextName();
	void FillGet(Poco::URI& uri TSRMLS_DC);
};

} // namespace tide

#endif
