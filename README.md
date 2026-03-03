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
```

### Return values

* A line read from the file descriptor
* `NULL` if:
	* end-of-file reached and buffer is empty
	* an error occured
	* the file descriptor is invalid

## How It Works

The implementation reads data from the file descriptor in fixed-size chunks defined by `BUFFER_SIZE`. The data is stored in a static buffer that preserves unread content between function calls.

The algorithm follows these steps:

1. Read from the file descriptor into a temporary buffer.
2. Append the new data to a persistent storage buffer.
3. Check for a newline character or end-of-file.
4. Extract and return the next complete line.
5. Keep the remaining data for the next call.
6. Repeat until end-of-file or error.

For the bonus part, the buffer are indexed via the given `fd`.

This approach ensures:

* Minimal reads from the file descriptor
* Correct handling of partial reads

## Compilation

Compile using:

```bash
# Mandatory
cc -Wall -Wextra -Werror
	main.c get_next_line.c get_next_line_utils.c
```
```bash
# Bonus
cc -Wall -Wextra -Werror
	main.c get_next_line_bonus.c get_next_line_utils_bonus.c
```

The program can compile both with and without the `-D BUFFER_SIZE` flag.
Avalaible macros:
* `BUFFER_SIZE` = 42 : size of the buffer used for `read`
* `EOL_SPEC` = '\n' : the character specifying the 'end of line'
* `FD_MAX` = 128 : the maximum value of the fd passed as parameter (bonus)

Example:

```bash
# Mandatory
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 -D "EOL_SPEC='\n'" \
    main.c get_next_line.c get_next_line_utils.c
```
```bash
# Bonus
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 -D "EOL_SPEC='\n'" -D FD_MAX=128 \
    main.c get_next_line_bonus.c get_next_line_utils_bonus.c
```

## Usage Example

* For mandatory part:
```c
#include <stdio.h>
#include <fcntl.h>

#include "get_next_line.h"

int	main(int ac, char **av)
{
	int fd;
	char *line;

	fd = 0;
	line = "";
	if (ac == 2)
		fd = open(av[1], O_RDONLY);
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
}
```

* For bonus part:
```c
#include <stdio.h>
#include <fcntl.h>

#include "get_next_line.h"

int	main(int ac, char **av)
{
	int fd1;
	int fd2;
    int f1_index;
    int f2_index;
	char *line;

	fd1 = 0;
	fd2 = 0;
    f1_index = 0;
    f2_index = 0;
	line = "";
	if (ac == 3)
    {
		fd1 = open(av[1], O_RDONLY);
		fd2 = open(av[2], O_RDONLY);
    }
	while (line)
	{
		line = get_next_line(fd1);
		if (line)
		{
			printf("%10s: %3i | %s", av[1], f1_index, line);
			free(line);
		}
		line = get_next_line(fd2);
		if (line)
		{
			printf("%10s: %3i | %s", av[2], f2_index, line);
			free(line);
		}
	}
	close(fd1);
	close(fd2);
}
```

## Features

* Reads one line at a time from any valid file descriptor
* Works with files and standard input
* Handles variable buffer sizes (1 to around 1024000 by default)
* Handles variable end-of-file specifier
* Handles several file descriptor (bonus)
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
