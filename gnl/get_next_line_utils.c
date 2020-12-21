/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbisscho <lbisscho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/20 13:39:37 by lbisscho      #+#    #+#                 */
/*   Updated: 2020/11/07 14:34:15 by lbisscho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t		ft_strlen(const char *str)
{
	size_t i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

char		*gnl_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*str3;

	i = 0;
	j = 0;
	if (s1 == NULL)
		return (NULL);
	str3 = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str3)
		return (NULL);
	while (s1[i] != '\0')
	{
		str3[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		str3[i] = s2[j];
		j++;
		i++;
	}
	str3[i] = '\0';
	free(s1);
	return (str3);
}

char		*gnl_strdup(const char *s1)
{
	size_t	i;
	char	*s2;

	if (!s1)
		return (NULL);
	s2 = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!s2)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

char		*gnl_strndup(char *str, size_t end)
{
	size_t		i;
	char		*newstr;

	i = 0;
	if (!str)
		return (NULL);
	while (i < end && str[i] != '\0')
		i++;
	newstr = malloc(sizeof(char) * (i + 1));
	if (!newstr)
		return (NULL);
	i = 0;
	while (i < end && str[i] != '\0')
	{
		newstr[i] = str[i];
		i++;
	}
	newstr[i] = '\0';
	return (newstr);
}
