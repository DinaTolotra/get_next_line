/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: todina-r <todina-r@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 18:52:25 by todina-r          #+#    #+#             */
/*   Updated: 2026/02/16 11:23:38 by todina-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

#ifndef EOL_SPEC
# define EOL_SPEC '\n'
#endif

char	*find_eol(char *p, size_t read_size)
{
	char	*p_eol;

	p_eol = ft_strchr(p, EOL_SPEC);
	if (!p_eol && read_size < BUFFER_SIZE)
		p_eol = ft_strchr(p, 0);
	return (p_eol);
}

char	*overwrite(char *dst, char *src)
{
	if (dst)
		free(dst);
	dst = src;
	return (dst);
}

char	*extract_line(char **buffer, char *p_eol)
{
	char	*line;
	char	*temp;
	size_t	line_size;
	size_t	buffer_size;

	temp = 0;
	line_size = p_eol - *buffer + 1;
	buffer_size = ft_strlen(*buffer);
	buffer_size = buffer_size - line_size;
	line = ft_substr(*buffer, 0, line_size);
	if (buffer_size)
		temp = ft_substr(*buffer, line_size, buffer_size);
	*buffer = overwrite(*buffer, temp);
	return (line);
}

size_t	read_data(int fd, char *data)
{
	size_t	size;

	size = read(fd, data, BUFFER_SIZE);
	data[size] = 0;
	return (size);
}

char	*get_next_line(int fd)
{
	char			data[BUFFER_SIZE + 1];
	size_t			data_size;
	static char		*buffer;
	char			*temp;
	char			*line;

	line = 0;
	while (!line)
	{
		temp = 0;
		data_size = read_data(fd, data);
		if (!data_size && (!buffer || !buffer[0]))
			return (0);
		if (buffer)
			temp = ft_strjoin(buffer, data);
		else
			temp = ft_strjoin("", data);
		buffer = overwrite(buffer, temp);
		temp = find_eol(buffer, data_size);
		if (temp)
			line = extract_line(&buffer, temp);
	}
	return (line);
}
