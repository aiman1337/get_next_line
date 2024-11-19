/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouass <ahouass@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 12:25:04 by ahouass           #+#    #+#             */
/*   Updated: 2024/11/19 16:15:22 by ahouass          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	split_line(char *full_line, int i, char **line, char **saved_line)
{
	*line = ft_substr(full_line, 0, i + 1);
	*saved_line = ft_substr(full_line, i + 1, ft_strlen(full_line) - (i + 1));
	if (!*line || !*saved_line)
	{
		free(*line);
		free(*saved_line);
		*line = NULL;
		*saved_line = NULL;
	}
}

void	ft_extract_line(char *full_line, char **saved_line, char **line)
{
	int	i;

	if (!full_line || !*full_line)
	{
		*line = NULL;
		*saved_line = NULL;
		free(full_line);
		return ;
	}
	i = 0;
	while (full_line[i])
	{
		if (full_line[i] == '\n')
		{
			split_line(full_line, i, line, saved_line);
			free(full_line);
			return ;
		}
		i++;
	}
	*line = ft_strdup(full_line);
	*saved_line = NULL;
	free(full_line);
}

char	*update_saved_line(char *saved_line, char *buffer)
{
	char	*tmp;

	if (!saved_line)
		return (ft_strdup(buffer));
	tmp = saved_line;
	saved_line = ft_strjoin(tmp, buffer);
	free(tmp);
	if (!saved_line)
		return (NULL);
	return (saved_line);
}

char	*ft_get_line(int fd, char *buffer, char *saved_line)
{
	int		bytes_read;

	while (1)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		buffer[bytes_read] = '\0';
		saved_line = update_saved_line(saved_line, buffer);
		if (!saved_line)
			return (NULL);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	if (bytes_read < 0)
	{
		free(saved_line);
		saved_line = NULL;
		return (NULL);
	}
	return (saved_line);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*buffer;
	char		*full_line;
	static char	*saved_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
	{
		free(saved_line);
		saved_line = NULL;
		return (NULL);
	}
	full_line = ft_get_line(fd, buffer, saved_line);
	free(buffer);
	ft_extract_line(full_line, &saved_line, &line);
	return (line);
}
