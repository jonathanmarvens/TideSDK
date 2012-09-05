describe("UI.Clipboard",{
	test_clipboard_text_data_set_twice: function()
	{
		Tide.UI.Clipboard.setData("text/plain", "blahblah");
		var data = Tide.UI.Clipboard.getData("text/plain");
		value_of(data).should_be("blahblah");

		Tide.UI.Clipboard.setData("text/plain", "blahblah");
		var data = Tide.UI.Clipboard.getData("text/plain");
		value_of(data).should_be("blahblah");
	},
	test_clipboard_methods: function()
	{
		value_of(Tide.UI.Clipboard).should_be_object();
		value_of(Tide.UI.Clipboard.setData).should_be_function();
		value_of(Tide.UI.Clipboard.getData).should_be_function();
		value_of(Tide.UI.Clipboard.clearData).should_be_function();
		value_of(Tide.UI.Clipboard.setText).should_be_function();
		value_of(Tide.UI.Clipboard.getText).should_be_function();
	},
	test_clipboard_text_data: function()
	{
		Tide.UI.Clipboard.setData("text/plain", "blahblah");
		var data = Tide.UI.Clipboard.getData("text/plain");
		value_of(data).should_be("blahblah");

		Tide.UI.Clipboard.setData("text/plain", "");
		value_of(Tide.UI.Clipboard.hasText()).should_be_false();
		var data = Tide.UI.Clipboard.getData("text/plain");
		value_of(data).should_be("");

		Tide.UI.Clipboard.setData("text/plain", "crazy utf8 ‽‽‽ ⸮⸮⸮ woohoo");
		data = Tide.UI.Clipboard.getData("text/plain");
		value_of(data).should_be("crazy utf8 ‽‽‽ ⸮⸮⸮ woohoo");
	},
	test_clipboard_text: function()
	{
		Tide.UI.Clipboard.setText("blahblah");
		var data = Tide.UI.Clipboard.getText();
		value_of(data).should_be("blahblah");

		Tide.UI.Clipboard.setText("");
		value_of(Tide.UI.Clipboard.hasText()).should_be_false();
		data = Tide.UI.Clipboard.getText();
		value_of(data).should_be("");

		Tide.UI.Clipboard.setText("crazy utf8 ‽‽‽ ⸮⸮⸮ woohoo");
		data = Tide.UI.Clipboard.getText();
		value_of(data).should_be("crazy utf8 ‽‽‽ ⸮⸮⸮ woohoo");
	},
	test_clipboard_clear_data: function()
	{
		Tide.UI.Clipboard.setText("blahblah");
		Tide.UI.Clipboard.setData("text/plain", "blahblah");
		Tide.UI.Clipboard.clearData("text/plain");

		var data = Tide.UI.Clipboard.getText();
		value_of(data).should_be("");

		data = Tide.UI.Clipboard.getData("text/plain");
		value_of(data).should_be("");
	},
	test_clipboard_clear_text: function()
	{
		Tide.UI.Clipboard.setText("blahblah");
		Tide.UI.Clipboard.setData("text/plain", "blahblah");

		Tide.UI.Clipboard.clearText();

		var data = Tide.UI.Clipboard.getText();
		value_of(data).should_be("");

		data = Tide.UI.Clipboard.getData("text/plain");
		value_of(data).should_be("");

		// TODO: This should eventually set other data types on the
		// clipboard and ensure that they are *not* cleared.
	},
	test_clipboard_has_text: function()
	{
		Tide.UI.Clipboard.setText("blahblah");
		value_of(Tide.UI.Clipboard.hasText()).should_be_true();

		Tide.UI.Clipboard.clearData("text/plain");
		value_of(Tide.UI.Clipboard.hasText()).should_be_false();

		Tide.UI.Clipboard.setText("blahblah");
		value_of(Tide.UI.Clipboard.hasText()).should_be_true();

		Tide.UI.Clipboard.clearData("text/plain");
		value_of(Tide.UI.Clipboard.hasText()).should_be_false();

		Tide.UI.Clipboard.setText("");
		value_of(Tide.UI.Clipboard.hasText()).should_be_false();
	},
	test_clipboard_urilist_data: function()
	{
		if (Tide.platform == "win32") /* TODO: implement uri-list in win32 */ return;
		
		var uri1 = Tide.Filesystem.getApplicationDirectory().toURL();
		var uri2 = Tide.Filesystem.getResourcesDirectory().toURL();
		var uri3 = Tide.Filesystem.getDesktopDirectory().toURL();
		var uristring = uri1 + "\n" + uri2 + "\n" + uri3;
		Tide.UI.Clipboard.setData("text/uri-list", uristring);
		var data = Tide.UI.Clipboard.getData("text/uri-list");
		value_of(data).should_be_array();
		value_of(data.length).should_be(3);
		value_of(data[0].indexOf(uri1)).should_be(0); // A trailing slash may have been added
		value_of(data[1].indexOf(uri2)).should_be(0); // A trailing slash may have been added
		value_of(data[2].indexOf(uri3)).should_be(0); // A trailing slash may have been added

		Tide.UI.Clipboard.setData("text/uri-list", null);
		value_of(Tide.UI.Clipboard.hasData("text/uri-list")).should_be_false();
		var data = Tide.UI.Clipboard.getData("text/uri-list");
		value_of(data).should_be_array();
		value_of(data.length).should_be(0);

		Tide.UI.Clipboard.setData("text/uri-list", [uri1, uri2, uri3]);
		var data = Tide.UI.Clipboard.getData("text/uri-list");
		value_of(data).should_be_array();
		value_of(data.length).should_be(3);
		value_of(data[0].indexOf(uri1)).should_be(0); // A trailing slash may have been added
		value_of(data[1].indexOf(uri2)).should_be(0); // A trailing slash may have been added
		value_of(data[2].indexOf(uri3)).should_be(0); // A trailing slash may have been added

		Tide.UI.Clipboard.setData("text/uri-list", null);
		value_of(Tide.UI.Clipboard.hasData("text/uri-list")).should_be_false();
		var data = Tide.UI.Clipboard.getData("text/uri-list");
		value_of(data).should_be_array();
		value_of(data.length).should_be(0);
	},
	test_clipboard_clear_uri_list: function()
	{
		if (Tide.platform == "win32") /* TODO: implement uri-list in win32 */ return;
	
		var uri1 = Tide.Filesystem.getApplicationDirectory().toURL();
		var uri2 = Tide.Filesystem.getResourcesDirectory().toURL();
		var uri3 = Tide.Filesystem.getDesktopDirectory().toURL();
		var uristring = uri1 + "\n" + uri2 + "\n" + uri3;
		Tide.UI.Clipboard.setData("text/uri-list", uristring);
		var data = Tide.UI.Clipboard.getData("text/uri-list");
		value_of(data).should_be_array();
		value_of(data.length).should_be(3);
		value_of(data[0].indexOf(uri1)).should_be(0); // A trailing slash may have been added
		value_of(data[1].indexOf(uri2)).should_be(0); // A trailing slash may have been added
		value_of(data[2].indexOf(uri3)).should_be(0); // A trailing slash may have been added

		Tide.UI.Clipboard.clearData("text/uri-list");
		value_of(Tide.UI.Clipboard.hasData("text/uri-list")).should_be(false);
	},
	test_clipboard_url_data: function()
	{
		if (Tide.platform == "win32") /* TODO: implement uri-list in win32 */ return;
		
		Tide.UI.Clipboard.setData("url", "http://www.google.com");
		var data = Tide.UI.Clipboard.getData("url");
		value_of(data).should_be("http://www.google.com");
		value_of(Tide.UI.Clipboard.hasData("url")).should_be(true);

		Tide.UI.Clipboard.setData("url", "http://www.yahoo.com");
		data = Tide.UI.Clipboard.getData("url");
		value_of(data).should_be("http://www.yahoo.com");
		value_of(Tide.UI.Clipboard.hasData("url")).should_be(true);

		Tide.UI.Clipboard.setData("url", null);
		value_of(Tide.UI.Clipboard.hasData("url")).should_be_false();
		data = Tide.UI.Clipboard.getData("url");
		value_of(data).should_be("");

		Tide.UI.Clipboard.setData("url", ["http://www.google.com", "http://www.yahoo.com"]);
		data = Tide.UI.Clipboard.getData("url");
		value_of(data).should_be("http://www.google.com");
		value_of(Tide.UI.Clipboard.hasData("url")).should_be_true();

		Tide.UI.Clipboard.setData("url", "");
		value_of(Tide.UI.Clipboard.hasData("url")).should_be_false();
		data = Tide.UI.Clipboard.getData("url");
		value_of(data).should_be("");
	},
	test_clipboard_clear_url_list: function()
	{
		if (Tide.platform == "win32") /* TODO: implement uri-list in win32 */ return;
		
		Tide.UI.Clipboard.setData("url", "http://www.yahoo.com");
		var data = Tide.UI.Clipboard.getData("url");
		value_of(data).should_be("http://www.yahoo.com");

		Tide.UI.Clipboard.clearData("url");
		value_of(Tide.UI.Clipboard.hasData("url")).should_be(false);
	},
});
