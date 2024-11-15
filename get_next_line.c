/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouass <ahouass@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 12:25:04 by ahouass           #+#    #+#             */
/*   Updated: 2024/11/15 19:55:51 by ahouass          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_extract_line(char *full_line, char **saved_line, char **line)
{
	int i;

	i = 0;
	while(full_line[i])
	{
		if (full_line[i] == '\n')
		{
			*line = ft_substr(full_line, 0, i + 1);
			*saved_line = ft_substr(full_line, i + 1, ft_strlen(full_line) - (i + 1));
			return ;
		}
		i++;
	}
	*line = ft_strdup(full_line);
	*saved_line = NULL;
	free(full_line);
}

char	*ft_get_line(int fd, char *buffer, char *saved_line)
{
	int		bytes_read;
	char	*tmp;
	
	while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[bytes_read] = '\0';
		if (!saved_line)
			saved_line = ft_strdup(buffer);
		else
		{
			tmp = saved_line;
			saved_line = ft_strjoin(tmp, buffer);
			free(tmp);
		}
		if (ft_strchr(buffer, '\n'))
			break;
	}
	return (saved_line);
}
#include <stdio.h>
char	*get_next_line(int fd)
{
	char		*line;
	char		*buffer;
	int			bytes_read;
	char		*full_line;
	static char	*saved_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc(BUFFER_SIZE + 1);
	full_line = ft_get_line(fd, buffer, saved_line);
	ft_extract_line(full_line, &saved_line, &line);
	return (line);
}
