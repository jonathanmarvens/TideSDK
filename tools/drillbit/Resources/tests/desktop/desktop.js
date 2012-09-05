describe("Desktop tests", {
	test_desktop_functions: function()
	{
		value_of(Tide.Desktop.openApplication).should_be_function();
		value_of(Tide.Desktop.openURL).should_be_function();
		value_of(Tide.Desktop.takeScreenshot).should_be_function();
	},
	test_screenshot: function()
	{
		// not implemented in linux yet
		if (Tide.platform == "linux") return;
		
		var invalid_args = false;
		try {
			Tide.Desktop.takeScreenshot();
		} catch (E) {
			invalid_args = true;
		}
		
		value_of(invalid_args).should_be_true();
		
		var ext = "png";
		if (Tide.platform == "win32") { ext = "bmp"; }
		
		var appdir = Tide.Filesystem.getApplicationDataDirectory();
		var file = Tide.Filesystem.getFile(appdir, "screenshot."+ext);
		Tide.Desktop.takeScreenshot(file.nativePath());
		
		value_of(file.exists()).should_be_true();
		
	}
});
