/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 03:08:36 by adesvall          #+#    #+#             */
/*   Updated: 2020/12/01 13:55:58 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int		ft_strlen(const char *s)
{
	int i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t i;

	if (n == 0)
		return (dest);
	if (src == 0 && dest == 0)
		return (0);
	if (dest > src)
	{
		i = n;
		while (i >= 1)
		{
			i--;
			((char*)dest)[i] = ((char*)src)[i];
		}
	}
	else
	{
		i = 0;
		while (i < n)
		{
			((char*)dest)[i] = ((char*)src)[i];
			i++;
		}
	}
	return (dest);
}

char	*join_and_realloc(char *s1, char *s2)
{
	size_t	lens1;
	size_t	lens2;
	size_t	lentot;
	char	*res;

	if (!s1 && !s2)
		return (0);
	lens1 = ft_strlen(s1);
	lens2 = ft_strlen((s2));
	lentot = lens1 + lens2 + 1;
	res = malloc(sizeof(char) * lentot);
	if (!res)
	{
		free(s1);
		free(s2);
		return (0);
	}
	ft_memmove(res, s1, lens1);
	ft_memmove(res + lens1, s2, lens2);
	res[lentot - 1] = '\0';
	free(s1);
	return (res);
}

int		is_endofline(char *ligne)
{
	int i;

	i = 0;
	if (!ligne)
		return (0);
	while (ligne[i])
	{
		if (ligne[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

int		ft_clean(t_save **lstbegin, int fd)
{
	t_save	*next;

	if (fd == -1)
	{
		if (*lstbegin)
		{
			ft_clean(&((*lstbegin)->next), -1);
			free((*lstbegin)->ligne);
		}
		free(*lstbegin);
		return (-1);
	}
	while (*lstbegin && (*lstbegin)->fd != fd)
		lstbegin = &((*lstbegin)->next);
	next = (*lstbegin)->next;
	free((*lstbegin)->ligne);
	free(*lstbegin);
	*lstbegin = next;
	return (0);
}
