# matrix_ee

The tools for my study, especially for "The Theorem of Electrical Circuit".

## Build info

This app depends on `regex.h` \([document link](https://www.gnu.org/software/libc/manual/html_node/Regular-Expressions.html)\). It only can be gained on Linux platform. So, this app couldn't be compiled on Windows without any libraries. But you can use [this library](http://gnuwin32.sourceforge.net/packages/regex.htm) to try to build it on Windows. I test it but I couldn't build it due to undefined reference error.

Maybe building this app on Linux platform is a good idea if you don't want any complex configuration.

Due to this, Debugging this app on Windows maybe a hardwork. My solution is that run gdb-server in WSL and use VSCode on Windows to debug this app.
