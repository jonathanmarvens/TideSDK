describe("Ti.Filesystem tests",{
	before_all:function()
	{
		// clean up testing folder if needed
		var base = Tide.Filesystem.getFile(Tide.Filesystem.getApplicationDataDirectory(), "unittest_filesystem");
		if(base.exists() && base.isDirectory()) {
			base.deleteDirectory(true);
		}
		else if(base.exists() && base.isFile()) {
			base.deleteFile();
		}
	
		base.createDirectory();
		
		this.base = base;

		this.createDirTree = function(base,name) {
			var dir = Tide.Filesystem.getFile(base, name);
			if(! dir.exists()) {
				dir.createDirectory();
			}

			var file1 = Tide.Filesystem.getFileStream(dir, "file1.txt");
			var file2 = Tide.Filesystem.getFileStream(dir, "file2.txt");
			var subDir1 = Tide.Filesystem.getFile(dir, "subDir1");
			subDir1.createDirectory();
			var file3 = Tide.Filesystem.getFileStream(subDir1, "file3.txt");

			file1.open(Tide.Filesystem.MODE_WRITE);
			file1.write("Text for file1");
			file1.close();

			file2.open(Tide.Filesystem.MODE_WRITE);
			file2.write("Text for file2");
			file2.close();

			file3.open(Tide.Filesystem.MODE_WRITE);
			file3.write("Text for file3");
			file3.close();
		};


	},
	
	filesystem_basic_static_properties: function()
	{
		var methods = ['getFile','getFileStream','getApplicationDataDirectory'];
		
		for (var c=0;c<methods.length;c++)
		{
			var method = methods[c];
			value_of(Tide.Filesystem[method]).should_be_function();
		}
	},
	
	other_props:function()
	{
		value_of(Tide.Filesystem.getLineEnding).should_be_function();
		value_of(Tide.Filesystem.getSeparator).should_be_function();
		value_of(Tide.Filesystem.MODE_READ).should_not_be_null();
		value_of(Tide.Filesystem.MODE_WRITE).should_not_be_null();
		value_of(Tide.Filesystem.MODE_APPEND).should_not_be_null();
				
		value_of(Tide.Filesystem.getLineEnding()).should_not_be_null();
		value_of(Tide.Filesystem.getSeparator()).should_not_be_null();
	},
	
	get_file: function()
	{
		var f = Tide.Filesystem.getFile(this.base, "getFileTest.txt");
		value_of(f).should_not_be_null();
		// we only created a path to a file, not a real file.
		value_of(f.exists()).should_be_false();
	},
	
	get_file_stream:function()
	{
		var fs = Tide.Filesystem.getFileStream(this.base, "getFileStreamTest.txt");
		value_of(fs).should_not_be_null();
	},
	
	temp_file:function()
	{
		value_of(Tide.Filesystem.createTempFile).should_be_function();
		
		var f = Tide.Filesystem.createTempFile();
		value_of(f).should_not_be_null();
		value_of(f.exists()).should_be_true();
		value_of(f.isFile()).should_be_true();
		value_of(f.isDirectory()).should_be_false();
	},
	
	temp_directory:function()
	{
		value_of(Tide.Filesystem.createTempDirectory).should_be_function();
		
		var f = Tide.Filesystem.createTempDirectory();
		value_of(f).should_not_be_null();
		value_of(f.exists()).should_be_true();	
		value_of(f.isFile()).should_be_false();
		value_of(f.isDirectory()).should_be_true();
	},
	
	common_directories:function()
	{
		value_of(Tide.Filesystem.getProgramsDirectory).should_be_function();
		value_of(Tide.Filesystem.getApplicationDirectory).should_be_function();
		value_of(Tide.Filesystem.getRuntimeHomeDirectory).should_be_function();
		value_of(Tide.Filesystem.getResourcesDirectory).should_be_function();
		value_of(Tide.Filesystem.getDesktopDirectory).should_be_function();
		value_of(Tide.Filesystem.getDocumentsDirectory).should_be_function();
		value_of(Tide.Filesystem.getUserDirectory).should_be_function();
		
		value_of(Tide.Filesystem.getProgramsDirectory()).should_not_be_null();
		value_of(Tide.Filesystem.getApplicationDirectory()).should_not_be_null();
		value_of(Tide.Filesystem.getRuntimeHomeDirectory()).should_not_be_null();
		value_of(Tide.Filesystem.getResourcesDirectory()).should_not_be_null();
		value_of(Tide.Filesystem.getDesktopDirectory()).should_not_be_null();
		value_of(Tide.Filesystem.getDocumentsDirectory()).should_not_be_null();
		value_of(Tide.Filesystem.getUserDirectory()).should_not_be_null();
	},
	
	test_ProgramsDirectory:function()
	{
		value_of(Tide.Filesystem.getProgramsDirectory).should_be_function();
		value_of(Tide.Filesystem.getProgramsDirectory()).should_not_be_null();
		
		var folder = Tide.Filesystem.getProgramsDirectory();
		value_of(folder).should_not_be_null();
		value_of(folder.exists()).should_be_true();	
		value_of(folder.isFile()).should_be_false();
		value_of(folder.isDirectory()).should_be_true();
		
		Tide.API.debug("Tide.Filesystem.getProgramsDirectory="+folder.nativePath());

		var progFileFolder = null;
				
		if ( Tide.platform == 'win32' )
		{
			// in windows we have an environment variable we can check
			// for the program files directory.
			
			progFileFolder = Tide.API.getEnvironment()["PROGRAMFILES"];
			Tide.API.debug("windows env PROGRAMFILES="+progFileFolder);
		}
		else if ( Tide.platform == 'osx' )
		{	
			// on the Mac, this should be hard coded to '/Applications' according to the source code.
			progFileFolder = "/Applications";
		}
		else if (Tide.platform == 'linux' )
		{
			// currently under linux we are hard coded to this path.  this could change
			progFileFolder = "/usr/local/bin";
		}
		else 
		{
			failed("unknown platform");
		}
		value_of(progFileFolder.indexOf(folder.nativePath())).should_not_be(-1);
	},
	
	test_ApplicationDirectory: function()
	{
		value_of(Tide.Filesystem.getApplicationDirectory).should_be_function();
		value_of(Tide.Filesystem.getApplicationDirectory()).should_not_be_null();
		
		var f = Tide.Filesystem.getApplicationDirectory();
		Tide.API.debug("application folder"+f.nativePath());
		value_of( f == Tide.App.home ).should_be_true();		
	},
	
	test_RuntimeHomeDirectory: function()
	{
		value_of(Tide.Filesystem.getRuntimeHomeDirectory).should_be_function();
		value_of(Tide.Filesystem.getRuntimeHomeDirectory()).should_not_be_null();

		var f = Tide.Filesystem.getRuntimeHomeDirectory();
		Tide.API.debug("runtime home folder"+f.nativePath());
		
		var componentPaths = Tide.API.getComponentSearchPaths()
		value_of(componentPaths).should_be_array();
		
		var bfound = false;
		
		for (i=0; i< componentPaths.length; i++ )		
		{
			if ( f == componentPaths[i] )
			{
				Tide.API.debug("runtime reported path = "+componentPaths[i].toString());
				bfound = true;
				break;
			}
		}
		value_of( bfound ).should_be_true();
	},
	
	test_ResourcesDirectory: function()
	{
		value_of(Tide.Filesystem.getResourcesDirectory).should_be_function();
		value_of(Tide.Filesystem.getResourcesDirectory()).should_not_be_null();

		var f = Tide.Filesystem.getResourcesDirectory();
		Tide.API.debug("Resources folder"+f.nativePath());
		
		value_of( f.nativePath().indexOf(Tide.Filesystem.getApplicationDirectory())).should_not_be(-1);
	},
	test_DesktopDirectory: function()
	{
		value_of(Tide.Filesystem.getDesktopDirectory).should_be_function();
		value_of(Tide.Filesystem.getDesktopDirectory()).should_not_be_null();

		var desktop = Tide.Filesystem.getDesktopDirectory();
		value_of(desktop).should_not_be_null();

		var userHome = null;		
		// we have an environment variable we can check
		// for the user home directory.  then we can make sure it's a substring
		// of the desktop folder path
		if ( Tide.platform == 'win32' )
		{
			userHome = Tide.API.getEnvironment()["USERPROFILE"];
			Tide.API.debug(Tide.platform+" env USERPROFILE="+userHome);
		}
		else 
		{	
			// on the Mac, this should be hard coded to '~/desktop' according to the source code.
			// on linux, this will be hard coded in a similar fashion
			userHome = Tide.API.getEnvironment()["HOME"];
			Tide.API.debug(Tide.platform+" env HOME="+userHome);
		}
		var path = desktop.nativePath();
		value_of(path.indexOf(userHome)).should_not_be(-1);
	},
	test_DocumentsDirectory: function()
	{
		value_of(Tide.Filesystem.getDocumentsDirectory).should_be_function();
		value_of(Tide.Filesystem.getDocumentsDirectory()).should_not_be_null();
		
		var documents = Tide.Filesystem.getDesktopDirectory();
		value_of(documents).should_not_be_null();

		var userHome = null;		
		// we have an environment variable we can check
		// for the user home directory.  then we can make sure it's a substring
		// of the desktop folder path
		if ( Tide.platform == 'win32' )
		{
			userHome = Tide.API.getEnvironment()["USERPROFILE"];
			Tide.API.debug(Tide.platform+" env USERPROFILE="+userHome);
		}
		else 
		{	
			// on the Mac, this should be hard coded to '~/desktop' according to the source code.
			// on linux, this will be hard coded in a similar fashion
			userHome = Tide.API.getEnvironment()["HOME"];
			Tide.API.debug(Tide.platform+" env HOME="+userHome);
		}
		var path = documents.nativePath();
		value_of(path.indexOf(userHome)).should_not_be(-1);
	},
	test_UserDirectory: function()
	{
		value_of(Tide.Filesystem.getUserDirectory).should_be_function();
		value_of(Tide.Filesystem.getUserDirectory()).should_not_be_null();
		
		var f = Tide.Filesystem.getUserDirectory();
		value_of(f).should_not_be_null();
		Tide.API.debug("user home folder ="+f.nativePath());

		var userHome = null;		
		if ( Tide.platform == 'win32'  ) 
		{
			// in windows we have an environment variable we can check
			// for the program files directory.
			userHome = Tide.API.getEnvironment()["USERPROFILE"];
			Tide.API.debug(Tide.platform +" environment USERPROFILE="+userHome);
		}
		else
		{	
			// on the Mac, this should be hard coded to '~/desktop' according to the source code.
			userHome = Tide.API.getEnvironment()["HOME"];
			Tide.API.debug(Tide.platform +" environment HOME="+userHome);
		}
		value_of(f.nativePath()).should_be(userHome);
	},
	
	root_directories:function()
	{
		value_of(Tide.Filesystem.getRootDirectories).should_be_function();
		
		var rootDirs = Tide.Filesystem.getRootDirectories();
		value_of(rootDirs).should_not_be_null();
		value_of(rootDirs.length>0).should_be_true();
		var rootDirFirst = rootDirs[0];
		value_of(rootDirFirst).should_be_object();
		try {
			value_of(rootDirFirst.isDirectory()).should_be_true();
		} catch (e) {
			// swallow accesss errors here, silly windows
			if (e.toString().indexOf("File access error") == -1) {
				throw e;
			}
		}
	},
	
	async_copy:function()
	{
		var fromDir = Tide.Filesystem.getFile(this.base, "ayncCopyFrom");
		var toDir = Tide.Filesystem.getFile(this.base, "asynCopyTo");
		this.createDirTree(this.base,"ayncCopyFrom");
		Tide.Filesystem.asyncCopy(fromDir,toDir,function() {
			
			value_of(AsyncCopy.running).should_be_true();
			
			var listings = toDir.getDirectoryListing();
			value_of(listings).should_not_be_null();
			value_of(listings.length==3).should_be_true();
			
			var toSubDir1 = Tide.Filesystem.getFile(fromDir, "subDir1");
			value_of(toSubDir1.isDirectory()).should_be_true();
			
			var subDirListings = toSubDir1.getDirectoryListing();
			value_of(subDirListings).should_not_be_null();
			value_of(subDirListings.length==1).should_be_true();
		});	
	},
	
	test_line_endings: function()
	{
		value_of(Tide.Filesystem.getLineEnding).should_be_function();
		value_of(Tide.Filesystem.getLineEnding()).should_not_be_null();
		
        if ( Tide.platform == 'win32' )
        {
            // this is weird, we need to investigate further.
            value_of(Tide.Filesystem.getLineEnding()).should_be("\n");
        }
        else 
        {
            value_of(Tide.Filesystem.getLineEnding()).should_be("\n");
        }
	},
	
	test_separator: function ()
	{
		value_of(Tide.Filesystem.getSeparator).should_be_function();
		value_of(Tide.Filesystem.getSeparator()).should_not_be_null();
		
        if ( Tide.platform == 'win32' )
        {
            value_of(Tide.Filesystem.getSeparator()).should_be("\\");
        }
        else 
        {
            value_of(Tide.Filesystem.getSeparator()).should_be("/");
        }
	}
});

