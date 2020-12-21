/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbisscho <lbisscho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/20 13:28:36 by lbisscho      #+#    #+#                 */
/*   Updated: 2020/11/07 14:34:20 by lbisscho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_free_tmp(char **tmp, int check, size_t *i)
{
	*i = 0;
	if (check == 1)
	{
		free(*tmp);
		return (-1);
	}
	free(*tmp);
	return (0);
}

static int	ft_next_line_found(char *tmp, size_t *i, char **line, size_t *j)
{
	(*line) = gnl_strndup(&tmp[*j], *i - *j);
	if (!(*line))
		return (ft_free_tmp(&tmp, 1, i));
	(*i)++;
	return (1);
}

static char	*ft_fill_tmp(char *tmp, int *ret)
{
	tmp = malloc(1);
	if (tmp)
	{
		tmp[0] = '\0';
		*ret = 1;
		return (tmp);
	}
	return (0);
}

static void	ft_read_join(int fd, char **buf, char **tmp, int *ret)
{
	*buf = malloc(BUFFER_SIZE + 1);
	if (*buf)
	{
		*ret = read(fd, *buf, BUFFER_SIZE);
		if (*ret >= 0)
		{
			(*buf)[*ret] = '\0';
			*tmp = gnl_strjoin(*tmp, *buf);
		}
		free(*buf);
	}
}

int			get_next_line(int fd, char **line)
{
	char			*buf;
	static	int		ret;
	static	size_t	i;
	static	size_t	j;
	static	char	*tmp;

	j = i;
	if (j == 0)
		tmp = ft_fill_tmp(tmp, &ret);
	while (ret > 0)
	{
		if (tmp[i] == '\0')
		{
			ft_read_join(fd, &buf, &tmp, &ret);
			if (!tmp || ret < 0 || !buf)
				return (ft_free_tmp(&tmp, 1, &i));
		}
		if (tmp[i] == '\n')
			return (ft_next_line_found(tmp, &i, line, &j));
		i++;
	}
	(*line) = gnl_strdup(&tmp[j]);
	if (!*line)
		return (ft_free_tmp(&tmp, 1, &i));
	return (ft_free_tmp(&tmp, 0, &i));
}
