describe("Contents of user agent",
{
	validate_name_and_version: function()
	{
		value_of(Tide.userAgent).should_contain('Tide/');
		value_of(Tide.userAgent).should_contain('Tide/'+Tide.version);
		// for now, we're going to simulate Safari -- this addresses TI-303
		value_of(Tide.userAgent).should_contain('Safari');
	},
});
