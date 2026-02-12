/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: todina-r <todina-r@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 18:52:25 by todina-r          #+#    #+#             */
/*   Updated: 2026/02/12 06:35:12 by todina-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

#ifndef EOL_SPEC
# define EOL_SPEC '\n'
#endif

char	*sub_mem(char *p, size_t start, size_t sub_len)
{
	char	*sub;
	size_t	index;

	index = 0;
	if (!sub_len)
		return (0);
	sub = malloc(sub_len + 1);
	while (index < sub_len)
	{
		sub[index] = p[start + index];
		index++;
	}
	sub[sub_len] = 0;
	return (sub);
}

char	*find_eol(char *p, size_t size, size_t read_size)
{
	size_t	index;

	index = 0;
	while (index < size + read_size)
	{
		if (p[index] == EOL_SPEC)
			return (p + index + 1);
		index++;
	}
	if (read_size < BUFFER_SIZE)
		return (p + size);
	return (0);
}

char	*overwrite(char *dst, char *src)
{
	if (dst)
		free(dst);
	dst = src;
	return (dst);
}

char	*mem_join(char *p1, char *p2, size_t p1_s, size_t p2_s)
{
	char	*new_p;
	size_t	index;

	index = 0;
	new_p = malloc(p1_s + p2_s);
	while (index < p1_s)
	{
		new_p[index] = p1[index];
		index++;
	}
	while (index - p1_s < p2_s)
	{
		new_p[index] = p2[index - p1_s];
		index++;
	}
	return (new_p);
}

char	*get_next_line(int fd)
{
	char			data[BUFFER_SIZE];
	static char		*buffer;
	static size_t	buffer_size;
	size_t			data_size;
	char			*temp;
	char			*line;
	size_t			line_size;

	line = 0;
	if (!buffer)
		buffer_size = 0;
	data_size = 0;
	while (!line)
	{
		data_size = read(fd, data, BUFFER_SIZE);
		if (!data_size && !buffer)
			return (0);
		temp = mem_join(buffer, data, buffer_size, data_size);
		buffer_size = buffer_size + data_size;
		buffer = overwrite(buffer, temp);
		temp = find_eol(buffer, buffer_size, data_size);
		if (temp)
		{
			line_size = (unsigned long)(temp) - (unsigned long)(buffer);
			line = sub_mem(buffer, 0, line_size);
			temp = sub_mem(buffer, line_size, buffer_size - line_size);
			buffer_size = buffer_size - line_size;
			buffer = overwrite(buffer, temp);
		}
	}
	return (line);
}

int	main(void)
{
	char	*line;

	line = "";
	while (line)
	{
		line = get_next_line(0);
		if (line)
		{
			printf("[%s]", line);
			free(line);
		}
	}
	return (0);
}
