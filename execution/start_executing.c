/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_executing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oessamdi <oessamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 10:55:36 by oessamdi          #+#    #+#             */
/*   Updated: 2022/12/05 03:36:55 by oessamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../parsing/parsing.h"

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

int	count_path(char *str)
{
	int		i;
	int		c;

	i = 0;
	c = 1;
	while (str && str[i])
	{
		if (str[i] == ':')
			c++;
		i++;
	}
	return (c);
}

char	**add_slash(char **path, char *cmd_name)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (path && path[i])
	{
		path[i] = ft_charjoin(path[i], '/');
		j = 0;
		while (cmd_name[j])
			path[i] = ft_charjoin(path[i], cmd_name[j++]);
		i++;
	}
	return (path);
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

void	free_path(char **path)
{
	int	i;

	i = 0;
	while (path[i])
	{
		free(path[i]);
		path[i] = NULL;
		i++;
	}
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


void	start_executing(void)
{
	char	*cmd;

	cmd = g_data->commands->cmd_name;
	printf("\n-----cmd = %s\n", cmd);
	// if built-in call the built-in function
	// return
	cmd = check_path(cmd);
	//execute_cmd(cmd);
	printf("+++++cmd = %s\n", cmd);
}
