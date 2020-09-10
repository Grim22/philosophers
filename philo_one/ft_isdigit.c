/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 16:00:12 by bbrunet           #+#    #+#             */
/*   Updated: 2020/09/10 11:49:39 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "one.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (YES);
	else
		return (NO);
}

int	only_zero(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '0')
			return (NO);
		i++;
	}
	return (YES);
}

int	ft_isdigit_str(char *str)
{
	int i;

	i = 0;
	if (only_zero(str) == YES)
		return (NO);
	while (str[i])
	{
		if (ft_isdigit(str[i]) == NO)
			return (NO);
		i++;
	}
	return (1);
}
