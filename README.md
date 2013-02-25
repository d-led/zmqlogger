Summary
=======

This is currently a research on using the [wonderful asynchronous C++11 logger g2log](http://www.codeproject.com/Articles/288827/g2log-An-efficient-asynchronous-logger-using-Cplus) as a back-end
for a [zeromq](http://www.zeromq.org/) based logging server.

The goal is to provide a possibility of asynchronous logging on client-side (using zeromq) and a fast asynchronous log message persistence on the server side using g2log.
The log entries can be formatted client-side using [picojson](https://github.com/kazuho/picojson) with a client-side time-stamp, for example.

Details
=======

Usage
-----

 * update the git submodules
 * [download or checkout g2log](https://bitbucket.org/KjellKod/g2log/overview) and extract the folder contents into the g2log folder
 * Be sure to have the bin directory of 0mq available in the path, i.e. by extending the PATH variable in environment settings for debugging in VS
 * Open the solution with Visual Studio 2012 (i.e. Express for Desktop), compile and run (zmqlogger and then zmqloggerclient)

Status
------

 * Right simple test client and server are available
 * The communication is asynchronous
 * No wrapper for the client side exist
 * A deadlock has to be solved

Todo
----

 * Create a client library (deployable as a couple of dlls, perhaps)

Contributions are welcome!

License
=======

Author: Dmitry Ledentsov

MIT License (http://www.opensource.org/licenses/mit-license.php)

dependencies retain their respective licenses
