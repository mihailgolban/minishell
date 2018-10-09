/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcspn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolban <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 21:22:44 by mgolban           #+#    #+#             */
/*   Updated: 2017/02/27 12:01:10 by mgolban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strcspn(const char *s, const char *delim)
{
	size_t res;

	res = 0;
	while (*s)
	{
		if (ft_strchr(delim, *s))
			return (res);
		else
		{
			s++;
			res++;
		}
	}
	return (res);
}
