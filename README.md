TideSDK
=======

``
  _______ _______ ____  ______
 |__   __|__   __|  _ \|  ____|
    | |     | |  | | \ | |__
    | |     | |  | | | |  __|
    | |   __| |__| |_/ | |____
    |_|  |_______|____/|______|

```

TideSDK (formerly Titanium Desktop) is a remarkable project inherited from Appcelerator. It is now managed as community open source project by group dedicated to the availability of this unique solution. 

The ability to deploy a Webkit-based desktop application across all three major desktop operating systems, with privileged access to native APIs, has empowered web developers to escape the browser and deliver rich, "always on" desktop apps. 

Users create applications using familiar HTML5, JavaScript and CSS technologies. Beyond this, the unique support for Python, PHP and Ruby extend the capabilities of TideSDK beyond the realm of any competitive framework. Further, our plans include the expansion and extension TideSDK's API's for even better, more complex, and reliable user experiences on the desktop as we move forward.


Getting and Using TideSDK
-------------------------

Downloads are available for the previous Titanium Desktop 1.2.0.RC4 in the interim as we prepare for our first release candidate 1.2.1.RC1. These are the downloads area for the project:

* [https://github.com/TideSDK/TideSDK/downloads](https://github.com/TideSDK/TideSDK/downloads)

The API's will remain compatible so there is nothing to fear with a transition from Titanium Desktop and TideSDK in the near future.

Our enhanced documentation efforts are in progress and our docs will be hosted with read-the-docs in multiple languages. While these efforts are underway, please refer to Appcelerator's API docs that ar available as a download in our downloads area.

You will find us building other resources to support you in our Wiki:

* [https://github.com/TideSDK/TideSDK/wiki](https://github.com/TideSDK/TideSDK/wiki)


Building TideSDK (Developers)
-----------------------------

This instruction applies to developers only. If you are a user, your involvement with the SDK will be obtaining and using TideSDK to build your apps.
Please refer to https://github.com/TideSDK/TideSDK/wiki/Building-tidesdk
for up to date instructions on how to build this project.

Support
-------
- Consult https://github.com/TideSDK/TideSDK/wiki for a list of updated user and developer resources including documentation, code examples, tutorials and more.
- Join our mailing list at https://groups.google.com/forum/#!forum/tidesdk.
- Report bugs or issues to https://github.com/TideSDK/TideSDK/issues. 
- Come and chat with us on IRC - freenode.net #tidesdk.
- Follow us on Twitter (@tidesdk)[http://twitter.com/tidesdk].
- Visit our blog at http://tidesdk.org/blog.

Legal
-----
TideSDK is licensed under a liberal Apache 2.0 license.
Please see LICENSE for more details.


Tide-MicroKernel
----------------

Tide has a compact microkernel written in C++ for running pluggable
modules. Tide-MicroKernel supports a cross-language, cross-platform "binding"
and invocation framework which supports mixing and matching
code within the Tide kernel. Yes, that means you can pass a
Javascript object to a Python function and stuff like that.

Currently, Tide supports the following languages:

- C/C++
- Python
- Ruby
- PHP
- JavaScript

However, any C/C++ exposed language which supports embedding most likely
can be supported with not much effort. These languages are on the
target list to be added soon:

- Lua  (already in progress)
- Falcon (interest from Falcon community indicated)
- C# (maybe via Mono)
- Java

## The Module API

The Module API is rather simple but powerful.  You can write modules
in C++ or even in the supported languages like Python.  The module
can really do anything it wants once it's loaded.

## The Binding API

The Module communicates to other modules through "binding". Binding
is the process of either adding values (primitive, objects, functions etc)
to the Tide runtime or retrieving them.  There are also a small number of
other utility functions like logging etc that are exposed by the "API module".

The binding implementation for each language knows how to box and unbox
values back and forth from the Tide runtime and the native language
runtime. This is the key part of the magic of Tide.

Once bound, you can invoke a function from Ruby which might take a Python
function as a reference and return a Javascript object.


