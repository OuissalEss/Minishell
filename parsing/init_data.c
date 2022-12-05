/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oessamdi <oessamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 10:48:55 by oessamdi          #+#    #+#             */
/*   Updated: 2022/12/03 16:41:44 by oessamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "parsing.h"

char	*get_var(char *str)
{
	int		i;
	char	*var;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	var = malloc(sizeof(char) * i + 1);
	i = 0;
	while (str[i] && str[i] != '=')
	{
		var[i] = str[i];
		i++;
	}
	var[i] = '\0';
	return (var);
}

char	*get_value(char *str)
{
	int		start;
	int		i;
	char	*value;

	start = 0;
	while (str[start] && str[start] != '=')
		start++;
	start++;
	value = malloc(sizeof(char) * strlen(&str[start]) + 1);
	i = 0;
	while (str[start])
		value[i++] = str[start++];
	value[i] = '\0';
	return (value);
}

void	set_env(char **envp)
{
	int		i;
	t_env	*node;

	i = 0;
	g_data->env = NULL;
	if (!envp)
		return ;
	while (envp[i])
	{
		node = malloc(sizeof(t_env));
		node->var = get_var(envp[i]);
		node->value = NULL;
		if (strcmp(node->var, "OLDPWD") != 0)
			node->value = get_value(envp[i]);
		node->next_var = NULL;
		env_add_back(&g_data->env, node);
		i++;
	}
}

void	init_data(char **envp)
{
	g_data = malloc(sizeof(t_data));
	g_data->commands = NULL;
	set_env(envp);
	g_data->exit_status = 0;
	g_data->child_process = 0;
}
