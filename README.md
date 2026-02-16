*This project has been created as part of the 42 curriculum by todina-r.*

# get_next_line

## Description

**get_next_line** is a C function that reads and returns a single line from a file descriptor at each call. The goal of this project is to implement an efficient and reusable line-reading mechanism while learning how to manage memory, file descriptors, and static variables in C.

The function allows sequential reading of a file or standard input without loading the entire content into memory. Each call returns the next available line, including the terminating newline character (`\n`) when present.

This project focuses on:
- File descriptor manipulation
- Buffered reading using `read`
- Memory management
- Persistent state handling through static variables

## Function Prototype

```c
char *get_next_line(int fd);
````

### Return values

* A line read from the file descriptor
* `NULL` if there is nothing left to read or if an error occurs

## How It Works

The implementation reads data from the file descriptor in fixed-size chunks defined by `BUFFER_SIZE`. The data is stored in a static buffer that preserves unread content between function calls.

The algorithm follows these steps:

1. Read from the file descriptor into a temporary buffer.
2. Append the new data to a persistent storage buffer.
3. Check for a newline character or end-of-file.
4. Extract and return the next complete line.
5. Keep the remaining data for the next call.
6. Repeat until end-of-file or error.

This approach ensures:

* Minimal reads from the file descriptor
* Efficient memory usage
* Correct handling of partial reads

## Compilation

Compile using:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 \
	main.c get_next_line.c get_next_line_utils.c
```

The program can compile both with and without the `-D BUFFER_SIZE` flag.

Example:

```bash
cc -Wall -Wextra -Werror main.c get_next_line.c get_next_line_utils.c
```

## Usage Example

```c
int fd;
char *line;

line = "";
fd = open("file.txt", O_RDONLY);
while (line)
{
    line = get_next_line(fd);
    if (line)
    {
        printf("%s", line);
        free(line);
    }
}
close(fd);
```

## Features

* Reads one line at a time from any valid file descriptor
* Works with files and standard input
* Handles variable buffer sizes (1 to around 1024000 by default)
* Memory-safe when properly used

## Project Structure

```bash
.
├── get_next_line_bonus.c
├── get_next_line_bonus.h
├── get_next_line.c
├── get_next_line.h
├── get_next_line_utils_bonus.c
├── get_next_line_utils.c
└── README.md
```

## Resources

* static variable theory: [wikipedia: static variable](https://en.wikipedia.org/wiki/Static_variable)
* static variable usage: [codecademy: c - static variable](https://www.codecademy.com/resources/docs/c/static-variables)
* 42 project subject documentation

### AI Usage

AI tools were used for documentation structuring and wording improvements.

AI was **not** used to generate or copy implementation code directly.
All logic and coding decisions were made and implemented by the project author.
