# get_next_line | 42 Madrid

*Reading a line on a file descriptor is too tedious :neutral_face:*

<p align="center">
  <img src=https://user-images.githubusercontent.com/40824677/149225116-4bc0f52c-1891-419a-853b-ac220c893fea.png />
</p>

### Table of Contents

* [Introduction](#introduction)
* [How it Works](#how-it-works)
* [Bonus](#bonus)
* [Installation](#installation)
* [Summary](#summary)


## Introduction

In this project we must create a function that returns one line from the specified fd every time it is called, followed by a newline if the line has one. This project introduces the idea of static variables, which will be very useful for future projects. On top of that, we'll also learn a way to define macros right when compiling!

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
| ``get_next_line`` | Reads from ``fd`` and returns one line or ``NULL`` |
| ``gnl_newread`` | Performs a new read of ``BUFFER_SIZE`` bytes and stores it in aux |
| ``gnl_expand_buffer`` | Expands the static variable ``buf`` with a new read |
| ``gnl_shrink_buffer`` | Shrinks static variable ``buf`` when a line has been found |
| ``gnl_strlen`` | Returns length of a string |
| ``gnl_strchr_i`` | Returns index of first occurrence of ``c`` in a string, or ``-1`` |
| ``gnl_strlcpy`` | Copies chars from ``src`` into ``dst``, ensuring ``\0`` |
| ``gnl_substr`` | Allocates enough memory and performs ``gnl_strlcpy`` |
| ``gnl_strlcat`` | Contatenates two strings |

As previously mentioned, this project takes advantage of static variables, i.e. variables that keep their value after the function being called again. My approach at this function is a recursive one. Every time the function runs, it checks if there's a newline in the static variable. If there isn't one, a new read is performed, increasing the size of the static variable. When a line is found, the line is returned and the static variable has that line removed from it (it shrinks). If no newline is found the program starts again, recursively. Eventually, when nothing new is read, the remains of the static variable are returned and the function lastly returns null.

## Bonus

The bonus part of this project is quite simple:

* ``Bonus 1`` Single static variable

My first approach at ``get_next_line`` already had one static variable (buffer).



* ``Bonus 2`` Make it work with several file descriptors

All I had to do was make the static variable an array of strings, each corresponding to one file descriptor.



## Installation

To test this out on your system, I recommend that you have the following packages installed:

```
gcc clang python-norminette (valgrind on linux)
```


* Clone the repository

```shell
git clone https://github.com/madebypixel02/get_next_line.git
cd get_next_line
```

* Testing the function

This repository includes a main and a few sample txt files I used to test the function. The main program opens a file to the file descriptor ``fd_1``, and then loops through the open file applying ``get_next_line`` to the file printing the lines until the file reading ends.

The compilation defines a value for the variable ``BUFFER_SIZE`` with the ``-D`` flag. You can modify this value to check how differently it performs.

``Mac OS``: Feel free to check for leaks by adding the ``system("leaks a.out")`` to the file

```shell
gcc -Wall -Wextra -Werror get_next_line.c get_next_line_utils.c tests/main.c -D BUFFER_SIZE=42 && ./a.out | cat -e 
```
Note: Because of printf's buffer management, you might not see the leak report at the bottom of the output, scroll up in the output and you'll see it buried in the output


``Linux``

```shell
gcc -Wall -Wextra -Werror get_next_line.c get_next_line_utils.c tests/main.c -D BUFFER_SIZE=42 && valgrind -q --leak-check=full -s ./a.out | cat -e 

```

* Examples

![get_next_line Test Image](https://i.imgur.com/HvTQBuu.png)

This is an example running the above command for ``linux``



* Available txt files

| Filename | Description | Ends with newline | Source |
| :------: | :---------: | :---------------: | :----: |
| ``empty.txt`` | Empty file | :x: | N/A |
| ``test.txt`` | A-Z with several newlines | :heavy_check_mark: | N/A |
| ``test2.txt`` | Shorter version of ``test.txt`` | :heavy_check_mark: | N/A |
| ``basic_oneline.txt`` | Single short line A-Z | :x: | N/A |
| ``the-king-james-bible.txt`` | Very long book (Holy Bible) | :heavy_check_mark: | [Link](https://github.com/ErikSchierboom/sentencegenerator/blob/master/samples/the-king-james-bible.txt) |
| ``big_line_no_nl.txt`` | Long single-line file (9999 chars) | :x: | [Link](https://github.com/Tripouille/gnlTester/blob/master/files/big_line_no_nl) |
| ``J. K. Rowling - Harry Potter 1 - Sorcerer's Stone.txt`` | Harry Potter book | :heavy_check_mark: | [Link](https://github.com/amephraim/nlp/blob/master/texts/J.%20K.%20Rowling%20-%20Harry%20Potter%201%20-%20Sorcerer's%20Stone.txt) |
| ``J. K. Rowling - Harry Potter 3 - Prisoner of Azkaban.txt`` | Harry Potter book | :heavy_check_mark: | [Link](https://github.com/amephraim/nlp/blob/master/texts/J.%20K.%20Rowling%20-%20Harry%20Potter%203%20-%20Prisoner%20of%20Azkaban.txt) |

Note: if you use the ``main.c`` with a large ``BUFFER_SIZE`` you might get reports (from valgrind) saying that some bytes are still reachable. This is normal since it happens when the program has finished but the static variable hasn't been emptied yet, which is the case here with my main.

## Summary
This project was somewhat hard to grasp at first, but once I understood what to do it wasn't too hard to implement

July 17th, 2021

<p align="center">
  <a href="https://github.com/madebypixel02/ft_printf">&#11013;</a>
  <a href="https://github.com/madebypixel02/42-Madrid-Cursus">&#127968;</a>
  <a href="https://github.com/madebypixel02/born2beroot">&#10145;</a>
</p>
