describe('ti global tests', {
  test_platform: function() {
    // function to testout the global properties in Tide.
    value_of(Tide.platform).should_be_string();
    // get the platform and version.
    value_of(Tide.platform).should_be_one_of(['win32','osx','linux']);
    Tide.API.info('Tide.platform = '+Tide.platform);
  },  
  test_version: function() {
    value_of(Tide.version).should_be_string();
    var arr = Tide.version.split('.');
    value_of(arr.length).should_be(4);
    value_of(Number(arr[0])).should_be_number();
    value_of(Number(arr[1])).should_be_number();
    value_of(Number(arr[2])).should_be_number();
    Tide.API.info('Tide.version = '+Tide.version);
  }
});
