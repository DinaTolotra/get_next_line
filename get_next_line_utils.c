/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: todina-r <todina-r@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 06:26:36 by todina-r          #+#    #+#             */
/*   Updated: 2026/02/16 11:23:53 by todina-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	index;

	index = 0;
	while (s[index])
		index++;
	return (index);
}

char	*ft_strchr(const char *s, int c)
{
	size_t		index;
	const char	*res;

	res = 0;
	index = 0;
	while (s[index] && s[index] != (char)c)
		index++;
	if (s[index] == (char)c)
		res = &s[index];
	return ((char *)res);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	index;
	size_t	len;

	index = 0;
	while (index + 1 < size && src[index])
	{
		dst[index] = src[index];
		index++;
	}
	if (size)
		dst[index] = 0;
	len = index;
	while (src[len])
		len++;
	return (len);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub_s;
	size_t	s_len;

	if (s == 0)
		return (0);
	s_len = ft_strlen(s);
	if (s_len < start)
	{
		len = 0;
		start = s_len;
	}
	else if (s_len - start < len)
		len = s_len - start;
	sub_s = malloc(sizeof(char) * (len + 1));
	if (sub_s == 0)
		return (0);
	ft_strlcpy(sub_s, s + start, len + 1);
	sub_s[len] = 0;
	return (sub_s);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	size_t	s1_len;
	size_t	s2_len;

	s1_len = 0;
	if (s1 == 0 || s2 == 0)
		return (0);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	res = malloc(sizeof(char) * (s2_len + s1_len + 1));
	if (res == 0)
		return (0);
	ft_strlcpy(res, s1, s2_len + s1_len + 1);
	ft_strlcpy(res + s1_len, s2, s2_len + 1);
	return (res);
}
