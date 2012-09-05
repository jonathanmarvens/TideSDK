describe("javascript",
{
	test_javascript_functions_no_window: function()
	{
		value_of(Tide.setTimeout).should_be_function();
		value_of(Tide.setInterval).should_be_function();
		value_of(Tide.clearTimeout).should_be_function();
		value_of(Tide.clearInterval).should_be_function();
		
		value_of(Tide.setTimeout).should_not_be(setTimeout);
		value_of(Tide.setInterval).should_not_be(setInterval);
		value_of(Tide.clearTimeout).should_not_be(clearTimeout);
		value_of(Tide.clearInterval).should_not_be(clearInterval);
	},
	
	test_setTimeout_as_async: function(callback)
	{
		var timer = 0;
		Tide.setTimeout(function() {
			try
			{
				value_of(clearTimeout).should_not_be(Tide.clearTimeout);
			}
			catch (e)
			{
				callback.failed(e);
			}
			
			clearTimeout(timer);
			callback.passed();
		}, 500);
		
		timer = setTimeout(function() {
			callback.failed("timed out waiting for native setTimeout");
		}, 2000);
	},
	
	test_setInterval_as_async: function(callback)
	{
		var times = 0;
		var timer = 0;
		Tide.setInterval(function() {
			times++;
			if (times == 5)
			{
				clearTimeout(timer);
				callback.passed();
			}
		}, 500);
		
		timer = setTimeout(function() {
			callback.failed("timed out waiting for 5 calls from native setInterval");
		}, 4000);
	},
	
	test_clearTimeout_as_async: function(callback)
	{
		var timer = Tide.setTimeout(function() {
			callback.failed("timer wasn't cleared correctly");
		}, 500);
		
		Tide.clearTimeout(timer);
		var timer2 = Tide.setTimeout(function() {
			callback.passed();
		}, 1500);
	},
	
	test_clearInterval_as_async: function(callback)
	{
		var times = 0;
		var timer = Tide.setInterval(function() {
			times++;
			if (times == 5)
			{
				Tide.clearInterval(timer);
			}
			else if (times > 5)
			{
				callback.failed("interval wasn't cleared correctly");
			}
		}, 500);
		
		var timer2 = Tide.setTimeout(function() {
			callback.passed();
		}, 4000);
	}
});
