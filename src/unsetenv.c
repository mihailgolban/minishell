/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolban <mgolban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 11:19:06 by mgolban           #+#    #+#             */
/*   Updated: 2017/02/27 12:56:16 by mgolban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		sh_unsetenv(char **args)
{
	size_t	len;
	char	**env;

	if (*(++args) == NULL)
		ft_putendl_fd("unsetenv: not enough arguments", 2);
	while (*args)
	{
		len = ft_strlen(*args);
		env = g_env;
		while (*env)
		{
			if (!ft_strncmp(*env, *args, len) && (*env)[len] == '=')
			{
				while (*env)
				{
					env[0] = env[1];
					env++;
				}
			}
			else
				env++;
		}
		args++;
	}
	return (1);
}
