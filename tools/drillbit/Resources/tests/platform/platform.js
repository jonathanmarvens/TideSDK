describe("ti.Platform tests", {
	test_interfaces: function() {
		var interfaces = Tide.Platform.interfaces;
		value_of(Tide.Platform.interfaces).should_be_array();
		value_of(Tide.Platform.interfaces.length > 0).should_be_true();
		
		for (var i = 0; i < Tide.Platform.interfaces.length; i++) {
			var iface = Tide.Platform.interfaces[i];
			value_of(iface.name).should_be_string();
			value_of(iface.address).should_be_string();
			value_of(iface.displayName).should_be_string();
			
			Tide.API.debug("interface "+ iface.name + 
			                   ", " +  iface.address + 
			                   ", " + iface.displayName );
		}
	},
	
	test_platform_properties: function() {
		value_of(Tide.Platform.name).should_be_string();
		value_of(Tide.Platform.ostype).should_be_string();
		value_of(Tide.Platform.version).should_be_string();
		value_of(Tide.Platform.architecture).should_be_string();
		value_of(Tide.Platform.address).should_be_string();
		value_of(Tide.Platform.id).should_be_string();
		value_of(Tide.Platform.macaddress).should_be_string();
		value_of(Tide.Platform.processorCount).should_be_number();
		value_of(Tide.Platform.username).should_be_string();
		value_of(Tide.Platform.createUUID).should_be_function();

		Tide.API.debug("Tide.Platform.name " +Tide.Platform.name);
		Tide.API.debug("Tide.Platform.ostype " +Tide.Platform.ostype);
		Tide.API.debug("Tide.Platform.version " +Tide.Platform.version);
		Tide.API.debug("Tide.Platform.architecture " +Tide.Platform.architecture);
		Tide.API.debug("Tide.Platform.address " +Tide.Platform.address);
		Tide.API.debug("Tide.Platform.id " +Tide.Platform.id);
		Tide.API.debug("Tide.Platform.macaddress " +Tide.Platform.macaddress);
		Tide.API.debug("Tide.Platform.processorCount " +Tide.Platform.processorCount);
		Tide.API.debug("Tide.Platform.username " +Tide.Platform.username);

        // TODO add more specific tests to insure we report the correct platform.
        if ( Tide.platform == "osx" )
        {
            value_of(Tide.Platform.name).should_not_be("Windows NT");
        }
        else if ( Tide.platform == "linux" )
        {
            value_of(Tide.Platform.name).should_not_be("Windows NT");
        }
        else if ( Tide.platform == "win32" )
        {
            value_of(Tide.Platform.name).should_be("Windows NT");
        }
        else 
        {
            // this is a delibrate error.  we should never get here.
            // but just in case we do, log it.
            value_of(Tide.Platform.name).should_not_be("unknown");
        }
	},
	
	test_unique_uuid: function() {
		var uuids = [];
		for (var i = 0; i < 100; i++) {
			var uuid = Tide.Platform.createUUID();
			value_of(uuid in uuids).should_be_false();
			uuids.push(uuid);
		}
	}
});
