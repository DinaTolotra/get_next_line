/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: todina-r <todina-r@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 18:52:25 by todina-r          #+#    #+#             */
/*   Updated: 2026/03/05 08:21:41 by todina-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

#ifndef EOL_SPEC
# define EOL_SPEC '\n'
#endif

static void	overwrite(char **dst, char *src)
{
	if (!dst)
		return ;
	if (*dst)
		free(*dst);
	*dst = src;
}

static char	*find_eol(char *line, char eol)
{
	char	*temp;

	temp = 0;
	if (line)
		temp = ft_strchr(line, eol);
	return (temp);
}

static char	*join(char *line, char *data, char delim)
{
	char	*temp;
	char	*p_eol;
	char	*n_line;
	size_t	data_size;

	data_size = ft_strlen(data);
	if (!data_size)
		return (line);
	p_eol = ft_strchr(data, delim);
	if (!p_eol)
		p_eol = data + data_size;
	temp = ft_substr(data, 0, p_eol - data + 1);
	n_line = ft_strjoin(line, temp);
	if (*p_eol == delim)
		p_eol++;
	ft_strlcpy(data, p_eol, BUFFER_SIZE);
	if (temp)
		free(temp);
	return (n_line);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*temp;
	static char	data[BUFFER_SIZE + 1];
	ssize_t		data_size;

	temp = 0;
	line = 0;
	data_size = 1;
	line = join(line, data, EOL_SPEC);
	temp = find_eol(line, EOL_SPEC);
	while (!temp && data_size > 0)
	{
		data_size = read(fd, data, BUFFER_SIZE);
		if (data_size > 0)
		{
			data[data_size] = 0;
			temp = join(line, data, EOL_SPEC);
			overwrite(&line, temp);
		}
		temp = find_eol(line, EOL_SPEC);
	}
	if (data_size == -1 && line)
		overwrite(&line, 0);
	return (line);
}
