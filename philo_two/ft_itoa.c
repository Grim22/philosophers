/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 10:07:55 by bbrunet           #+#    #+#             */
/*   Updated: 2020/08/17 10:15:11 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "one.h"

static int	ft_charnum(long int n)
{
	int	count;

	if (n == 0)
		return (1);
	count = 0;
	if (n < 0)
		count++;
	while (n)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

char		*ft_itoa(long int nlong)
{
	char		*p;
	int			i;
	int			num;

	num = ft_charnum(nlong);
	if (!(p = malloc((num + 1) * sizeof(char))))
		return (NULL);
	if (nlong == 0)
		p[0] = '0';
	if (nlong < 0)
	{
		p[0] = '-';
		nlong = (nlong * -1);
	}
	i = num - 1;
	while (nlong)
	{
		p[i] = (nlong % 10) + 48;
		nlong = nlong / 10;
		i--;
	}
	p[num] = 0;
	return (p);
}
