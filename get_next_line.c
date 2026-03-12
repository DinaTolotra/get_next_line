/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: todina-r <todina-r@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 18:52:25 by todina-r          #+#    #+#             */
/*   Updated: 2026/03/12 08:10:33 by todina-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*find_eol(char *p, size_t read_size)
{
	char	*p_eol;

	if (p == 0)
		return (0);
	p_eol = ft_strchr(p, EOL_SPEC);
	if (!p_eol && read_size < BUFFER_SIZE)
		p_eol = ft_strchr(p, 0);
	return (p_eol);
}

static char	*overwrite(char *dst, char *src)
{
	if (dst)
		free(dst);
	return (src);
}

static char	*extract_line(char **buffer, char *p_eol)
{
	char	*line;
	char	*temp;
	size_t	line_size;
	size_t	buffer_size;

	temp = 0;
	line_size = p_eol - *buffer + 1;
	buffer_size = ft_strlen(*buffer);
	line = ft_substr(*buffer, 0, line_size);
	if (buffer_size > line_size)
	{
		temp = ft_substr(*buffer, line_size, buffer_size);
		*buffer = overwrite(*buffer, temp);
	}
	else
		*buffer = overwrite(*buffer, 0);
	return (line);
}

static ssize_t	read_data(int fd, char *data)
{
	ssize_t	size;

	size = read(fd, data, BUFFER_SIZE);
	if (size != -1)
		data[size] = 0;
	return (size);
}

char	*get_next_line(int fd)
{
	char			*data;
	ssize_t			data_size;
	static char		*buffer;
	char			*temp;
	char			*line;

	line = 0;
	data_size = -1;
	data = malloc(BUFFER_SIZE + 1);
	while (BUFFER_SIZE > 0 && fd >= 0 && data && !line)
	{
		data_size = read_data(fd, data);
		if (data_size == -1 || (!data_size && (!buffer || !buffer[0])))
			break ;
		temp = ft_strjoin(buffer, data);
		buffer = overwrite(buffer, temp);
		temp = find_eol(buffer, data_size);
		if (temp)
			line = extract_line(&buffer, temp);
	}
	data = overwrite(data, 0);
	if (data_size == -1)
		buffer = overwrite(buffer, 0);
	return (line);
}
