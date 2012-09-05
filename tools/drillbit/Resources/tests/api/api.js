// TODO - add tests for Tide.API methods and properties that are called else where in other tests.
// this test suite contains all of the missing API coverage as of 4-July-20009

describe("ti.API tests",
{
	// test the logging functions
	test_logging_methods: function()
	{
		value_of(Tide.API.critical).should_be_function();
		value_of(Tide.API.debug).should_be_function();
		value_of(Tide.API.error).should_be_function();
		value_of(Tide.API.fatal).should_be_function();
		value_of(Tide.API.notice).should_be_function();
		value_of(Tide.API.trace).should_be_function();
		value_of(Tide.API.warn).should_be_function();
		
		//new 1.0
		value_of(Tide.API.setLogLevel).should_be_function();

		Tide.API.critical("this is a critical message");
		Tide.API.debug("this is a debug message");
		Tide.API.error("this is a error message");
		Tide.API.fatal("this is a fatal message");

		Tide.API.notice("this is a notice message");
		Tide.API.trace("this is a trace message");
		Tide.API.warn("this is a warn message");
		
		Tide.API.print("this is a print message to stdout");
	},
	// test the logging functions
	test_log_method: function()
	{
		value_of(Tide.API.log).should_be_function();

		Tide.API.log(Tide.API.CRITICAL,"this is a log message with severity Tide.API.CRITICAL");
		Tide.API.log(Tide.API.DEBUG,"this is a log message with severity Tide.API.DEBUG");
		Tide.API.log(Tide.API.ERROR,"this is a log message with severity Tide.API.ERROR");
		Tide.API.log(Tide.API.FATAL,"this is a log message with severity Tide.API.FATAL");
		Tide.API.log(Tide.API.INFO,"this is a log message with severity Tide.API.INFO");
		Tide.API.log(Tide.API.NOTICE,"this is a log message with severity Tide.API.NOTICE");
		Tide.API.log(Tide.API.TRACE,"this is a log message with severity Tide.API.TRACE");
		Tide.API.log(Tide.API.WARN,"this is a log message with severity Tide.API.WARN");

	},

	// test the logging functions
	test_setLogLevel_method: function()
	{
		//new 1.0
		value_of(Tide.API.setLogLevel).should_be_function();
		value_of(Tide.API.log).should_be_function();

		Tide.API.setLogLevel(Tide.API.WARN);
		Tide.API.log(Tide.API.FATAL,"this is a log message with severity Tide.API.FATAL should be logged");
		Tide.API.log(Tide.API.CRITICAL,"this is a log message with severity Tide.API.CRITICAL should be logged");
		Tide.API.log(Tide.API.ERROR,"this is a log message with severity Tide.API.ERROR should be logged");
		Tide.API.log(Tide.API.WARN,"Logging severity set to Tide.API.WARN");
		Tide.API.log(Tide.API.NOTICE,"this is a log message with severity Tide.API.NOTICE should not be logged");
		Tide.API.log(Tide.API.INFO,"this is a log message with severity Tide.API.INFO should not be logged");
		Tide.API.log(Tide.API.DEBUG,"this is a log message with severity Tide.API.DEBUG should not be logged");
		Tide.API.log(Tide.API.TRACE,"this is a log message with severity Tide.API.TRACE should not be logged");

		Tide.API.setLogLevel(Tide.API.FATAL);
	},

	validate_properties: function()
	{
		value_of(Tide.API.APP_UPDATE).should_not_be_null();
		value_of(Tide.API.CRITICAL).should_not_be_null();
		value_of(Tide.API.DEBUG).should_not_be_null();
		value_of(Tide.API.EQ).should_not_be_null();
		value_of(Tide.API.ERROR).should_not_be_null();
		value_of(Tide.API.FATAL).should_not_be_null();
		value_of(Tide.API.GT).should_not_be_null();
		value_of(Tide.API.GTE).should_not_be_null();
		value_of(Tide.API.INFO).should_not_be_null();
		value_of(Tide.API.LT).should_not_be_null();
		value_of(Tide.API.LTE).should_not_be_null();
		value_of(Tide.API.MOBILESDK).should_not_be_null();
		value_of(Tide.API.NOTICE).should_not_be_null();
		value_of(Tide.API.RUNTIME).should_not_be_null();
		value_of(Tide.API.SDK).should_not_be_null();
		value_of(Tide.API.TRACE).should_not_be_null();
		value_of(Tide.API.UNKNOWN).should_not_be_null();
		value_of(Tide.API.WARN).should_not_be_null();

		value_of(Tide.API.createDependency).should_be_function();
		value_of(Tide.API.critical).should_be_function();
		value_of(Tide.API.debug).should_be_function();
		value_of(Tide.API.error).should_be_function();
		value_of(Tide.API.fatal).should_be_function();
		value_of(Tide.API.fireEvent).should_be_function();
		value_of(Tide.API.get).should_be_function();
		value_of(Tide.API.getApplication).should_be_function();			 //done
		value_of(Tide.API.getComponentSearchPaths).should_be_function();
		value_of(Tide.API.getInstalledComponents).should_be_function();
		value_of(Tide.API.getInstalledMobileSDKs).should_be_function();
		value_of(Tide.API.getInstalledModules).should_be_function();
		value_of(Tide.API.getInstalledRuntimes).should_be_function();
		value_of(Tide.API.getInstalledSDKs).should_be_function();
		value_of(Tide.API.info).should_be_function();
		value_of(Tide.API.installDependencies).should_be_function();
		value_of(Tide.API.log).should_be_function();
		value_of(Tide.API.notice).should_be_function();
		value_of(Tide.API.readApplicationManifest).should_be_function();
		value_of(Tide.API.addEventListener).should_be_function();
		value_of(Tide.API.set).should_be_function();
		value_of(Tide.API.trace).should_be_function();
		value_of(Tide.API.removeEventListener).should_be_function();
		value_of(Tide.API.warn).should_be_function();
		
		//new 1.0
		value_of(Tide.API.setLogLevel).should_be_function();
		value_of(Tide.API.print).should_be_function();
	},
	// test the application components API
	test_components: function()
	{
		Tide.API.error("Tide.API.getInstalledComponents()");
		// now that the app is finished testing, test the Tide.API runtime calls.
		// this should return a valid list of runtime components installed with this app.		
		var apiInstalledComponents1 = Tide.API.getInstalledComponents();
		
		value_of(apiInstalledComponents1).should_be_object();
		if ( apiInstalledComponents1.length )
		{
			Tide.API.error("Tide.API.getInstalledComponents() contains:");
			for (i=0; i<apiInstalledComponents1.length; i++)
			{
				var item = apiInstalledComponents1[i];
				value_of(item).should_be_object();
				Tide.API.info("apiInstalledComponents["+i+"]= name: '" + item.getName() + 
								  "' type: '"+item.getType()+
								  "' version: '"+item.getVersion()+
								  "' path '" + item.getPath() + "'");
			}
		}
		else 
		{
			Tide.API.error("Tide.API.getInstalledComponents() returned an empty list");
		}		
	},
	// test the application dependancies API
	test_dependancies: function()
	{
		// create a dependancy  what does this mean?  what are we trying to accomplish?
		var dep = Tide.API.createDependency(Tide.API.RUNTIME, "test", "0.0.1", Tide.API.EQ);
		
		value_of(dep).should_be_object();
		value_of(dep.getName).should_be_function();
		value_of(dep.getType).should_be_function();
		value_of(dep.getVersion).should_be_function();
		
		Tide.API.info("processing dependancy '" + dep.getName() + 
						  "' type: '"+dep.getType()+
						  "' version: '"+dep.getVersion()+"'");
	},
	// test the installed runtime component functions
	test_installed_runtime: function()
	{
		Tide.API.error("Tide.API.getInstalledRuntimes()");
		// now that the app is finished testing, test the Tide.API runtime calls.
		// this should return a valid list of runtime components installed with this app.		
		var apiInstalledRuntimes1 = Tide.API.getInstalledRuntimes();
		
		value_of(apiInstalledRuntimes1).should_be_object();
		if ( apiInstalledRuntimes1.length )
		{
			Tide.API.error("Tide.API.getInstalledRuntimes() contains:");
			for (i=0; i<apiInstalledRuntimes1.length; i++)
			{
				var item = apiInstalledRuntimes1[i];
				value_of(item).should_be_object();
			
				Tide.API.info("apiInstalledRuntimes["+i+"] name: '" + item.getName() + 
								  "' type: '"+item.getType()+
								  "' version: '"+item.getVersion()+
								  "' path '" + item.getPath() + "'");
			}
		}
		else 
		{
			Tide.API.error("Tide.API.getInstalledRuntimes() returned an empty list");
		}
	},
	// test the installed modules component functions
	test_installed_modules: function()
	{
		Tide.API.error("Tide.API.getInstalledModules()");
		// now that the app is finished testing, test the Tide.API runtime calls.
		// this should return a valid list of runtime components installed with this app.		
		var apiInstalledModules1 = Tide.API.getInstalledModules();
		
		value_of(apiInstalledModules1).should_be_object();
		if ( apiInstalledModules1.length )
		{
			Tide.API.error("Tide.API.getInstalledModules() contains:");
			for (i=0; i<apiInstalledModules1.length; i++)
			{
				var item = apiInstalledModules1[i];
				value_of(item).should_be_object();
				
				Tide.API.info("apiInstalledModules["+i+"] name: '" + item.getName() + 
								  "' type: '"+item.getType()+
								  "' version: '"+item.getVersion()+
								  "' path '" + item.getPath() + "'");
			}
		}
		else 
		{
			Tide.API.error("Tide.API.getInstalledModules() returned an empty list");
		}
	},

	// test the API SDK functions
	test_api_sdk: function()
	{
		Tide.API.error("Tide.API.getInstalledSDKs()");
		// now that the app is finished testing, test the Tide.API runtime calls.
		// this should return a valid list of runtime components installed with this app.		
		var sdks = Tide.API.getInstalledSDKs();
		value_of(sdks).should_be_array();
		if ( sdks.length )
		{
			Tide.API.error("Tide.API.getInstalledSDKs() contains:");
			for (i=0; i<sdks.length; i++)
			{
				var item = sdks[i];
				value_of(item).should_be_object();
				
				Tide.API.info("apiInstalledSDKs["+i+"] name: '" + item.getName() + 
								  "' type: '"+item.getType()+
								  "' version: '"+item.getVersion()+
								  "' path '" + item.getPath() + "'");
			}
		}
		else 
		{
			Tide.API.error("Tide.API.getInstalledSDKs() returned an empty list");
		}

		// test the objects in API		
		var app = Tide.API.getApplication();
	  
		value_of(app).should_not_be_null();
		if ( app ) 
		{
			value_of(app).should_be_object();

			// every module, runtime object and SDK should have a component entry		
			var components = app.getComponents();
			value_of(components).should_be_array();
			
			// once we have the list of components from the application 
			// object, we need to  verify that the lists are the same 
			// that we get through the application object.

			Tide.API.info("checking installed SDKs[] ");
			var bFound = false;
			for (j=0; j<sdks.length; j++ )
			{
				var module = sdks[j];
				Tide.API.info("processing SDK component '" + module.getName() + 
								  "' type: '"+module.getType()+
								  "' version: '"+module.getVersion()+
								  "' path '" + module.getPath() + "'");
				
				
				for ( i=0; i<components.length; i++ )
				{
					var am = components[i];
					value_of(am).should_not_be_null();
					
					Tide.API.info("processing component '" + am.getName() + 
									  "' type: '"+am.getType()+
									  "' version: '"+am.getVersion()+
									  "' path '" +am.getPath() + "'");

					if ( module.getName() == am.getName() &&
						 module.getType() == am.getType() &&
						 module.getPath() == am.getPath())
					{
						Tide.API.trace("match SDK  "+module.getName() +" to component entry");
						bFound = true;
						break;
					}
				}
			}
			
			if ( !bFound )
			{
				// fail the test if we don't find a value.						
				Tide.API.fatal("failed to match SDK object to list of loaded components");
				// this is not a real bug.  this is only meant for developer environments.
			}
		}
	},
	
	test_api_installed_mobile_sdks: function()
	{
		// test the objects in API		
		var app = Tide.API.getApplication();
		value_of(app).should_be_object();

		// every module, runtime object and SDK should have a component entry		
		var components = app.getComponents();
		value_of(components).should_be_array();
		
		// once we have the list of components from the application 
		// object, we need to  verify that the lists are the same 
		// that we get through the application object.
		var mobileSDKs = Tide.API.getInstalledMobileSDKs();
		value_of(mobileSDKs).should_be_array();

		var bFound = false;
		for (j=0; j<mobileSDKs.length; j++ )
		{
			var module = mobileSDKs[j];
			Tide.API.info("processing mobile SDK module '" + module.getName() + 
							  "' type: '"+module.getType()+
							  "' version: '"+module.getVersion()+
							  "' path '" + module.getPath() + "'");
			
			for ( i=0; i<components.length; i++ )
			{
				if ( module.getName() == components[i].getName() &&
					 module.getType() == components[i].getType() &&
					 module.getPath() == components[i].getPath())
				{
					Tide.API.trace("match avialable mobile SDK  "+module.getName() +" to components entry");
					bFound = true;
					break;
				}
			}
			
			if ( !bFound )
			{
				// don't fail the test if we don't find a value.  this is really just for Tide development.
				Tide.API.warn("failed to match mobile SDK object to list of loaded components");
				// this is not a real bug.  this is only meant for developer environments.
			}
		}
	},
	// test the api arguments.
	test_api_arguments: function()
	{
		// test the objects in API		
		var app = Tide.API.getApplication();
	  
		value_of(app).should_not_be_null();
		if ( app ) 
		{
			value_of(app).should_be_object();
			var argv = app.getArguments();

			if ( argv )
			{
				value_of(argv).should_be_object();
				value_of(argv.length).should_not_be(0);
				
				// print out all the arguments to drillbit.
				for (i=0; i<argv.length; i++)
				{
					Tide.API.info("argv["+i+"] = "+argv[i]);
				}
				
				var bHasit = app.hasArgument("results");
				value_of(bHasit).should_be_true();
				
				var results = app.getArgumentValue("results");
				value_of(results).should_not_be_null();
			}
		}
	},
	// test the module component functions
	test_api_module: function()
	{
		// test the objects in API		
		var app = Tide.API.getApplication();
	  
		value_of(app).should_not_be_null();
		if ( app ) 
		{
			value_of(app).should_be_object();
			
			var pid = app.getPID();
			
			// isCurrent is true when we are the currently running app
			if (app.isCurrent())
			{
				// the PID should not be null when we are the current app
				value_of(pid).should_not_be_null();
				Tide.API.info("Application PID = "+pid);
			}
			else
			{
				// the pid should be null when we are not the current running app.				
				// I don't think we should ever get here in the unit test since 
				// we should always be the current app.
				value_of(pid).should_be_null();
			}
		}
	},
	// test the application path functions
	test_api_component_Search_Paths: function()
	{
	    var componentSearchPaths = Tide.API.getComponentSearchPaths();
	    
	    value_of(componentSearchPaths).should_be_object();
	    value_of(componentSearchPaths.length).should_not_be(0);
	    
	    
        Tide.API.info("dump component search paths")
	    for (i=0; i<componentSearchPaths.length; i++)
	    {
	        Tide.API.info(componentSearchPaths[i]);
	    }
	},
	
	test_api_events_as_async: function(callback)
	{
		// create an event
		var w = Tide.API.addEventListener("foo", function()
		{
			callback.passed();
		});

		// make sure we have a callback for it
		value_of(w).should_be_function();

		// fire it off
		Tide.API.fireEvent("foo");

		// unregister the event when we are done.
		Tide.API.removeEventListener("foo", w);

	},
	
	test_api_global_object: function()
	{
		// set a global object
		Tide.API.set("foo", "bar" );
		
		value_of(Tide.API.foo).should_be_string();
		value_of(Tide.API.foo).should_be("bar");
		
		var str = Tide.API.get("foo");
		
		value_of(str).should_be_string();
		value_of(str).should_be("bar");
	},

	test_api_run_on_main: function()
	{
		function test(value) {
			Tide.API.foo = value;
		}

		Tide.API.runOnMainThread(test, "works!");
		value_of(Tide.API.foo).should_be("works!");
	}
});
