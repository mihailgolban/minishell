/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolban <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 13:00:07 by mgolban           #+#    #+#             */
/*   Updated: 2017/02/27 13:05:41 by mgolban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_getch(void)
{
	struct termios	oldterm;
	struct termios	newterm;
	int				c;

	tcgetattr(0, &oldterm);
	newterm = oldterm;
	newterm.c_lflag &= ~(ICANON | ECHO | IEXTEN);
	newterm.c_cc[VMIN] = 1;
	newterm.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &newterm);
	c = ft_getchar();
	tcsetattr(0, TCSANOW, &oldterm);
	return (c);
}
