describe("Contents of user agent",
{
	validate_name_and_version: function()
	{
		value_of(Ti.userAgent).should_contain('Tide/');
		value_of(Ti.userAgent).should_contain('Tide/'+Ti.version);
		// for now, we're going to simulate Safari -- this addresses TI-303
		value_of(Ti.userAgent).should_contain('Safari');
	},
});
