#include "shell.h"

/**
 * print_to_stderr - Prints an input string to stderr
 * @str: The string to be printed
 *
 * Return: Nothing
 */
void _eputs(char *str)
{
	int index = 0;

	if (!str)
		return;

	while (str[index] != '\0')
	{
		_eputchar(str[index]);
		index++;
	}
}

/**
 * write_char_to_stderr - Writes the character c to stderr
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _eputchar(char c)
{
	static int buffer_index;
	static char buffer[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || buffer_index >= WRITE_BUF_SIZE)
	{
		write(2, buffer, buffer_index);
		buffer_index = 0;
	}

	if (c != BUF_FLUSH)
		buffer[buffer_index++] = c;

	return (1);
}

/**
 * write_char_to_fd - Writes the character c to the given file descriptor
 * @c: The character to print
 * @fd: The file descriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putfd(char c, int fd)
{
	static int buffer_index;
	static char buffer[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || buffer_index >= WRITE_BUF_SIZE)
	{
		write(fd, buffer, buffer_index);
		buffer_index = 0;
	}

	if (c != BUF_FLUSH)
		buffer[buffer_index++] = c;

	return (1);
}

/**
 * print_str_to_fd - Prints an input string to the given file descriptor
 * @str: The string to be printed
 * @fd: The file descriptor to write to
 *
 * Return: The number of characters written
 */
int _putsfd(char *str, int fd)
{
	int char_count = 0;

	if (!str)
		return (0);

	while (*str)
	{
		char_count += _putfd(*str++, fd);
	}

	return (char_count);
}
