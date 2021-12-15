/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acamaras <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 12:26:20 by acamaras          #+#    #+#             */
/*   Updated: 2021/12/07 17:19:06 by acamaras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	find_line(char **str, char **line)
{
	int		i;
	char	*temp;

	i = 0;
	while ((*str)[i] != '\0' && (*str)[i] != '\n')
		i++;
	if ((*str)[i] == '\n')
	{
		*line = ft_strsub(*str, 0, i);
		temp = ft_strdup(&((*str)[i + 1]));
		free(*str);
		*str = temp;
		if ((*str)[0] == '\0')
			ft_strdel(str);
	}
	else
	{
		*line = ft_strdup(*str);
		ft_strdel(str);
	}
	return (1);
}

static int	check_output(char **str, char **line, int ret, const int fd)
{
	if (ret < 0)
	{
		ft_memdel((void **)str);
		return (-1);
	}
	else if (str[fd] == NULL && ret == 0)
	{
		ft_memdel((void **)str);
		return (0);
	}
	else
		return (find_line(&str[fd], line));
}

int	get_next_line(const int fd, char **line)
{
	static char	*str[FD_SIZE];
	char		buff[BUFF_SIZE + 1];
	char		*temp;
	int			ret;

	if (fd < 0 || line == NULL || fd >= FD_SIZE || BUFF_SIZE <= 0)
		return (-1);
	ret = read(fd, buff, BUFF_SIZE);
	while (ret > 0)
	{
		buff[ret] = '\0';
		if (str[fd] == NULL)
			str[fd] = ft_strdup(buff);
		else
		{
			temp = ft_strjoin(str[fd], buff);
			free(str[fd]);
			str[fd] = temp;
		}
		if (ft_strchr(str[fd], '\n'))
			break ;
		ret = read(fd, buff, BUFF_SIZE);
	}
	return (check_output(str, line, ret, fd));
}
