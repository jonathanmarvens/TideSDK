/**
* Appcelerator Kroll - licensed under the Apache Public License 2
* see LICENSE in the root folder for details on the license.
* Copyright (c) 2009 Appcelerator, Inc. All Rights Reserved.
*/
#include "php_module.h"

extern "C" {
#include <spl/spl_array.h>
}

#define GET_MY_List() \
	reinterpret_cast<PHPKObject*>( \
	 zend_object_store_get_object(getThis() TSRMLS_CC))->kvalue->ToList()

// FIXME: PHP does not export any of the token constants in the
// headers so we have to hardcode them here. Ick.
#define T_FUNCTION 334
#define T_STRING 307
using std::string;
using std::map;

namespace tide
{
	static map<string, string> currentCaseMap;
	zend_class_entry *PHPKObjectClassEntry = NULL;
	zend_class_entry *PHPMethodClassEntry = NULL;
	zend_class_entry *PHPListClassEntry = NULL;
	zend_object_handlers PHPKObjectHandlers;
	zend_object_handlers PHPMethodHandlers;
	zend_object_handlers PHPListHandlers;

	// Private data and function declarations below here
	static zend_object_value PHPKObjectCreateObject(zend_class_entry *ce TSRMLS_DC);
	static zend_class_entry* PHPKObjectGetClassEntry(const zval* zthis TSRMLS_DC);
	static zend_class_entry* PHPMethodGetClassEntry(const zval* zthis TSRMLS_DC);
	static zend_class_entry* PHPListGetClassEntry(const zval* zthis TSRMLS_DC);
	static void PHPKObjectFreeStorage(void* zthis TSRMLS_DC);
	static zval* PHPKObjectReadProperty(zval* zthis, zval* property, int type TSRMLS_DC);
	static void PHPKObjectWriteProperty(zval* zthis, zval* property, zval* value TSRMLS_DC);
	static HashTable* PHPKObjectGetProperties(zval* zthis TSRMLS_DC);
	static void PHPKObjectUnsetProperty(zval* zthis, zval* property TSRMLS_DC);
	static int PHPKObjectHasProperty(zval* zthis, zval* property, int type TSRMLS_DC);
	static int PHPKObjectHasDimension(zval* zthis, zval* property, int type TSRMLS_DC);

	PHP_METHOD(PHPKObject, __toString);
	PHP_METHOD(PHPKObject, __call);
	PHP_METHOD(PHPMethod, __invoke);
	PHP_METHOD(PHPList, offsetExists);
	PHP_METHOD(PHPList, offsetGet);
	PHP_METHOD(PHPList, offsetUnset);
	PHP_METHOD(PHPList, offsetSet);
	PHP_METHOD(PHPList, count);
	PHP_METHOD(PHPList, append);
	PHP_METHOD(PHPList, getArrayCopy);
	PHP_METHOD(PHPList, exchangeArray);

	static ZEND_FUNCTION(krollAddFunction);

	ZEND_BEGIN_ARG_INFO_EX(KrollAddFunctionArgInfo, 0, 0, 2)
		ZEND_ARG_INFO(0, object)
		ZEND_ARG_INFO(0, fname)
	ZEND_END_ARG_INFO()
	
	static const zend_function_entry PHPFunctions[] = {
		ZEND_FE(krollAddFunction, KrollAddFunctionArgInfo)
		{ NULL, NULL, NULL, NULL }
	};

	// This is our class "function" table. Right now we only implement
	// __call, because that seems to be preferred over the handler version.
	ZEND_BEGIN_ARG_INFO_EX(PHPKObjectCallArgInfo, 0, 0, 2)
	ZEND_ARG_INFO(0, methodName)
	ZEND_ARG_INFO(0, arguments)
	ZEND_END_ARG_INFO()

	static function_entry PHPKObjectMethods[] =
	{
		PHP_ME(PHPKObject, __call, PHPKObjectCallArgInfo, ZEND_ACC_PUBLIC)
		PHP_ME(PHPKObject, __toString, NULL, ZEND_ACC_PUBLIC)
		{NULL, NULL, NULL}
	};

	static function_entry PHPMethodMethods[] =
	{
		PHP_ME(PHPMethod, __invoke, NULL, ZEND_ACC_PUBLIC)
		PHP_ME(PHPKObject, __call, PHPKObjectCallArgInfo, ZEND_ACC_PUBLIC)
		PHP_ME(PHPKObject, __toString, NULL, ZEND_ACC_PUBLIC)
		{NULL, NULL, NULL}
	};

	ZEND_BEGIN_ARG_INFO_EX(PHPListOffsetGetArgInfo, 0, 0, 1)
		ZEND_ARG_INFO(0, index)
	ZEND_END_ARG_INFO()
	ZEND_BEGIN_ARG_INFO_EX(PHPListOffsetSetArgInfo, 0, 0, 2)
		ZEND_ARG_INFO(0, index)
		ZEND_ARG_INFO(0, newval)
	ZEND_END_ARG_INFO()
	ZEND_BEGIN_ARG_INFO(PHPListAppendArgInfo, 0)
		ZEND_ARG_INFO(0, value)
	ZEND_END_ARG_INFO()
	ZEND_BEGIN_ARG_INFO(PHPListExchangeArrayArgInfo, 0)
		ZEND_ARG_INFO(0, array)
	ZEND_END_ARG_INFO()
	ZEND_BEGIN_ARG_INFO(PHPListVoidArgInfo, 0)
	ZEND_END_ARG_INFO()

	static function_entry PHPListMethods[] =
	{
		PHP_ME(PHPKObject, __call, PHPKObjectCallArgInfo, ZEND_ACC_PUBLIC)
		PHP_ME(PHPKObject, __toString, NULL, ZEND_ACC_PUBLIC)
		PHP_ME(PHPList, offsetExists, PHPListOffsetGetArgInfo, ZEND_ACC_PUBLIC)
		PHP_ME(PHPList, offsetGet, PHPListOffsetGetArgInfo, ZEND_ACC_PUBLIC)
		PHP_ME(PHPList, offsetSet, PHPListOffsetSetArgInfo, ZEND_ACC_PUBLIC)
		PHP_ME(PHPList, offsetUnset, PHPListOffsetGetArgInfo, ZEND_ACC_PUBLIC)
		PHP_ME(PHPList, count, PHPListVoidArgInfo, ZEND_ACC_PUBLIC)
		PHP_ME(PHPList, exchangeArray, PHPListExchangeArrayArgInfo, ZEND_ACC_PUBLIC)
		PHP_ME(PHPList, getArrayCopy, PHPListVoidArgInfo, ZEND_ACC_PUBLIC)
		{NULL, NULL, NULL}
	};

	PHP_METHOD(PHPKObject, __toString)
	{
		ValueRef kvalue(reinterpret_cast<PHPKObject*>(
			zend_object_store_get_object(getThis() TSRMLS_CC))->kvalue);
		SharedString ss = kvalue->DisplayString();
		ZVAL_STRINGL(return_value, (char *) ss->c_str(), ss->size(), 1);
	}

	PHP_METHOD(PHPKObject, __call)
	{
		char* methodName;
		int methodNameLength;
		zval* zargs;

		if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "sa",
			&methodName, &methodNameLength, &zargs) == FAILURE)
		{
			zend_throw_exception(zend_exception_get_default(TSRMLS_C),
				(char*) "Wrong arguments passed to __call", 666 TSRMLS_CC);
			RETVAL_NULL();
			return;
		}

		PHPKObject* kthis = reinterpret_cast<PHPKObject*>(
			zend_object_store_get_object(getThis() TSRMLS_CC));
		KObjectRef obj = kthis->kvalue->ToObject();
		MethodRef method = obj->GetMethod(methodName, 0);

		// Find the method by its name.
		if (method.isNull())
		{
			string error("Could not find method named '");
			error.append(methodName);
			error.append("'");
			zend_throw_exception(zend_exception_get_default(TSRMLS_C),
				(char*) error.c_str(), 666 TSRMLS_CC);
			RETVAL_NULL();
			return;
		}

		// Pull out the arguments from the argument array.
		ArgList kargs;
		int numArgs = zend_hash_num_elements(Z_ARRVAL_P(zargs));
		if (numArgs > 0)
		{
			HashPosition position;
			zval** parameter;
			zend_hash_internal_pointer_reset_ex(Z_ARRVAL_P(zargs), &position);

			while (zend_hash_get_current_data_ex(Z_ARRVAL_P(zargs),
				(void **) &parameter, &position) == SUCCESS)
			{
				kargs.push_back(PHPUtils::ToTideValue(*parameter TSRMLS_CC));
				zend_hash_move_forward_ex(Z_ARRVAL_P(zargs), &position);
			}
		}

		// Do the method invocation.
		try
		{
			ValueRef returnValue = method->Call(kargs);
			PHPUtils::ToPHPValue(returnValue, &return_value);
		}
		catch (ValueException& e)
		{
			zend_throw_exception(zend_exception_get_default(TSRMLS_C),
				(char*) e.ToString().c_str(), 666 TSRMLS_CC);
			RETVAL_NULL();
			return;
		}
	}

	zend_object_value PHPKObjectCreateObject(zend_class_entry *classEntry TSRMLS_DC)
	{
		PHPKObject* intern;
		zend_object_value retval;

		// We're using a custom zend_object* (PHPKObject*) so we
		// need to do the things done by zend_objects_new manually.
		intern = (PHPKObject*) emalloc(sizeof(PHPKObject));
		memset(intern, 0, sizeof(PHPKObject));

		zend_object_std_init(&intern->std, classEntry TSRMLS_CC);

		// We don't have any default properties in our object
		// so just start out with a blank properties hash.
		ALLOC_HASHTABLE(intern->std.properties);
		zend_hash_init(intern->std.properties,
			0, NULL, ZVAL_PTR_DTOR, 0);

		// Use the standard object destructor, but we want to use a
		// custom memory free so that we can deference the internal
		// Kroll value.
		retval.handle = zend_objects_store_put(intern,
			(zend_objects_store_dtor_t) zend_objects_destroy_object,
			(zend_objects_free_object_storage_t) PHPKObjectFreeStorage,
			NULL TSRMLS_CC);

		// Use our special handlers for doing common object operations.
		if (classEntry == PHPListClassEntry)
			retval.handlers = &PHPListHandlers;
		else if (classEntry == PHPMethodClassEntry)
			retval.handlers = &PHPMethodHandlers;
		else
			retval.handlers = &PHPKObjectHandlers;

		return retval;
	}

	void PHPKObjectFreeStorage(void *zthis TSRMLS_DC)
	{
		PHPKObject* phpkobject = static_cast<PHPKObject*>(zthis);
		phpkobject->kvalue = 0;

		zend_object_std_dtor(&phpkobject->std TSRMLS_CC);
		efree(zthis);
	}

	zval* PHPKObjectReadProperty(zval* zthis, zval* property, int type TSRMLS_DC)
	{
		PHPKObject* kthis = reinterpret_cast<PHPKObject*>(
			zend_object_store_get_object(zthis TSRMLS_CC));
		KObjectRef obj = kthis->kvalue->ToObject();
		string propertyName = PHPUtils::ZvalToPropertyName(property);

		try
		{
			ValueRef value = obj->Get(propertyName.c_str());
			return PHPUtils::ToPHPValue(value);
		}
		catch (ValueException& e)
		{
			zend_throw_exception(zend_exception_get_default(TSRMLS_C),
				(char*) e.ToString().c_str(), 666 TSRMLS_CC);
			zval* retval = NULL;
			ZVAL_NULL(retval);
			return retval;
		}
	}

	void PHPKObjectWriteProperty(zval* zthis, zval* property, zval* value TSRMLS_DC)
	{
		PHPKObject* kthis = reinterpret_cast<PHPKObject*>(
			zend_object_store_get_object(zthis TSRMLS_CC));

		try
		{
			ValueRef tideValue = PHPUtils::ToTideValue(value TSRMLS_CC);
			if (!property) // A NULL property name means this is an append ([]=) operation.
			{
				// TODO: It's unclear what this should do if not called on a list.
				if (kthis->kvalue->IsList())
				{
					kthis->kvalue->ToList()->Append(tideValue);
				}
			}
			else
			{
				KObjectRef obj = kthis->kvalue->ToObject();
				string propertyName = PHPUtils::ZvalToPropertyName(property);
					obj->Set(propertyName.c_str(), tideValue);
			}
		}
		catch (ValueException& e)
		{
			zend_throw_exception(
				zend_exception_get_default(TSRMLS_C), (char*) e.ToString().c_str(), 666 TSRMLS_CC);
		}
	}

	HashTable* PHPKObjectGetProperties(zval *zthis TSRMLS_DC)
	{
		PHPKObject *kthis = reinterpret_cast<PHPKObject*>(
			zend_object_store_get_object(zthis TSRMLS_CC));
		KObjectRef obj = kthis->kvalue->ToObject();

		try
		{
			SharedStringList propertyNames = obj->GetPropertyNames();
			HashTable* properties;
			ALLOC_HASHTABLE(properties);
			zend_hash_init(properties, propertyNames->size(), NULL, ZVAL_PTR_DTOR, 0);

			for (size_t i = 0; i < propertyNames->size(); i++)
			{
				const char *key = propertyNames->at(i)->c_str();
				ValueRef value = obj->Get(key);
				zval* zvalue = PHPUtils::ToPHPValue(value);
				zend_hash_add(properties, (char *)key, strlen(key)+1, &zvalue, sizeof(zval*), NULL);
			}
			return properties;
		}
		catch (ValueException& e)
		{
			zend_throw_exception(zend_exception_get_default(TSRMLS_C),
				(char *) e.ToString().c_str(), 666 TSRMLS_CC);
		}

		return 0;
	}

	/* Extending and Embedding PHP pg. 153
	 * When isset() is called against an object property, this handler is invoked.
	 * By default the standard handler will check for the property named by
	 * 'property', if it's not found and -- as of PHP 4.1.0 -- if an __isset()
	 * method is defined it will call that. The checkType parameter will be one of
	 * three possible values. If the value is 2 the property need only exist to
	 * qualify as a success. If the checkType is 0, it must exist and be of any
	 * type except IS_NULL. If the value of checkType is 1, the value msut both
	 * eist and evaluate to a non-false value. Note: In PHP 4.0.x the meaning of
	 * checkType matched has_dimension's version of checkType (Martin: but not any
	 * longer!).
	 */
	int PHPKObjectHasProperty(zval* zthis, zval* property, int checkType TSRMLS_DC)
	{
		PHPKObject* kthis = reinterpret_cast<PHPKObject*>(
			zend_object_store_get_object(zthis TSRMLS_CC));
		KObjectRef obj = kthis->kvalue->ToObject();
		string propertyName = PHPUtils::ZvalToPropertyName(property);

		if (checkType == 0)
		{
			ValueRef value = obj->Get(propertyName.c_str());
			return !value->IsUndefined() && !value->IsNull();
		}
		else if (checkType == 1)
		{
			ValueRef value = obj->Get(propertyName.c_str());
			zval* phpValue = PHPUtils::ToPHPValue(value);
			convert_to_boolean(phpValue);
			return Z_BVAL_P(phpValue);
		}
		else // Generally this should be checkType == 2
		{
			return obj->HasProperty(propertyName.c_str());
		}
	}

	/* Extending and Embedding PHP pg. 154
	 * When isset() is called against an object that is being treated like an
	 * array, such as isset($obj['idx']), this handler is used. The standard
	 * handler, if the object implements the ArrayAccess interface, will call the
	 * offsetexists($idx) method first. If not found, it returns failure in the
	 * form of a 0. Otherwise, if checkType is 0 it returns true (1) immediately.
	 * A checkType of 1 indicates that it must also check that the value is
	 * non-false by invoking the object's offsetget($idx) method as well and
	 * examining the returned value.
	 */
	int PHPKObjectHasDimension(zval* zthis, zval* property, int checkType TSRMLS_DC)
	{
		PHPKObject* kthis = reinterpret_cast<PHPKObject*>(
			zend_object_store_get_object(zthis TSRMLS_CC));
		KObjectRef obj = kthis->kvalue->ToObject();
		string propertyName = PHPUtils::ZvalToPropertyName(property);

		if (checkType == 0)
		{
			return obj->HasProperty(propertyName.c_str());
		}
		else
		{
			if (!obj->HasProperty(propertyName.c_str()))
			{
				return false;
			}
			else
			{
				ValueRef value = obj->Get(propertyName.c_str());
				zval* phpValue = PHPUtils::ToPHPValue(value);
				convert_to_boolean(phpValue);
				return Z_BVAL_P(phpValue);
			}
		}
	}

	zend_class_entry* PHPKObjectGetClassEntry(const zval* zthis TSRMLS_DC)
	{
		return PHPKObjectClassEntry;
	}

	zend_class_entry* PHPMethodGetClassEntry(const zval* zthis TSRMLS_DC)
	{
		return PHPMethodClassEntry;
	}

	zend_class_entry* PHPListGetClassEntry(const zval* zthis TSRMLS_DC)
	{
		return PHPListClassEntry;
	}

	void PHPKObjectUnsetProperty(zval* zthis, zval* property TSRMLS_DC)
	{
		PHPKObject* kthis = reinterpret_cast<PHPKObject*>(
			zend_object_store_get_object(zthis TSRMLS_CC));
		KObjectRef obj = kthis->kvalue->ToObject();
		string propertyName = PHPUtils::ZvalToPropertyName(property);

		try
		{
			obj->Set(propertyName.c_str(), Value::Undefined);
		}
		catch (ValueException& e)
		{
			zend_throw_exception(
				zend_exception_get_default(TSRMLS_C), (char*) e.ToString().c_str(), 666 TSRMLS_CC);
		}
	}

	PHP_METHOD(PHPMethod, __invoke)
	{
		PHPKObject* kthis = reinterpret_cast<PHPKObject*>(
			zend_object_store_get_object(getThis() TSRMLS_CC));
		MethodRef Method = kthis->kvalue->ToMethod();

		zend_function *func = EG(current_execute_data)->function_state.function;
		zval*** arguments = (zval***) emalloc(sizeof(zval**) * ZEND_NUM_ARGS());

		if (zend_get_parameters_array_ex(ZEND_NUM_ARGS(), arguments) == FAILURE)
		{
			efree(arguments);
			zend_error(E_RECOVERABLE_ERROR, "Cannot get arguments for calling closure");
			RETVAL_FALSE;
			return;
		}

		ArgList kargs;
		for (int i = 0; i < ZEND_NUM_ARGS(); i++)
		{
			zval** zargValue = arguments[i];
			ValueRef argValue = PHPUtils::ToTideValue(*zargValue TSRMLS_CC);
			kargs.push_back(argValue);
		}
		efree(arguments);

		PHPUtils::PushPHPSymbolsIntoGlobalObject(&EG(symbol_table),
			 PHPUtils::GetCurrentGlobalObject() TSRMLS_CC);

		// CAUTION: FRIGGIN SWEET METHOD INVOCATION COMING UP.
		try
		{
			ValueRef returnValue = Method->Call(kargs);
			PHPUtils::ToPHPValue(returnValue, &return_value);
		}
		catch (ValueException& e)
		{
			// TODO: Create an exception class that can hold a ValueRef.
			zend_throw_exception(zend_exception_get_default(TSRMLS_C),
				(char*) e.ToString().c_str(), 666 TSRMLS_CC);
			RETVAL_NULL();
		}

		PHPUtils::PushGlobalObjectMembersIntoPHPSymbolTable(&EG(symbol_table),
			PHPUtils::GetCurrentGlobalObject() TSRMLS_CC);
	}

	PHP_METHOD(PHPList, offsetExists)
	{
		zval *index;
		if (zend_parse_parameters(ZEND_NUM_ARGS()
			TSRMLS_CC, "z", &index) == FAILURE) {
			return;
		}

		ListRef List(GET_MY_List());
		string name(PHPUtils::ZvalToPropertyName(index));
		RETURN_BOOL((!name.empty() && List->HasProperty(name.c_str())));
	}

	PHP_METHOD(PHPList, offsetGet)
	{
		zval *index;
		if (zend_parse_parameters(ZEND_NUM_ARGS()
			TSRMLS_CC, "z", &index) == FAILURE)
		 {
			return;
			
		}

		ListRef List(GET_MY_List());
		string name(PHPUtils::ZvalToPropertyName(index));
		ValueRef returnValue(List->Get(name.c_str()));
		PHPUtils::ToPHPValue(returnValue, &return_value);
	}

	PHP_METHOD(PHPList, offsetSet)
	{
		zval *zindexString, *zvalue;
		if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zz",
			&zindexString, &zvalue) == FAILURE)
		{
			return;
		}

		ListRef List(GET_MY_List());
		string indexString(PHPUtils::ZvalToPropertyName(zindexString));
		ValueRef value(PHPUtils::ToTideValue(zvalue TSRMLS_CC));

		if (List::IsInt(indexString))
		{
			List->SetAt(List::ToIndex(indexString), value);
		}
		else
		{
			List->Set(indexString.c_str(), value);
		}
	}

	PHP_METHOD(PHPList, offsetUnset)
	{
		zval *zindex;
		if (zend_parse_parameters(ZEND_NUM_ARGS()
			TSRMLS_CC, "z", &zindex) == FAILURE) {
			return;
		}

		ListRef List(GET_MY_List());
		string indexString(PHPUtils::ZvalToPropertyName(zindex));
		List->Set(indexString.c_str(), Value::Undefined);
	}

	PHP_METHOD(PHPList, count)
	{
		ListRef List(GET_MY_List());
		SharedStringList propertyList = List->GetPropertyNames();
		RETVAL_LONG(propertyList->size());
	}

	PHP_METHOD(PHPList, append)
	{
		zval *zvalue;
		if (zend_parse_parameters(ZEND_NUM_ARGS()
			TSRMLS_CC, "z", &zvalue) == FAILURE)
		{
			return;
		}

		ListRef List(GET_MY_List());
		ValueRef value(PHPUtils::ToTideValue(zvalue TSRMLS_CC));
		List->Append(value);
	} 

	PHP_METHOD(PHPList, getArrayCopy)
	{
		ListRef List(GET_MY_List());
		SharedStringList propertyList = List->GetPropertyNames();

		array_init(return_value);
		for (size_t i = 0; i < propertyList->size(); i++)
		{
			SharedString ss(propertyList->at(i));
			zval* newValue = PHPUtils::ToPHPValue(List->Get(ss->c_str()));
			zend_hash_next_index_insert(HASH_OF(return_value),
				(void**) &newValue, sizeof (void*), 0);
		}
	}

	PHP_METHOD(PHPList, exchangeArray)
	{
		// TODO: Implement
	}

	ZEND_FUNCTION(krollAddFunction)
	{
		zval *phpWindowContext;
		char *fname;
		int fnameLength;
		if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zs",
			&phpWindowContext, &fname, &fnameLength) == FAILURE)
		{
			return;
		}
		
		PHPKObject* object = reinterpret_cast<PHPKObject*>(
			zend_object_store_get_object(phpWindowContext TSRMLS_CC));

		// If there is a preceding namespace to this function name trim it off.
		// This is likely the namespace we use to isolate PHP executions.
		string fnameString(fname);
		size_t index = fnameString.find("\\");
		if (index != string::npos)
		{
			fnameString = fnameString.substr(index + 1);
		}

		// Convert the function name back to its original case.
		if (currentCaseMap.find(fnameString) != currentCaseMap.end())
			fnameString = currentCaseMap[fnameString];

		// Use the name without the namespace for the Window object, but use
		// the full name for the KPHPFunction.
		KObjectRef window = object->kvalue->ToObject();
		window->Set(fnameString.c_str(),
			Value::NewMethod(new KPHPFunction(fname)));
	}

	namespace PHPUtils
	{
		void InitializePHPKrollClasses()
		{
			TSRMLS_FETCH();

			// Initialize the class entry for our classes
			zend_class_entry kobjectClassEntry;
			INIT_CLASS_ENTRY(kobjectClassEntry, "PHPKObject", PHPKObjectMethods);
			PHPKObjectClassEntry = zend_register_internal_class(&kobjectClassEntry TSRMLS_CC);
			zend_class_entry MethodClassEntry;
			INIT_CLASS_ENTRY(MethodClassEntry, "PHPMethod", PHPMethodMethods);
			PHPMethodClassEntry = zend_register_internal_class(&MethodClassEntry TSRMLS_CC);
			zend_class_entry ListClassEntry;
			INIT_CLASS_ENTRY(ListClassEntry, "PHPList", PHPListMethods);
			PHPListClassEntry = zend_register_internal_class_ex(
				&ListClassEntry, spl_ce_ArrayObject, "ArrayObject" TSRMLS_CC);

			// PHPMethod has enough of the same behavior that we can use the same
			// handler table that PHPKObject uses. This may change in the future.
			PHPKObjectClassEntry->create_object = PHPKObjectCreateObject;
			PHPMethodClassEntry->create_object = PHPKObjectCreateObject;
			PHPListClassEntry->create_object = PHPKObjectCreateObject;

			// Create our custom handlers table to override the
			// default behaviour of our PHP objects.
			PHPKObjectHandlers = *zend_get_std_object_handlers();
			PHPKObjectHandlers.read_property = PHPKObjectReadProperty;
			PHPKObjectHandlers.write_property = PHPKObjectWriteProperty;
			PHPKObjectHandlers.get_properties = PHPKObjectGetProperties;
			PHPKObjectHandlers.read_dimension = PHPKObjectReadProperty;
			PHPKObjectHandlers.unset_property = PHPKObjectUnsetProperty;
			PHPKObjectHandlers.unset_dimension = PHPKObjectUnsetProperty;
			PHPKObjectHandlers.write_dimension = PHPKObjectWriteProperty;
			PHPKObjectHandlers.has_property = PHPKObjectHasProperty;
			PHPKObjectHandlers.has_dimension = PHPKObjectHasDimension;
			PHPKObjectHandlers.get_class_entry = PHPKObjectGetClassEntry;

			PHPListHandlers = PHPKObjectHandlers;
			PHPListHandlers.get_class_entry = PHPListGetClassEntry;

			// PHPList mostly uses the standard handlers.
			PHPMethodHandlers = *zend_get_std_object_handlers();
			PHPMethodHandlers.get_class_entry = PHPMethodGetClassEntry;

			// Initialize static functions
			zend_register_functions(NULL, PHPFunctions, NULL, MODULE_PERSISTENT TSRMLS_CC);
		}

		void KObjectToKPHPObject(ValueRef objectValue, zval** returnValue)
		{
			// Initialize our object with our pre-defined Object class entry.
			TSRMLS_FETCH();
			object_init_ex(*returnValue, PHPKObjectClassEntry);

			// Place the KValue into the internal struct.
			PHPKObject* internal = reinterpret_cast<PHPKObject*>(
				zend_object_store_get_object(*returnValue TSRMLS_CC));
			internal->kvalue = objectValue;
		}

		void MethodToKPHPMethod(ValueRef methodValue, zval** returnValue)
		{
			// Initialize our object with our pre-defined Object class entry.
			TSRMLS_FETCH();
			object_init_ex(*returnValue, PHPMethodClassEntry);

			// Place the KValue into the internal struct.
			PHPKObject* internal = reinterpret_cast<PHPKObject*>(
				zend_object_store_get_object(*returnValue TSRMLS_CC));
			internal->kvalue = methodValue;
		}

		void ListToKPHPArray(ValueRef listValue, zval** returnValue)
		{
			// Initialize our object with our pre-defined Object class entry.
			TSRMLS_FETCH();
			object_init_ex(*returnValue, PHPListClassEntry);

			// Place the KValue into the internal struct.
			PHPKObject* internal = reinterpret_cast<PHPKObject*>(
				zend_object_store_get_object(*returnValue TSRMLS_CC));
			internal->kvalue = listValue;
		}

		void GenerateCaseMap(string code TSRMLS_DC)
		{
			// HACK: Okay, so PHP stores all function names in lowercase, but
			// we need the original case, so that developers can call these
			// functions from other contexts. Here do a simple search for function
			// defintions. There are several cases where this can generate inaccurate
			// results. A true fix for this issue may require patching PHP itself.
			currentCaseMap.clear();
			size_t searchStart = 0;
			size_t functionNameStart = code.find("function ", 0);

			while (functionNameStart != string::npos)
			{
				functionNameStart += sizeof("function ");

				// Find next non-space character / beginning of function name.
				while (isspace(code[functionNameStart]))
				{
					if (functionNameStart > code.size())
						return;
					functionNameStart++;
				}

				size_t functionNameEnd = functionNameStart;
				while (!isspace(code[functionNameEnd]) && code[functionNameEnd] != '(')
				{
					if (functionNameEnd > code.size())
						return;
					functionNameEnd++;
				}

				string originalName(code.substr(functionNameStart - 1,
					 functionNameEnd - functionNameStart + 1).c_str());
				string lcName(originalName);
				std::transform(lcName.begin(), lcName.end(), lcName.begin(), tolower);
				currentCaseMap[lcName] = originalName;

				functionNameStart = code.find("function ", functionNameStart);
			}
		}
	}

}
