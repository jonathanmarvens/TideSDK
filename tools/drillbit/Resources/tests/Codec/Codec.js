describe("Codec Tests",{
	
	test_base64_encode: function()
	{
		value_of(Tide.Codec).should_be_object();
		value_of(Tide.Codec.encodeBase64("abc")).should_be("YWJj");
	},

	test_base64_decode: function()
	{
		value_of(Tide.Codec.decodeBase64("YWJj")).should_be("abc");
	},
	
	test_md2: function()
	{
		value_of(Tide.Codec.digestToHex(Tide.Codec.MD2,"abc")).should_be("da853b0d3f88d99b30283a69e6ded6bb");
	},

	test_md4: function()
	{
		value_of(Tide.Codec.digestToHex(Tide.Codec.MD4,"abc")).should_be("a448017aaf21d8525fc10ae87aa6729d");
	},

	test_md5: function()
	{
		value_of(Tide.Codec.digestToHex(Tide.Codec.MD5,"abc")).should_be("900150983cd24fb0d6963f7d28e17f72");
	},

	test_sha1: function()
	{
		value_of(Tide.Codec.digestToHex(Tide.Codec.SHA1,"abc")).should_be("a9993e364706816aba3e25717850c26c9cd0d89d");
	},
	
	test_hmac_md5: function()
	{
		value_of(Tide.Codec.digestHMACToHex(Tide.Codec.MD5,"abc","123")).should_be("ffb7c0fc166f7ca075dfa04d59aed232");
	},

	test_hmac_sha1: function()
	{
		value_of(Tide.Codec.digestHMACToHex(Tide.Codec.SHA1,"abc","123")).should_be("540b0c53d4925837bd92b3f71abe7a9d70b676c4");
	},

	test_encode_hex_binary: function()
	{
		value_of(Tide.Codec.encodeHexBinary("ABCDEF")).should_be("414243444546");
	},

	test_decode_hex_binary: function()
	{
		value_of(Tide.Codec.decodeHexBinary("414243444546")).should_be("ABCDEF");
	},
	
	test_checksum_crc32: function()
	{
		value_of(Tide.Codec.checksum("abc")).should_be(891568578);
		value_of(Tide.Codec.checksum("abc",Tide.Codec.CRC32)).should_be(891568578);
		var blob = Tide.API.createBytes("abc");
		value_of(Tide.Codec.checksum(blob,Tide.Codec.CRC32)).should_be(891568578);
	},
	
	test_checksum_adler32: function()
	{
		value_of(Tide.Codec.checksum("abc",Tide.Codec.ADLER32)).should_be(38600999);

		var blob = Tide.API.createBytes("abc");
		value_of(Tide.Codec.checksum(blob,Tide.Codec.ADLER32)).should_be(38600999);
	},
	
	test_createZip_as_async: function(callback)
	{
		var fs = Tide.Filesystem;
		function appFile(url)
		{
			return fs.getFile(Tide.App.appURLToPath(url));
		}
		function getFileSHA1(file)
		{
			var blob = file.read();
			return Tide.Codec.digestToHex(Tide.Codec.SHA1, blob);
		}
		
		var dir = appFile("app://zipdir");
		var zipFile = fs.createTempFile();
		var unzipDir = fs.createTempDirectory();
		var png = appFile("app://zipdir/default_app_logo.png");
		var file1 = appFile("app://zipdir/file1.txt");
		var file2 = appFile("app://zipdir/file2.txt");
		
		Tide.API.debug("zipfile="+zipFile);
		value_of(dir.isDirectory()).should_be_true();
		
		var timer = 0;
		Tide.Codec.createZip(dir, zipFile, function(destFile)
		{
			try
			{
				clearTimeout(timer);
				value_of(destFile).should_be(zipFile);
				var file = fs.getFile(destFile);
				value_of(file.size()).should_be(5791);
				var blob = file.read();
				value_of(blob.length).should_be(5791);
				
				// in OSX, the the file contents seem to change each time the zip is created
				// so, a SHA1 is unreliable (weird). We'll just check the files
				file.unzip(unzipDir);
				var zipPNG = fs.getFile(unzipDir, "default_app_logo.png");
				var zipFile1 = fs.getFile(unzipDir, "file1.txt");
				var zipFile2 = fs.getFile(unzipDir, "file2.txt");
				
				value_of(zipPNG.isFile()).should_be_true();
				value_of(zipPNG.size()).should_be(png.size());
				value_of(getFileSHA1(zipPNG)).should_be("d4f3cdccba5cc918150ad0d99ea2d395361d35b9");
				
				value_of(zipFile1.isFile()).should_be_true();
				value_of(zipFile1.size()).should_be(file1.size());
				value_of(getFileSHA1(zipFile1)).should_be("51c79e08a7986b23085fddd9c6d284a3a591efda")
				
				value_of(zipFile2.isFile()).should_be_true();
				value_of(zipFile2.size()).should_be(file2.size());
				value_of(getFileSHA1(zipFile2)).should_be("8538a15f340202ec8052e9cc44adce70df475ac7")
				
				callback.passed();
			}
			catch (e)
			{
				callback.failed(e);
			}
		});
		
		timer = setTimeout(function()
		{
			callback.failed("timed out waiting for create zip callback");
		}, 5000);
	},

	test_extractZip_as_async: function(callback)
	{
		function appFile(url)
		{
			return Tide.Filesystem.getFile(Tide.App.appURLToPath(url));
		}
		function getFileSHA1(file)
		{
			var blob = file.read();
			return Tide.Codec.digestToHex(Tide.Codec.SHA1, blob);
		}

		var zipFile = Tide.App.appURLToPath("app://stuff.zip");
		var destDir = Tide.Filesystem.createTempDirectory();
		var png = appFile("app://zipdir/default_app_logo.png");
		var file1 = appFile("app://zipdir/file1.txt");
		var file2 = appFile("app://zipdir/file2.txt");

		var timer = 0;
		Tide.Codec.extractZip(zipFile, destDir, function(dest) {
			clearTimeout(timer);

			// Verify extracted directory contents
			try
			{
				var zipPNG = Tide.Filesystem.getFile(destDir, "default_app_logo.png");
				var zipFile1 = Tide.Filesystem.getFile(destDir, "file1.txt");
				var zipFile2 = Tide.Filesystem.getFile(destDir, "file2.txt");
				
				value_of(zipPNG.isFile()).should_be_true();
				value_of(zipPNG.size()).should_be(png.size());
				value_of(getFileSHA1(zipPNG)).should_be("d4f3cdccba5cc918150ad0d99ea2d395361d35b9");
				
				value_of(zipFile1.isFile()).should_be_true();
				value_of(zipFile1.size()).should_be(file1.size());
				value_of(getFileSHA1(zipFile1)).should_be("51c79e08a7986b23085fddd9c6d284a3a591efda");
				
				value_of(zipFile2.isFile()).should_be_true();
				value_of(zipFile2.size()).should_be(file2.size());
				value_of(getFileSHA1(zipFile2)).should_be("8538a15f340202ec8052e9cc44adce70df475ac7");

				callback.passed();
			}
			catch (e)
			{
				callback.failed(e)
			}
		});

		timer = setTimeout(function()
		{
			callback.failed("timed out waiting for extract zip callback");
		}, 5000);
	}
});
