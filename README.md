# get_next_line
Reading a line on a file descriptor is too tedious :neutral_face:

### Table of Contents

* [Introduction](#introduction)
* [How it Works](#how-it-works)
* [Bonus](#bonus)
* [Installation](#installation)
* [Summary](#summary)


## Introduction

In this project we must create a function that returns one line every time it is called, followed by a newline if the line has it. This project introduces the idea of static variables, which will be very useful for future projects. On top of that, we'll also find a way to define macros right when compiling!

The function to implement is called ``get_next_line``, and will have the following prototype:
```C
char *get_next_line(int fd);
```
Note: As of July 2021 the prototype changed, previously the prototype was ``int get_next_line(int fd, char **line);``


* Input Parameters

The function only receives an int ``fd``, which will be the file descriptor of an open file, or perhaps even the standard input if the file descriptor is zero.


* Return Values

This function only has two possible return values:

| Return Value | Description |
| :----------: | :---------: |
| char * | The string containing a line read by the function |
| (null) | Either an error occurred or reached EOF (End Of File) |


## How it Works

* Function Overview

| Name | Description |
| :--: | :---------: |
| ``get_next_line(int fd)`` | Reads from ``fd`` and returns one line or ``NULL`` |
| ``gnl_newread(int fd)`` | Performs a new read of ``BUFFER_SIZE`` bytes and stores it in aux |
| ``gnl_expand_buffer(char *buf, int fd)`` | Expands the static variable ``buf`` with a new read |
| ``gnl_shrink_buffer(char *buf, char *line)`` | Shrinks static variable ``buf`` when a line has been selected |
| ``gnl_strlen(const char *s)`` | Returns length of a string |
| ``gnl_strchr_i(const char *s, int c)`` | Returns index of first occurrence of ``c`` in a string, or ``-1`` |
| ``gnl_strlcpy(char *dst, const char *src, size_t size)`` | Copies chars from ``src`` into ``dst``, ensuring ``\0`` |
| ``gnl_substr(char const *s, unsigned int start, size_t len)`` | Allocates enough memory and performs ``gnl_strlcpy`` |
| ``gnl_strlcat(char *dst, const char *src, size_t size)`` | Contatenates two strings |

As previously mentioned, this project takes advantage of static variables, i.e. variables that keep their value after the function being called again. My approach at this function is a recursive one. Every time the function runs, it checks if there's a newline in the static variable. If there isn't one, a new read is performed, increasing the size of the static variable. When a line is found, the line is returned and the static variable has that line removed from it (it shrinks). If no newline is found the program starts again, recursively. Eventually, when nothing new is read, the remains of the static variable are returned and the function lastly returns null.

## Bonus

The bonus part of this project is quite simple:

* ``Bonus 1`` Single static variable

My first approach at ```get_next_line``` already had one static variable (buffer).



* ``Bonus 2`` Make it work with several file descriptors

All I had to do was make the static variable an array of strings, each corresponding to one file descriptor.



## Installation

To test this out on your system, I recommend that you have the following packages installed:

```
gcc python-norminette valgrind
```


* Clone the repository

```shell
git clone https://github.com/madebypixel02/get_next_line.git
cd get_next_line
```

* Testing the function

This repository includes a main and a few sample txt files I used to test the function. The main opens two files to the file descriptors ``fd_1`` and ``fd_2``, and then loops throught fhe open files applying ``get_next_line`` to both open files and printing the lines until either file reading ends.

The compilation defines a value for the variable ``BUFFER_SIZE`` with the ``-D`` flag. You can modify this value to check how it performs.

``Mac OS`` Feel free to check for leaks by uncommenting the ``system("leaks a.out")``

```shell
gcc -Wall -Wextra -Werror get_next_line.c get_next_line_utils.c tests/main.c -D BUFFER_SIZE=42 && ./a.out | cat -e 
```


``Linux``

```shell
gcc -Wall -Wextra -Werror get_next_line.c get_next_line_utils.c tests/main.c -D BUFFER_SIZE=42 && valgrind -q --leak-check=full -s ./a.out | cat -e 

```

* Example

![get_next_line Test Gif](https://s6.gifyu.com/images/get_next_line.gif)

![get_next_line Test Image](https://i.imgur.com/HvTQBuu.png)

This is an example running the above command for ``linux``



* Available txt files

| Filename | Description | Ends with newline | Source |
| :------: | :---------: | :---------------: | :----: |
| ``empty.txt`` | Empty file | :x: | N/A |
| ``test.txt`` | A-Z with several newlines | :heavy_check_mark: | N/A |
| ``test2.txt`` | Shorter version of ``test.txt`` | :heavy_check_mark: | N/A |
| ``basic_oneline.txt`` | Single short line | :x: | N/A |
| ``the-king-james-bible.txt`` | Very long book (Holy Bible) | :heavy_check_mark: | [Link](https://github.com/ErikSchierboom/sentencegenerator/blob/master/samples/the-king-james-bible.txt) |
| ``big_line_no_nl.txt`` | very large single-line file (9999 chars) | :x: | [Link](https://github.com/Tripouille/gnlTester/blob/master/files/big_line_no_nl) |
| ``J. K. Rowling - Harry Potter 1 - Sorcerer's Stone.txt`` | Harry Potter full book | :heavy_check_mark: | [Link](https://github.com/amephraim/nlp/blob/master/texts/J.%20K.%20Rowling%20-%20Harry%20Potter%201%20-%20Sorcerer's%20Stone.txt) |

## Summary
This project was somewhat hard to grasp at first, but once I understood what to do it wasn't very hard to implement :)

July 17th, 2021
