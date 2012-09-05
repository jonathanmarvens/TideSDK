describe("ti.App tests",
{
	validate_app: function()
	{
		value_of(Tide.platform).should_be_one_of(['win32','osx','linux']);
		value_of(Tide.version).should_be_string();
		
		value_of(Tide.App.getID()).should_be('com.Tideapp.unittest');
		value_of(Tide.App.getName()).should_be('foobar');
		value_of(Tide.App.getVersion()).should_be('1.2');
		value_of(Tide.App.getPublisher()).should_be('yoy');
		value_of(Tide.App.getURL()).should_be('blah.com');
		value_of(Tide.App.getCopyright()).should_be('2010');
		value_of(Tide.App.getDescription()).should_be('cool like dat');
		value_of(Tide.App.getGUID()).should_be('CF0D2CB7-B4BD-488F-9F8E-669E6B53E0C4');

		// No default icon set for the application.
		var icon = Tide.App.getIcon();
		value_of(icon).should_be_null();

		value_of(Tide.App.exit).should_be_function();
		value_of(Tide.App.loadProperties).should_be_function();
		value_of(Tide.App.path).should_not_be_null();
		value_of(Tide.App.arguments).should_not_be_null();
		value_of(Tide.App.Properties).should_be_object();
		
		value_of(Tide.App.home).should_not_be_null();
		value_of(Tide.App.stdout).should_be_function();
		value_of(Tide.App.stderr).should_be_function();
		
		// this should be the default stream if not specified in the manifest
		value_of(Tide.App.getStreamURL()).should_be('https://api.appcelerator.net/p/v1');
		// test passing arg
		value_of(Tide.App.getStreamURL('foo')).should_be('https://api.appcelerator.net/p/v1/foo');
		// test passing multiple args
		value_of(Tide.App.getStreamURL('foo','bar')).should_be('https://api.appcelerator.net/p/v1/foo/bar');
	},
	
	//comment out for now, this test function causes the app test to timeout in win32,
	test_system_properties: function()
	{
		// test type conversion and parsing of system properties embedded in tiapp.xml
		value_of(Tide.App.getSystemProperties()).should_be_object();
		var sysProps = Tide.App.getSystemProperties();
		
		value_of(sysProps.getString("teststring")).should_be("stringvalue");
		value_of(sysProps.getInt("testint")).should_be(1);
		value_of(sysProps.getDouble("testdouble")).should_be(1.23);
		value_of(sysProps.getString("testdefaultstring")).should_be("stringvalue");
		value_of(sysProps.getInt("badint")).should_be(0);
		value_of(sysProps.getDouble("baddouble")).should_be(0);
	},
	
	test_create_properties_object: function()
	{
		var props = Tide.App.createProperties();
		value_of(props).should_be_object();

		value_of(props.getBool).should_be_function();
		value_of(props.getInt).should_be_function();
		value_of(props.getList).should_be_function();
		value_of(props.getDouble).should_be_function();
		value_of(props.setString).should_be_function();
		value_of(props.setBool).should_be_function();
		value_of(props.setInt).should_be_function();
		value_of(props.setList).should_be_function();
		value_of(props.setDouble).should_be_function();
		value_of(props.setString).should_be_function();
		value_of(props.hasProperty).should_be_function();
		value_of(props.listProperties).should_be_function();
		value_of(props.saveTo).should_be_function();
	},
	
	test_create_properties: function()
	{
		var props2 = Tide.App.createProperties({
			"val1": true,
			"val2": 1.1,
			"val3": ['a', 'b', 'c'],
			"val4": "123"
		});
		
		value_of(props2).should_be_object();
		
		value_of(props2.listProperties()).should_match_array(["val1","val2","val3","val4"]);
		value_of(props2.getBool("val1")).should_be_true();
		value_of(props2.getDouble("val2")).should_be(1.1);
		
		var val3 = props2.getList("val3");
		value_of(val3).should_not_be_null();
		value_of(val3).should_be_array();
		
		value_of(props2.getList("val3")).should_match_array(['a','b','c']);
		value_of(props2.getString("val4")).should_be("123");
		
		var TFS = Tide.Filesystem;
		var sep = TFS.getSeparator();
		var appdir = TFS.getApplicationDataDirectory();
		var path = appdir+sep+"_testing.properties";
		
		props2.saveTo(path);
		value_of(TFS.getFile(path).exists()).should_be_true();
	},

	test_remove_properties: function()
	{
		var props = Tide.App.createProperties({
			"val1": true,
			"val2": 1.1,
			"val3": ['a', 'b', 'c'],
			"val4": "123"
		});

		value_of(props.hasProperty('val1')).should_be_true();
		props.removeProperty('val1');
		value_of(props.hasProperty('val1')).should_be_false();
		props.setInt('val1', 42);
		value_of(props.hasProperty('val1')).should_be_true();
		value_of(props.getInt('val1')).should_be(42);
	},

	test_app_URLToPath: function ()
	{
	    // get the fully qualified absolute path to the properties.
		var path = Tide.App.appURLToPath("app://app.properties");
		value_of(path).should_be_string();
		
		// get the application object
		var app = Tide.API.getApplication();
		value_of(app).should_not_be_null();

		// the application object will give us the exe path
		var exePath = app.getExecutablePath();
		value_of(exePath).should_be_string();

		// for this test, the exe path should be a substring of the path
		// returned by appURLToPath()
		var index = path.indexOf(exePath);
		value_of(index).should_not_be(-1);
		
		// Lighthouse issue #90: Make sure app URLs with the appid in the host are stripped
		var url = Tide.UI.currentWindow.getURL();
		var urlNoHost = "app://index.html";
		var urlPath = Tide.App.appURLToPath(url);
		value_of(urlPath).should_be(Tide.App.appURLToPath(urlNoHost));
	},

	test_app_loadproperties: function ()
	{
		var props = Tide.App.loadProperties(Tide.App.appURLToPath("app://app.properties"));
		value_of(props).should_be_object();
		value_of(props.getBool("trueval")).should_be_true();
		value_of(props.getBool("falseval")).should_be_false();
		value_of(props.getInt("numval")).should_be(1);
		value_of(props.getString("stringval")).should_be("hey this is just a string");
		value_of(props.getDouble("doubleval")).should_be(1.1);
		value_of(props.getList("listval")).should_match_array(["entry1","entry2","entry3"]);
	},
	
	test_app_arguments: function()
	{
		value_of(Tide.App.arguments).should_be_array();
		// this is specific to the test harness args
		value_of(Tide.App.arguments.length).should_be(6); 

		Tide.API.debug("arguments[0] "+Tide.App.arguments[0]);

		// get the application object
		var app = Tide.API.getApplication();
		value_of(app).should_not_be_null();

		var argv = app.getArguments();
		value_of(argv).should_be_array();

		// find "a" shared part of the path string so we can search for it inside 
		// the Ti.App.arguments.  These arguments ARE NOT the same as ti.api.application.argv[][]
		// we can't hard code any paths due to the differences in platforms.
		var subPath = argv[0].substr(0,argv[0].search(app.getName()));

		// argv[0] is the fully qualified name and path to the exe
		var index = Tide.App.arguments[0].indexOf(subPath);
		value_of(index).should_not_be(-1);
	},
	
	test_app_home_property: function()
	{
		value_of(Tide.App.home).should_not_be_null();
		Tide.API.debug("home is "+Tide.App.home);
		Tide.API.debug("Tide.App.arguments[0] is "+Tide.App.arguments[0]);

		// get the application object
		var app = Tide.API.getApplication();
		value_of(app).should_not_be_null();

		var argv = app.getArguments();
		value_of(argv).should_be_array();

		// find "a" shared part of the path string so we can search for it inside 
		// the Ti.App.arguments.  These arguments ARE NOT the same as ti.api.application.argv[][]
		// we can't hard code any paths due to the differences in platforms.
		var subPath = argv[0].substr(0,argv[0].search(app.getName()));

		// argv[0] is the fully qualified name and path to the exe
		var index = Tide.App.home.indexOf(subPath);
		value_of(index).should_not_be(-1);
	},

	test_app_path_property: function()
	{
		value_of(Tide.App.path).should_not_be_null();
		Tide.API.debug("path is "+Tide.App.path);

		var index = Tide.App.path.indexOf(Tide.App.home);
		value_of(index).should_not_be(-1);
	},
});
