describe("test ti.Analytics",{
	test_analytics_properties: function()
	{
		value_of(Ti.Analytics).should_be_object();
		value_of(Ti.Analytics.addEvent).should_be_function();
	},
});
