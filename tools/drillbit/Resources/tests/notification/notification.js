/**
* (c) 2008-2012 Appcelerator Inc.
* 
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*   http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
**/

describe("Notification Tests", {
  test_notification_object: function () {
    var wnd = Ti.Notification.createNotification(parent.window);

    value_of(wnd.hide)
      .should_be_function();
    value_of(wnd.setCallback)
      .should_be_function();
    value_of(wnd.setDelay)
      .should_be_function();
    value_of(wnd.setIcon)
      .should_be_function();
    value_of(wnd.setMessage)
      .should_be_function();
    value_of(wnd.setTitle)
      .should_be_function();
    value_of(wnd.show)
      .should_be_function();
    value_of(wnd)
      .should_be_object();
  },

  test_it_with_large_icon_as_async: function (callback) {
    value_of(Ti.Notification.createNotification)
      .should_be_function();

    // create a notification object
    var parent = Ti.UI.getCurrentWindow();
    var wnd = Ti.Notification.createNotification(parent.window);
    wnd.setTitle("title");
    wnd.setMessage("this is a message with a big icon");
    wnd.setIcon("app://logo_large.png");
    wnd.setDelay(5000);

    wnd.setCallback(function () {
      Ti.API.debug("user click on notification window");
      callback.passed();
    });


    Ti.API.debug("attempting to show the notification");
    wnd.show();

    timer = setTimeout(function () {
      try {
        Ti.API.debug("hiding the notification");
        wnd.hide();
        callback.passed();
      } catch (e) {
        Ti.API.debug("hiding the notification failed with an exception");
        callback.failed();
      }
    }, 1000);
  },

  test_it_with_small_icon_as_async: function (callback) {
    value_of(Ti.Notification.createNotification)
      .should_be_function();

    // create a notification object
    var parent = Ti.UI.getCurrentWindow();
    var wnd = Ti.Notification.createNotification(parent.window);
    wnd.setTitle("title");
    wnd.setMessage("this is a message with a small icon");
    wnd.setIcon("app://logo_small.png");
    wnd.setDelay(5000);

    wnd.setCallback(function () {
      Ti.API.debug("user click on notification window");
      callback.passed();
    });


    Ti.API.debug("attempting to show the notification");
    wnd.show();

    timer = setTimeout(function () {
      try {
        Ti.API.debug("hiding the notification");
        wnd.hide();
        callback.passed();
      } catch (e) {
        Ti.API.debug("hiding the notification failed with an exception");
        callback.failed();
      }
    }, 1000);
  }
});
