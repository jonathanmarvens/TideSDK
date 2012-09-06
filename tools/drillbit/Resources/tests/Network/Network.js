describe("Network Module",{
	// ti.network.HTTP objects are covered in the http_server unit test.

	// test the network object and properties.
	test_network_object:function()
	{
		value_of(Ti.Network).should_not_be_null();
		value_of(Ti.Network.getProxy).should_be_function();
		value_of(Ti.Network.setProxy).should_be_function();
		value_of(Ti.Network.addConnectivityListener).should_be_function();
		value_of(Ti.Network.createHTTPClient).should_be_function();
		value_of(Ti.Network.createHTTPServer).should_be_function();
		value_of(Ti.Network.createIPAddress).should_be_function();
		value_of(Ti.Network.createIRCClient).should_be_function();
		value_of(Ti.Network.createTCPSocket).should_be_function();
		value_of(Ti.Network.decodeURIComponent).should_be_function();
		value_of(Ti.Network.encodeURIComponent).should_be_function();
		value_of(Ti.Network.getHostByAddress).should_be_function();
		value_of(Ti.Network.getHostByName).should_be_function();
		value_of(Ti.Network.online).should_not_be_null();
		value_of(Ti.Network.removeConnectivityListener).should_be_function();
	 
		value_of(Ti.Network.online).should_be_true();
	},
	
	test_network_URIComponents: function()
	{
		var str = "the test string";
		
		var encoded = Ti.Network.encodeURIComponent(str);
		
		// is the string encoded?
		value_of(str == encoded).should_be_false();
		value_of(encoded.indexOf("%20")).should_not_be(-1);
		
		var decoded = Ti.Network.decodeURIComponent(encoded);

		// is the string decoded?
		value_of(str == decoded).should_be_true();
		value_of(decoded.indexOf("%20")).should_be(-1);
	},
	test_network_proxy_functions:function()
	{
		value_of(Ti.Network).should_not_be_null();
		value_of(Ti.Network.getProxy).should_be_function();
		value_of(Ti.Network.setProxy).should_be_function();
		value_of(Ti.Network.getHTTPProxy).should_be_function();
		value_of(Ti.Network.setHTTPProxy).should_be_function();
		value_of(Ti.Network.getHTTPSProxy).should_be_function();
		value_of(Ti.Network.setHTTPSProxy).should_be_function();
	},
	test_proxy: function()
	{
		var proxy = Ti.Network.getProxy();
		value_of(proxy).should_be(null);

		Ti.Network.setProxy("http://www.google.com:81");
		var proxy = Ti.Network.getProxy();
		value_of(proxy).should_be("http://www.google.com:81");

		Ti.Network.setProxy(null);
		proxy = Ti.Network.getProxy();
		value_of(proxy).should_be(null);

		Ti.Network.setProxy("http://www.google.com:81");
		var proxy = Ti.Network.getProxy();
		value_of(proxy).should_be("http://www.google.com:81");

		Ti.Network.setProxy("www.yahoo.com:81");
		var proxy = Ti.Network.getProxy();
		value_of(proxy).should_be("http://www.yahoo.com:81");

		Ti.Network.setProxy("");
		proxy = Ti.Network.getProxy();
		value_of(proxy).should_be(null);
	},
	test_http_proxy: function()
	{
		var proxy = Ti.Network.getHTTPProxy();
		value_of(proxy).should_be(null);

		Ti.Network.setHTTPProxy("http://www.google.com:81");
		var proxy = Ti.Network.getHTTPProxy();
		value_of(proxy).should_be("http://www.google.com:81");

		Ti.Network.setHTTPProxy(null);
		proxy = Ti.Network.getHTTPProxy();
		value_of(proxy).should_be(null);

		Ti.Network.setHTTPProxy("http://www.google.com:81");
		var proxy = Ti.Network.getHTTPProxy();
		value_of(proxy).should_be("http://www.google.com:81");

		Ti.Network.setHTTPProxy("www.yahoo.com:81");
		var proxy = Ti.Network.getHTTPProxy();
		value_of(proxy).should_be("http://www.yahoo.com:81");

		Ti.Network.setHTTPProxy("direct://");
		var proxy = Ti.Network.getHTTPProxy();
		value_of(proxy).should_be_null();

		Ti.Network.setHTTPProxy("http://joe:blow@foo.com:80");
		var proxy = Ti.Network.getHTTPProxy();
		value_of(proxy).should_be("http://joe:blow@foo.com:80");

		Ti.Network.setHTTPProxy("");
		proxy = Ti.Network.getHTTPProxy();
		value_of(proxy).should_be(null);
	},
	test_https_proxy: function()
	{
		var proxy = Ti.Network.getHTTPSProxy();
		value_of(proxy).should_be(null);

		Ti.Network.setHTTPSProxy("https://www.google.com:81");
		var proxy = Ti.Network.getHTTPSProxy();
		value_of(proxy).should_be("https://www.google.com:81");

		Ti.Network.setHTTPSProxy(null);
		proxy = Ti.Network.getHTTPSProxy();
		value_of(proxy).should_be(null);

		Ti.Network.setHTTPSProxy("https://www.google.com:81");
		var proxy = Ti.Network.getHTTPSProxy();
		value_of(proxy).should_be("https://www.google.com:81");

		Ti.Network.setHTTPSProxy("www.yahoo.com:81");
		var proxy = Ti.Network.getHTTPSProxy();
		value_of(proxy).should_be("https://www.yahoo.com:81");

		Ti.Network.setHTTPSProxy("direct://");
		var proxy = Ti.Network.getHTTPSProxy();
		value_of(proxy).should_be_null();

		Ti.Network.setHTTPSProxy("http://joe:blow@foo.com:80");
		var proxy = Ti.Network.getHTTPSProxy();
		value_of(proxy).should_be("http://joe:blow@foo.com:80");

		Ti.Network.setHTTPSProxy("");
		proxy = Ti.Network.getHTTPSProxy();
		value_of(proxy).should_be(null);
	},
});
