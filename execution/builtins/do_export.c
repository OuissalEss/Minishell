/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaajour <slaajour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 20:23:36 by slaajour          #+#    #+#             */
/*   Updated: 2022/12/11 02:23:13 by slaajour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	display_export(t_cmd *cmd)
{
	t_env	*head;

	head = g_data->env;
	while (head)
	{
		if (head->var)
		{
			ft_putstr_fd("declare -x ", cmd->outfile);
			ft_putstr_fd(head->var, cmd->outfile);
			if (head->value)
			{
				ft_putstr_fd("=\"", cmd->outfile);
				ft_putstr_fd(head->value, cmd->outfile);
				ft_putstr_fd("\"", cmd->outfile);
			}
		}
		ft_putstr_fd("\n", cmd->outfile);
		head = head->next_var;
	}
}

void	creat_env(char *name, char *value)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	env->var = name;
	env->value = value;
	env->next_var = NULL;
	env_add_back(&g_data->env, env);
}

void	change_env(char *name, char *value, int add)
{
	int		i;
	t_env	*head;

	i = 0;
	head = g_data->env;
	while (head)
	{
		if (ft_strcmp(head->var, name))
			break ;
		head = head->next_var;
	}
	if (add == 0)
		head->value = NULL;
	while (value[i])
	{
		head->value = ft_charjoin(head->value, value[i++]);
	}
}

void	creat_or_change(char *str)
{
	int		add;
	char	*var_name;
	char	*var_value;

	add = 0;
	var_name = env_name(str, &add);
	var_value = env_value(str);
	if (exist_env(var_name) == 1)
		change_env(var_name, var_value, add);
	else
		creat_env(var_name, var_value);
}

int	do_export(t_cmd *cmd)
{
	int		i;

	if (!cmd->arguments[1])
		display_export(cmd);
	i = 1;
	while (cmd->arguments[i])
	{
		if (is_valid(cmd->arguments[i]) == 1)
			creat_or_change(cmd->arguments[i]);
		else
		{
			ft_putstr_fd("Minishell: export: `", 2);
			ft_putstr_fd(cmd->arguments[i], 2);
			ft_putstr_fd("`: not a valid identifier\n", 2);
			return (1);
		}
		i++;
	}
	return (0);
}
