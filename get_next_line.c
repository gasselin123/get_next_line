/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 12:50:24 by gasselin          #+#    #+#             */
/*   Updated: 2021/05/13 10:52:49 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_get_index(char *save)
{
	int	i;

	i = 0;
	while (save[i] && save[i] != '\n')
		i++;
	return (i);
}

char	*ft_getsave(char *buff, char **line, char *save)
{
	char	*str;
	int		i;
	int		j;

	j = 0;
	free(buff);
	*line = ft_getline(save);
	if (!save)
		return (0);
	i = ft_get_index(save);
	if (!save[i])
	{
		free(save);
		return (0);
	}
	str = (char *)malloc(sizeof(char) * ((ft_strlen(save) - i) + 1));
	if (!str)
		return (0);
	i++;
	while (save[i])
		str[j++] = save[i++];
	str[j] = '\0';
	free(save);
	return (str);
}

char	*ft_getline(char *save)
{
	int		i;
	int		j;
	char	*str;

	j = 0;
	if (!save)
		return (0);
	i = ft_get_index(save);
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (!str)
		return (0);
	while (j < i)
	{
		str[j] = save[j];
		j++;
	}
	str[j] = '\0';
	return (str);
}

int	get_next_line(int fd, char **line)
{
	char		*buff;
	int			reading;
	static char	*save;

	reading = 1;
	if (!line || fd < 0 || BUFFER_SIZE <= 0)
		return (-1);
	buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (-1);
	while (!ft_is_end_of_line(save) && reading != 0)
	{
		reading = read(fd, buff, BUFFER_SIZE);
		if (reading == -1)
		{
			free(buff);
			return (-1);
		}
		buff[reading] = '\0';
		save = ft_strjoin(save, buff);
	}
	save = ft_getsave(buff, &*line, save);
	if (reading == 0)
		return (0);
	return (1);
}
