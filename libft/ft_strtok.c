/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolban <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 21:21:09 by mgolban           #+#    #+#             */
/*   Updated: 2017/02/27 12:01:42 by mgolban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtok(char *str, const char *delim)
{
	static char *ptr;

	if (str)
		ptr = str;
	else if (!ptr)
		return (0);
	str = ptr + ft_strspn(ptr, delim);
	ptr = str + ft_strcspn(str, delim);
	if (ptr == str)
		return (ptr = 0);
	if (*ptr)
		*ptr++ = 0;
	return (str);
}
