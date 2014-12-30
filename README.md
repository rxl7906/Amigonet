#AmigoNet

AmigoNet maintains a collection of users that have friend ("amigo") connections between them. It is loosely based on some elementary features in a system like Facebook or Linkedin. Some operations that are supported as connecting ("friending") and disconnecting ("un-friending") users, as well as determining the distance, or degrees of separation between two users. 

## Data Structure

The AmigoNet uses a linked list of linked lists. The linked list is all 
the users in the "social network". Each user has their own linked list 
which is essentially their friend list. 

## Installation

1. Download MinGW to obtain the GNU Compiler Collection(GNU) for compiling C programs. 
2. Download zip file.

## Usage

1. Use header.mak to generate the make file and use the make file to create the executable. (If already made, skip this step)
2. Type "./amigosim" to create a amigonet. Or type "./amigosim < scenario1.txt" to redirect the input directly. 
3. See "scenario1.txt" for input test cases. 


## History

Project 2 of CSCI243 - Mechanics of Programming 

## Credits

Author: Robin Li

## License

The MIT License (MIT)

Copyright (c) 2014 Robin Li

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
