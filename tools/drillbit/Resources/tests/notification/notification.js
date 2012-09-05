describe("Notification tests",
{

	test_notification_object: function()
	{
		var wnd = Tide.UI.createNotification(parent.window);
		
		value_of(wnd.hide).should_be_function();
		value_of(wnd.setDelay).should_be_function();
		value_of(wnd.setIcon).should_be_function();
		value_of(wnd.setMessage).should_be_function();
		value_of(wnd.setTitle).should_be_function();
		value_of(wnd.show).should_be_function();	   
		value_of(wnd).should_be_object();	
	},
	
	test_it_with_old_icon_as_async: function(callback)
	{
		value_of(Tide.UI.createNotification).should_be_function();
		
		// create a notification object
		var parent = Tide.UI.getCurrentWindow();
		var wnd = Tide.UI.createNotification(parent.window);
		wnd.setTitle("title");
		wnd.setMessage("this is a message with the old drillbit icon");
		wnd.setIcon("app://logo_large.png");
		wnd.setDelay(5000);
		
		
		Tide.API.debug("attempting to show the notification");
		wnd.show();

		timer = setTimeout(function()
		{
			try 
			{
				Tide.API.debug("hiding the notification");
				wnd.hide();
				callback.passed();
			}
			catch(e)
			{
				Tide.API.debug("hiding the notification failed with an exception");
				callback.failed();
			}
		},1000);
	},

	test_it_with_new_icon_as_async: function(callback)
	{
		value_of(Tide.UI.createNotification).should_be_function();
		
		// create a notification object
		var parent = Tide.UI.getCurrentWindow();
		var wnd = Tide.UI.createNotification(parent.window);
		wnd.setTitle("title");
		wnd.setMessage("this is a message with the new tidesdk icon");
		wnd.setIcon("app://logo_small.png");
		wnd.setDelay(5000);
		
		
		Tide.API.debug("attempting to show the notification");
		wnd.show();

		timer = setTimeout(function()
		{
			try 
			{
				Tide.API.debug("hiding the notification");
				wnd.hide();
				callback.passed();
			}
			catch(e)
			{
				Tide.API.debug("hiding the notification failed with an exception");
				callback.failed();
			}
		},1000);
	},

	test_non_utf8_as_async: function(callback)
	{
		value_of(Tide.UI.createNotification).should_be_function();
		
		// create a notification object
		var parent = Tide.UI.getCurrentWindow();
		var wnd = Tide.UI.createNotification(parent.window);
		wnd.setTitle("title");
		wnd.setMessage("Стоял он, дум великих полн");
		wnd.setIcon("app://logo_small.png");
		wnd.setDelay(5000);
		
		
		Tide.API.debug("attempting to show the notification");
		wnd.show();

		timer = setTimeout(function()
		{
			try 
			{
				Tide.API.debug("hiding the notification");
				wnd.hide();
				callback.passed();
			}
			catch(e)
			{
				Tide.API.debug("hiding the notification failed with an exception");
				callback.failed();
			}
		},1000);
	}
});
