# GET_next_line

Get Next Line is the 3rd mandatory project at Hive Helsinki.

It is a function that reads a file and allows you to read a line ending with a newline character from a file descriptor. When you call the function again on the same file, it grabs the next line. This project deals with memory allocation and when to free and allocate memory to prevent leaks.

A (-1) is returned if an error occurred. A (0) is returned if the file is finished reading. And a (1) is returned if a line is read.
