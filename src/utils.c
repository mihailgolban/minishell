/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolban <mgolban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/31 11:55:25 by mgolban           #+#    #+#             */
/*   Updated: 2017/02/27 13:03:29 by mgolban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(const char *name)
{
	size_t	len;
	char	**p;

	if (name == NULL || g_env == NULL)
		return (NULL);
	len = ft_strlen(name);
	p = g_env;
	while (*p)
	{
		if (ft_strncmp(*p, name, len) == 0 && (*p)[len] == '=')
			return (*p + len + 1);
		p++;
	}
	return (NULL);
}

void	ft_checkdollar(char **args)
{
	char *dollar;
	char *temp;

	while (*args)
	{
		if ((dollar = ft_strchr(*args, '$')) && *(dollar + 1))
		{
			*dollar = '\0';
			if ((temp = ft_getenv(dollar + 1)) == NULL)
				temp = ft_strnew(0);
			*args = ft_strjoin(*args, temp);
		}
		args++;
	}
}

int		ft_is_exist(char *file)
{
	if (access(file, F_OK) == -1)
	{
		ft_putstr_fd("minishell: no such file or directory: ", 2);
		ft_putendl_fd(file, 2);
		return (0);
	}
	return (1);
}

int		ft_is_executable(char *file)
{
	struct stat buf;

	lstat(file, &buf);
	if (access(file, X_OK) == -1 || !S_ISREG(buf.st_mode))
	{
		ft_putstr_fd("minishell: permission denied: ", 2);
		ft_putendl_fd(file, 2);
		return (0);
	}
	return (1);
}
