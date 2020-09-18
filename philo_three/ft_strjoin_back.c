/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_back.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 18:44:39 by julnolle          #+#    #+#             */
/*   Updated: 2020/09/18 10:26:12 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "one.h"

char	*ft_strdup(const char *src)
{
	int		i;
	char	*ptr;

	if (src == NULL)
		return (NULL);
	i = 0;
	while (src[i])
		i++;
	if (!(ptr = malloc((i + 1) * sizeof(char))))
		return (0);
	i = 0;
	while (src[i])
	{
		ptr[i] = src[i];
		i++;
	}
	ptr[i] = 0;
	return (ptr);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*p;
	int		i;
	int		j;

	if (s1 == 0 || s2 == 0)
		return (NULL);
	if (!(p = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(*p))))
		return (NULL);
	i = 0;
	while (s1[i])
	{
		p[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		p[i + j] = s2[j];
		j++;
	}
	p[i + j] = 0;
	return (p);
}

void	ft_strjoin_back(char *back, char **src)
{
	char *tmp;

	if (back == NULL || src == NULL)
		return ;
	if (*src)
	{
		tmp = ft_strdup(*src);
		free(*src);
		*src = NULL;
	}
	else
		tmp = ft_strdup("");
	*src = ft_strjoin(tmp, back);
	free(tmp);
	tmp = NULL;
}
