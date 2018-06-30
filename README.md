<div align="center">
  <h1>tumbiChat</h1>

  <a href="https://travis-ci.org/manparvesh/tumbiChat/builds" target="_blank"><img src="https://img.shields.io/travis-ci/manparvesh/tumbiChat.svg?style=for-the-badge" alt="Build Status"></a> 
  <a href="https://manparvesh.mit-license.org/" target="_blank"><img src="https://img.shields.io/badge/license-MIT-blue.svg?longCache=true&style=for-the-badge" alt="License"></a> 
  
  <p>A simple chat server written in C++</p>
</div>

[![](https://github.com/manparvesh/tumbiChat/raw/master/demo.gif)](https://asciinema.org/a/hzKAqrxpKyGhL4obnoQYGXPDE?speed=2&theme=solarized-light&autoplay=1)

## Building
```
> git clone https://github.com/manparvesh/tumbiChat.git 
> mkdir build
> cd build
> cmake ..
> make
```

## Usage
- After compilation, go to the build directory.
- Run `./tumbiServer` with or without port as an argument to start the server.
- Run `./tumbiClient` with or without server port as an argument to connect to the server. Multiple users can connect to the server
- Messages sent be sent to all the connected users.
- all the messages will also be saved in a log file where the server is run.

## LICENSE
```
MIT License

Copyright (c) 2018 Man Parvesh Singh Randhawa

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```
