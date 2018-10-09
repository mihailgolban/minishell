/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolban <mgolban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 11:18:46 by mgolban           #+#    #+#             */
/*   Updated: 2017/02/27 12:25:33 by mgolban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		sh_echo(char **args)
{
	int nflag;

	nflag = 1;
	if (*++args && !ft_strcmp(*args, "-n"))
	{
		args++;
		nflag = 0;
	}
	while (*args)
	{
		ft_putstr(*args);
		if (*++args)
			ft_putchar(' ');
	}
	if (nflag)
		ft_putchar('\n');
	return (1);
}
