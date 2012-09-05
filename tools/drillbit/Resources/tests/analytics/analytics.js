describe("test ti.Analytics",{
	test_analytics_properties: function()
	{
		value_of(Tide.Analytics).should_be_object();
		value_of(Tide.Analytics.addEvent).should_be_function();
	},
});
