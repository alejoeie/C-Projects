# C-Projects
What's up coders! This repo is intended to show some advance into my personal coding skills using C,
my favorite language. 

Here I show some basic examples if you want to start a new coding path into C programming language.
The first example is that I created a ZMQ server and client to communicate over a socket id for
managing messages between two processes (terminal 1 and terminal 2). This is intended to practice
sockets, threads, processes and use concurrent programming, which is a mystic technique for ensuring
your code is optimized in terms of speed and performance. 

The other one is a data processing exercise using a probability algoritm called the Maximum 
Verosimilitude Function, in which the main function of the program is to set wheter a given value from
an observation corresponds to M1 or M2 message, thinking about a emitter that sends out different types
of messages. For an easier implementation, I used two messages, but I coded the script to ensure its 
scalability. 

Have fun with ZMQ and data processing algorithms. 


## ZMQ instructions
This folder contains an example program from czmq library. (ZMQ for C). Note that czmq corresponds to a high level
API for libzmq.

## Build instructions
``` console
$ git clone https://github.com/zeromq/libzmq.git
$ cd libzmq
$ mkdir build
$ cd build
$ cmake ..
$ sudo make install
$ sudo ldconfig

```
```console
$ git clone https://github.com/zeromq/czmq.git
$ cd czmq
$ mkdir build
$ cd build
$ cmake ..
$ sudo make install
$ sudo ldconfig
```
From the root of this directory:

``` console
cd src
mkdir build
cd build
cmake ..
sudo make install
```
