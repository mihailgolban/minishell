/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolban <mgolban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 11:18:59 by mgolban           #+#    #+#             */
/*   Updated: 2017/02/27 12:51:00 by mgolban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		sh_setenv(char **args)
{
	char	*value;
	char	*s;

	s = "*?[]'\"\\$;&(){}|^<>\n\t ";
	(*(args + 1) == NULL) ? sh_env() : 0;
	while (*(++args))
	{
		if (ft_strcspn(*args, s) != ft_strlen(*args))
		{
			ft_putstr_fd("minishell: not valid in this context: ", 2);
			ft_putendl_fd(*args, 2);
		}
		else if ((ft_strchr(*args, '=') == NULL))
			continue;
		else if (ft_strcmp(*args, "=") == 0)
			ft_putendl_fd("minishell: bad assignment", 2);
		else
		{
			value = ft_strchr(*args, '=') + 1;
			*(ft_strchr(*args, '=')) = '\0';
			ft_setenv(*args, value, 1);
		}
	}
	return (1);
}

int		ft_setenv(const char *name, const char *value, int overwrite)
{
	char *new;

	if (name == NULL || name[0] == '\0' ||
			ft_strchr(name, '=') != NULL || value == NULL)
		return (-1);
	if (ft_getenv(name) != NULL && !overwrite)
		return (0);
	new = malloc(ft_strlen(name) + ft_strlen(value) + 2);
	if (new == NULL)
		return (-1);
	ft_strcpy(new, name);
	ft_strcat(new, "=");
	ft_strcat(new, value);
	return (ft_putenv(new) != 0) ? -1 : 0;
}

int		ft_putenv(const char *str)
{
	char	**pos;
	char	**new_env;
	size_t	env_len;
	size_t	name_len;

	name_len = ft_strchr(str, '=') - str + 1;
	pos = g_env;
	env_len = 0;
	while (*pos)
	{
		env_len++;
		if (ft_strncmp(*pos, str, name_len) == 0)
		{
			*pos = (char *)str;
			return (0);
		}
		pos++;
	}
	if ((new_env = ft_create_env(env_len)) == NULL)
		return (-1);
	g_env = new_env;
	g_env[env_len] = (char *)str;
	g_env[env_len + 1] = NULL;
	return (0);
}

char	**ft_create_env(size_t env_len)
{
	char		**new_env;
	static int	first;

	if (first == 0)
	{
		new_env = (char **)malloc(sizeof(char *) * (env_len + 2));
		if (new_env == NULL)
			return (NULL);
		first = 1;
		ft_memcpy(new_env, g_env, sizeof(char *) * env_len);
	}
	else
	{
		new_env = (char **)ft_realloc(g_env, sizeof(char *) *
				(env_len + 2));
		if (new_env == NULL)
			return (NULL);
	}
	return (new_env);
}
