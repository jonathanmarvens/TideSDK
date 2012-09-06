describe('ti global tests', {
  test_platform: function() {
    // function to testout the global properties in Ti.
    value_of(Ti.platform).should_be_string();
    // get the platform and version.
    value_of(Ti.platform).should_be_one_of(['win32','osx','linux']);
    Ti.API.info('Ti.platform = '+Ti.platform);
  },  
  test_version: function() {
    value_of(Ti.version).should_be_string();
    var arr = Ti.version.split('.');
    value_of(arr.length).should_be(4);
    value_of(Number(arr[0])).should_be_number();
    value_of(Number(arr[1])).should_be_number();
    value_of(Number(arr[2])).should_be_number();
    Ti.API.info('Ti.version = '+Ti.version);
  }
});
