ezio - A library for doing simple I/O operations (sockets and files) in C++
===========================================================================

Premises
--------

* Easy things should be easy
* Hard things should be easy, but not at the expense of easy things
  being hard
* Programs should be fast, but not at the expense of legibility
* Polymorphism is not expensive in an IO-bound application
* Memory allocations can be expensive and should be avoidable in the
  critical path
* Abstractions should be intuitive for someone familiar with the
  underlying C API
* Templates make programs slower to compile.  They shouldn't be
  avoided altogether, but it should be possible to write a
  fully-functional application without using any of the template API.
* Source code should be simple and easy to read.  It should not be
  unnecessarily complicated with workarounds for broken compilers or
  non-POSIX-compliant operating systems.
* The library does NOT attempt to be an all-inclusive wrapper for
  every single C function; if there's a function that's not included,
  it should be relatively simple to call that function directly.
* Whenever possible the library should provide access to the
  underlying C data types

Why libevent instead of libev?
------------------------------

* Feel free to write a libev-based reactor.  I chose libevent because
  it had better documentation.

HTTP/FTP/etc.?
--------------

* Not currently supported, but could be in the future.  Maybe a
  libcurl wrapper?

Requirements
-------------

* gmake
* POSIX.1-2001

