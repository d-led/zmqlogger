Summary
=======

This is currently a research on using the [wonderful asynchronous C++11 logger g2log](http://www.codeproject.com/Articles/288827/g2log-An-efficient-asynchronous-logger-using-Cplus) as a back-end
for a [zeromq](http://www.zeromq.org/) based logging server.

The goal is to provide a possibility of asynchronous logging on client-side (using zeromq) and a fast asynchronous log message persistence on the server side using g2log.

Details
=======

Usage
-----

 * update the git submodules
 * [download g2log](https://bitbucket.org/KjellKod/g2log/overview) and extract the folder contents into the g2log folder
 * Open the solution with Visual Studio 2012 (i.e. Express for Desktop), compile and run (zmqlogger and then zmqloggerclient)

Status
------

Right now nothing works.

Contributions are welcome!

License
=======

Author: Dmitry Ledentsov

MIT License (http://www.opensource.org/licenses/mit-license.php)

dependencies retain their respective licenses
