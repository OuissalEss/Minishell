/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaajour <slaajour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 12:44:37 by slaajour          #+#    #+#             */
/*   Updated: 2022/12/10 12:44:39 by slaajour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

char	*get_path(void)
{
	t_env	*env;

	env = g_data->env;
	while (env)
	{
		if (strcmp(env->var, "PATH") == 0)
			return (env->value);
		env = env->next_var;
	}
	return (NULL);
}

char	**split_path(char *cmd_name)
{
	int		i;
	int		j;
	char	*value;
	char	**path;

	value = get_path();
	j = count_path(value);
	path = malloc(sizeof(char *) * (j + 1));
	i = 0;
	while (i < j + 1)
		path[i++] = NULL;
	i = 0;
	j = 0;
	while (value && value[i])
	{
		if (value[i] == ':')
			j++;
		else
			path[j] = ft_charjoin(path[j], value[i]);
		i++;
	}
	return (add_slash(path, cmd_name));
}

char	*check_path(char *cmd_name)
{
	int		i;
	char	**path;
	char	*new;

	if (access(cmd_name, F_OK) == 0)
		return (strdup(cmd_name));
	path = split_path(cmd_name);
	i = 0;
	while (path[i])
	{
		if (access(path[i], F_OK) == 0)
			break ;
		i++;
	}
	new = strdup(cmd_name);
	if (path[i] != NULL)
		new = strdup(path[i]);
	free_path(path);
	if (path)
		free(path);
	path = NULL;
	return (new);
}
