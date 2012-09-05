describe("Network Module",{
	// ti.network.HTTP objects are covered in the http_server unit test.

	// test the network object and properties.
	test_network_object:function()
	{
		value_of(Tide.Network).should_not_be_null();
		value_of(Tide.Network.getProxy).should_be_function();
		value_of(Tide.Network.setProxy).should_be_function();
		value_of(Tide.Network.addConnectivityListener).should_be_function();
		value_of(Tide.Network.createHTTPClient).should_be_function();
		value_of(Tide.Network.createHTTPServer).should_be_function();
		value_of(Tide.Network.createIPAddress).should_be_function();
		value_of(Tide.Network.createIRCClient).should_be_function();
		value_of(Tide.Network.createTCPSocket).should_be_function();
		value_of(Tide.Network.decodeURIComponent).should_be_function();
		value_of(Tide.Network.encodeURIComponent).should_be_function();
		value_of(Tide.Network.getHostByAddress).should_be_function();
		value_of(Tide.Network.getHostByName).should_be_function();
		value_of(Tide.Network.online).should_not_be_null();
		value_of(Tide.Network.removeConnectivityListener).should_be_function();
	 
		value_of(Tide.Network.online).should_be_true();
	},
	
	test_network_URIComponents: function()
	{
		var str = "the test string";
		
		var encoded = Tide.Network.encodeURIComponent(str);
		
		// is the string encoded?
		value_of(str == encoded).should_be_false();
		value_of(encoded.indexOf("%20")).should_not_be(-1);
		
		var decoded = Tide.Network.decodeURIComponent(encoded);

		// is the string decoded?
		value_of(str == decoded).should_be_true();
		value_of(decoded.indexOf("%20")).should_be(-1);
	},
	test_network_proxy_functions:function()
	{
		value_of(Tide.Network).should_not_be_null();
		value_of(Tide.Network.getProxy).should_be_function();
		value_of(Tide.Network.setProxy).should_be_function();
		value_of(Tide.Network.getHTTPProxy).should_be_function();
		value_of(Tide.Network.setHTTPProxy).should_be_function();
		value_of(Tide.Network.getHTTPSProxy).should_be_function();
		value_of(Tide.Network.setHTTPSProxy).should_be_function();
	},
	test_proxy: function()
	{
		var proxy = Tide.Network.getProxy();
		value_of(proxy).should_be(null);

		Tide.Network.setProxy("http://www.google.com:81");
		var proxy = Tide.Network.getProxy();
		value_of(proxy).should_be("http://www.google.com:81");

		Tide.Network.setProxy(null);
		proxy = Tide.Network.getProxy();
		value_of(proxy).should_be(null);

		Tide.Network.setProxy("http://www.google.com:81");
		var proxy = Tide.Network.getProxy();
		value_of(proxy).should_be("http://www.google.com:81");

		Tide.Network.setProxy("www.yahoo.com:81");
		var proxy = Tide.Network.getProxy();
		value_of(proxy).should_be("http://www.yahoo.com:81");

		Tide.Network.setProxy("");
		proxy = Tide.Network.getProxy();
		value_of(proxy).should_be(null);
	},
	test_http_proxy: function()
	{
		var proxy = Tide.Network.getHTTPProxy();
		value_of(proxy).should_be(null);

		Tide.Network.setHTTPProxy("http://www.google.com:81");
		var proxy = Tide.Network.getHTTPProxy();
		value_of(proxy).should_be("http://www.google.com:81");

		Tide.Network.setHTTPProxy(null);
		proxy = Tide.Network.getHTTPProxy();
		value_of(proxy).should_be(null);

		Tide.Network.setHTTPProxy("http://www.google.com:81");
		var proxy = Tide.Network.getHTTPProxy();
		value_of(proxy).should_be("http://www.google.com:81");

		Tide.Network.setHTTPProxy("www.yahoo.com:81");
		var proxy = Tide.Network.getHTTPProxy();
		value_of(proxy).should_be("http://www.yahoo.com:81");

		Tide.Network.setHTTPProxy("direct://");
		var proxy = Tide.Network.getHTTPProxy();
		value_of(proxy).should_be_null();

		Tide.Network.setHTTPProxy("http://joe:blow@foo.com:80");
		var proxy = Tide.Network.getHTTPProxy();
		value_of(proxy).should_be("http://joe:blow@foo.com:80");

		Tide.Network.setHTTPProxy("");
		proxy = Tide.Network.getHTTPProxy();
		value_of(proxy).should_be(null);
	},
	test_https_proxy: function()
	{
		var proxy = Tide.Network.getHTTPSProxy();
		value_of(proxy).should_be(null);

		Tide.Network.setHTTPSProxy("https://www.google.com:81");
		var proxy = Tide.Network.getHTTPSProxy();
		value_of(proxy).should_be("https://www.google.com:81");

		Tide.Network.setHTTPSProxy(null);
		proxy = Tide.Network.getHTTPSProxy();
		value_of(proxy).should_be(null);

		Tide.Network.setHTTPSProxy("https://www.google.com:81");
		var proxy = Tide.Network.getHTTPSProxy();
		value_of(proxy).should_be("https://www.google.com:81");

		Tide.Network.setHTTPSProxy("www.yahoo.com:81");
		var proxy = Tide.Network.getHTTPSProxy();
		value_of(proxy).should_be("https://www.yahoo.com:81");

		Tide.Network.setHTTPSProxy("direct://");
		var proxy = Tide.Network.getHTTPSProxy();
		value_of(proxy).should_be_null();

		Tide.Network.setHTTPSProxy("http://joe:blow@foo.com:80");
		var proxy = Tide.Network.getHTTPSProxy();
		value_of(proxy).should_be("http://joe:blow@foo.com:80");

		Tide.Network.setHTTPSProxy("");
		proxy = Tide.Network.getHTTPSProxy();
		value_of(proxy).should_be(null);
	},
});
