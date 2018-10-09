/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolban <mgolban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 21:28:04 by mgolban           #+#    #+#             */
/*   Updated: 2017/02/09 19:30:16 by mgolban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *mem, size_t size)
{
	void *new_mem;

	new_mem = ft_memalloc(size);
	new_mem = ft_memcpy(new_mem, mem, size);
	ft_memdel(&mem);
	return (new_mem);
}
