describe("UI Module Tests",{
	test_user_window_title: function()
	{
		// get the current UserWindow object
		var w = Tide.UI.getCurrentWindow().createWindow('http://www.google.com');

		var title = "blahahahahahahahahahahahahaha";
		w.setTitle(title);
		value_of(w.getTitle()).should_be(title);
		title = "	___	   ";
		w.setTitle(title);
		value_of(w.getTitle()).should_be(title);
		title = "	_¬˚∆¬˚¬∂ƒ¬∆ø´ˆ∆¬ßƒ∂ˆ__	   ";
		w.setTitle(title);
		value_of(w.getTitle()).should_be(title);
		title = "";
		w.setTitle(title);
		value_of(w.getTitle()).should_be(title);

		w.open();

		title = "blahahahahahahahahahahahahaha";
		w.setTitle(title);
		value_of(w.getTitle()).should_be(title);
		title = "	___	   ";
		w.setTitle(title);
		value_of(w.getTitle()).should_be(title);
		title = "	_¬˚∆¬˚¬∂ƒ¬∆ø´ˆ∆¬ßƒ∂ˆ__	   ";
		w.setTitle(title);
		value_of(w.getTitle()).should_be(title);
		title = "";
		w.setTitle(title);
		value_of(w.getTitle()).should_be(title);

		w.close();
	},

	test_user_window_url: function()
	{
		// get the current UserWindow object
		var w = Tide.UI.getCurrentWindow().createWindow('http://www.google.com');

		var url = "http://www.google.com/";
		w.setURL(url);
		value_of(w.getURL()).should_be(url);
		url = "http://gmail.com/";
		w.setURL(url);
		value_of(w.getURL()).should_be(url);
		url = "http://www.bbc.co.uk/";
		w.setURL(url);
		value_of(w.getURL()).should_be(url);
		url = "http://mail.google.com/";
		w.setURL(url);
		value_of(w.getURL()).should_be(url);

		w.open();

		url = "http://www.google.com/";
		w.setURL(url);
		value_of(w.getURL()).should_be(url);
		url = "http://gmail.com/";
		w.setURL(url);
		value_of(w.getURL()).should_be(url);
		url = "http://www.bbc.co.uk/";
		w.setURL(url);
		value_of(w.getURL()).should_be(url);
		url = "http://mail.google.com/";
		w.setURL(url);
		value_of(w.getURL()).should_be(url);
		w.close();
	},
	test_event_name_constants: function()
	{
		// If these tests fail, perhaps the constant has changed. If that's
		// the case, just update the tests below and be sure that nothing
		// else in the system breaks! Hopefully apps do not rely on magic strings.
		value_of(Tide.FOCUSED).should_be("focused");
		value_of(Tide.UNFOCUSED).should_be("unfocused");
		value_of(Tide.OPEN).should_be("open");
		value_of(Tide.OPENED).should_be("opened");
		value_of(Tide.CLOSE).should_be("close");
		value_of(Tide.CLOSED).should_be("closed");
		value_of(Tide.HIDDEN).should_be("hidden");
		value_of(Tide.SHOWN).should_be("shown");
		value_of(Tide.FULLSCREENED).should_be("fullscreened");
		value_of(Tide.UNFULLSCREENED).should_be("unfullscreened");
		value_of(Tide.MAXIMIZED).should_be("maximized");
		value_of(Tide.MINIMIZED).should_be("minimized");
		value_of(Tide.RESIZED).should_be("resized");
		value_of(Tide.MOVED).should_be("moved");
		value_of(Tide.PAGE_INITIALIZED).should_be("page.init");
		value_of(Tide.PAGE_LOADED).should_be("page.load");
	},
	test_window_listener_as_async: function(callback)
	{
		// get the current UserWindow object
		var w = Tide.UI.getCurrentWindow().createWindow('app://blahblah.html');

		var messageLog = { };
		messageLog[Tide.CLOSE]  = false;
		messageLog[Tide.CLOSED]  = false;
		messageLog[Tide.OPEN]  = false;
		messageLog[Tide.OPENED]  = false;
		messageLog[Tide.HIDDEN]  = false;

		w.addEventListener(function(event)
		{
			messageLog[event.type] = true;
		});

		w.open();
		setTimeout(function()
		{
			w.close();
			if (messageLog[Tide.OPEN] !== true)
			{
				callback.failed("Did not detect open message");
			}
			else if (messageLog[Tide.OPENED] !== true)
			{
				callback.failed("Did not detect opened message");
			}
			else
			{
				callback.passed();
			}
		}, 1000);
	},
	test_window_maximize_fires_resize_as_async: function(callback)
	{
		// get the current UserWindow object
		var w = Tide.UI.getCurrentWindow().createWindow('app://blahblah.html');
		w.open();

		var resizedFired = false;
		var maximizedFired = false;

		w.addEventListener(function(event)
		{
			if (event.type == "resized")
			{
				resizedFired = true;
			}
			else if (event.type == "maximized")
			{
				maximizedFired = true;
			}
		});

		var stageTwo = function()
		{
			w.close();
			if (!maximizedFired)
			{
				callback.failed("Did not detect maximized message");
			}
			if (!resizedFired)
			{
				callback.failed("Did not detect resized message");
			}
			callback.passed();
		};

		setTimeout(function()
		{
			w.maximize();
			setTimeout(function()
			{
				stageTwo();
			}, 300);
		}, 300);
	},
	
	test_constants: function()
	{
		value_of(Tide.UI.CENTERED).should_be_number();
		value_of(Tide.FOCUSED).should_be_string();
		value_of(Tide.UNFOCUSED).should_be_string();
		value_of(Tide.OPEN).should_be_string();
		value_of(Tide.OPENED).should_be_string();
		value_of(Tide.CLOSE).should_be_string();
		value_of(Tide.CLOSED).should_be_string();
		value_of(Tide.HIDDEN).should_be_string();
		value_of(Tide.SHOWN).should_be_string();
		value_of(Tide.FULLSCREENED).should_be_string();
		value_of(Tide.UNFULLSCREENED).should_be_string();
		value_of(Tide.MAXIMIZED).should_be_string();
		value_of(Tide.MINIMIZED).should_be_string();
		value_of(Tide.RESIZED).should_be_string();
		value_of(Tide.MOVED).should_be_string();
		value_of(Tide.PAGE_INITIALIZED).should_be_string();
		value_of(Tide.PAGE_LOADED).should_be_string();
		value_of(Tide.CREATED).should_be_string();
	},
	test_window_events_as_async: function(callback)
	{
		var eventTests = [];
		var addEventTest = function(eventTrigger, eventsToVerify, timeout)
		{
			eventTests.push({ 
				'trigger': eventTrigger,
				'events': eventsToVerify,
				'timeout': timeout == null ? 250 : timeout
			});
		}

		var observedEvents = {};
		var eventListener = function(event)
		{
			observedEvents[event.getType()] = "Yakko";
		}

		var w = Tide.UI.getCurrentWindow().createWindow('app://test.html');
		var listener = w.addEventListener(eventListener);
		value_of(listener).should_be_function();

		addEventTest(function() { w.open(); }, [Tide.OPEN, Tide.OPENED, Tide.PAGE_LOADED], 2000);
		addEventTest(function() { w.setVisible(false); }, [Tide.HIDDEN]);
		addEventTest(function() { w.setVisible(true); }, [Tide.SHOWN]);
		addEventTest(function() { w.setFullscreen(true); }, [Tide.FULLSCREENED]);
		addEventTest(function() { w.setFullscreen(false); }, [Tide.UNFULLSCREENED]);
		addEventTest(function() { w.maximize(); }, [Tide.MAXIMIZED]);
		addEventTest(function() { w.unmaximize(); w.minimize(); }, [Tide.MINIMIZED]);
		addEventTest(function() { w.unminimize(); var b = w.getBounds(); w.setX(b.x+1);}, [Tide.MOVED]);
		addEventTest(function() {var b = w.getBounds(); w.setY(b.y+1); }, [Tide.MOVED]);
		addEventTest(function() {var b = w.getBounds(); w.setWidth(b.width*2); }, [Tide.RESIZED]);
		addEventTest(function() {var b = w.getBounds(); w.setHeight(b.height+1); }, [Tide.RESIZED]);
		addEventTest(function() {w.close();}, [Tide.CLOSE, Tide.CLOSED]);
		
		var runNextTest = function() {
			if (eventTests.length <= 0)
			{
				callback.passed();
				return;
			}

			var nextTest = eventTests.shift();
			setTimeout(function() {
				for (var i = 0; i < nextTest.events.length; i++)
				{
					var evname = nextTest.events[i];
					if (!observedEvents[evname] || observedEvents[evname] !== "Yakko")
					{
						callback.failed("Did not receive event:" + evname);
					}
				}
				runNextTest();
			}, nextTest.timeout);
			observedEvents = {};
			nextTest.trigger();
		}
		runNextTest();
	},
	test_set_x_sanity_as_async: function(callback)
	{
		var w = Tide.UI.getCurrentWindow().createWindow({width: 500, height: 300});
		var orig_y = w.getY();
		w.setX(100);

		setTimeout(function() {
			if (w.x != 100) { callback.failed("X property was not correct"); }
			if (w.y != orig_y) { callback.failed("Y property was not correct"); }
			if (w.width != 500) { callback.failed("width property was not correct"); }
			if (w.height != 300) { callback.failed("height property was not correct"); }
			callback.passed();
		}, 250);
	},
	test_set_y_sanity_as_async: function(callback)
	{
		var w = Tide.UI.getCurrentWindow().createWindow({width: 500, height: 300});
		var orig_x = w.getX();
		w.setY(100);

		setTimeout(function() {
			if (w.y != 100) { callback.failed("Y property was not correct"); }
			if (w.x != orig_x) { callback.failed("X property was not correct"); }
			if (w.width != 500) { callback.failed("width property was not correct"); }
			if (w.height != 300) { callback.failed("height property was not correct"); }
			callback.passed();
		}, 250);
	},
	test_set_width_sanity_as_async: function(callback)
	{
		var w = Tide.UI.getCurrentWindow().createWindow({width: 500, height: 300});
		var orig_x = w.getX();
		var orig_y = w.getY();
		w.setWidth(400);

		setTimeout(function() {
			if (w.y != orig_y) { callback.failed("Y property was not correct"); }
			if (w.x != orig_x) { callback.failed("X property was not correct"); }
			if (w.width != 400) { callback.failed("width property was not correct"); }
			if (w.height != 300) { callback.failed("height property was not correct"); }
			callback.passed();
		}, 250);
	},
	test_set_height_sanity_as_async: function(callback)
	{
		var w = Tide.UI.getCurrentWindow().createWindow({width: 500, height: 300});
		var orig_x = w.getX();
		var orig_y = w.getY();
		w.setHeight(400);

		setTimeout(function() {
			if (w.y != orig_y) { callback.failed("Y property was not correct"); }
			if (w.x != orig_x) { callback.failed("X property was not correct"); }
			if (w.width != 500) { callback.failed("width property was not correct"); }
			if (w.height != 400) { callback.failed("height property was not correct"); }
			callback.passed();
		}, 250);
	},
	test_cancel_close_with_stop_propagation_as_async: function(callback)
	{
		var w = Tide.UI.getCurrentWindow().createWindow({width: 500, height: 300});
		var cancel = true;
		var sawEvent = false;
		w.addEventListener(Tide.CLOSE, function(event) {
			sawEvent = true;
			if (cancel)
			{
				event.stopPropagation();
			}
		});

		// Ensure this is after the window is open.
		w.open();
		setTimeout(function() {
			w.close();
			setTimeout(function () {
				Tide.API.debug("here1");
				if (!sawEvent)
				{
					callback.failed("Did not see CLOSE event.");
				}

				Tide.API.debug("did see the event");
				if (w.isActive()) {
					Tide.API.debug("window is active");
					callback.passed();
				} else {
					Tide.API.debug("window is not active");
					callback.failed("Window close event was not cancelled.");
				}
				cancel = false;
				w.close();
			}, 250);
		}, 150);
	},
	test_cancel_close_with_prevent_default_as_async: function(callback)
	{
		var w = Tide.UI.getCurrentWindow().createWindow({width: 500, height: 300});
		var cancel = true;
		var sawEvent = false;
		w.addEventListener(Tide.CLOSE, function(event) {
			sawEvent = true;
			if (cancel)
			{
				event.preventDefault();
			}
		});

		// Ensure this is after the window is open.
		w.open();
		setTimeout(function() {
			w.close();
			setTimeout(function () {
				if (!sawEvent)
				{
					callback.failed("Did not see CLOSE event.");
				}

				if (w.isActive()) {
					callback.passed();
				} else {
					callback.failed("Window close event was not cancelled.");
				}
				cancel = false;
				w.close();
			}, 250);
		}, 150);
	}
});
