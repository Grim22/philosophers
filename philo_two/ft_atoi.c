/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 15:08:16 by bbrunet           #+#    #+#             */
/*   Updated: 2020/08/14 10:01:26 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "one.h"

static int	ft_isspace(const char *c)
{
	if (*c == 32 || *c == 9 || *c == 10 || *c == 11 || *c == 12 || *c == 13)
		return (1);
	return (0);
}

static int	ft_issign(const char *c)
{
	if (*c == 43 || *c == 45)
		return (1);
	return (0);
}

static int	ft_isnum(const char *c)
{
	int i;

	i = 0;
	while (i <= 9)
	{
		if (*c == 48 + i)
			return (1);
		i++;
	}
	return (0);
}

int			ft_atoi(const char *str)
{
	int i;
	int c;
	int ret;

	i = 0;
	c = 1;
	while (ft_isspace(str + i))
		i++;
	if (ft_issign(str + i))
	{
		if (str[i] == 45)
			c = -1;
		i++;
	}
	ret = 0;
	while (ft_isnum(str + i))
	{
		ret = ret * 10 + str[i] - 48;
		i++;
	}
	return (c * ret);
}
