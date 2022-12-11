/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaajour <slaajour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 18:37:35 by slaajour          #+#    #+#             */
/*   Updated: 2022/12/11 02:21:21 by slaajour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

char	*go_home(char *pwd)
{
	t_env	*head;

	head = g_data->env;
	while (head)
	{
		if (ft_strcmp("HOME", head->var))
		{
			chdir(head->value);
			pwd = getcwd(NULL, 0);
		}
		head = head->next_var;
	}
	return (pwd);
}

void	update_pwd(char *old_pwd, char *pwd)
{
	t_env	*head;

	head = g_data->env;
	while (g_data->env)
	{
		if (ft_strcmp("OLDPWD", g_data->env->var))
			g_data->env->value = old_pwd;
		if (ft_strcmp("PWD", g_data->env->var))
		{
			if (pwd != NULL)
				g_data->env->value = pwd;
			else
				ft_putstr_fd("Minishell: cd: No such file or directory\n", 2);
		}
		g_data->env = g_data->env->next_var;
	}
	g_data->env = head;
}

int	do_cd(t_cmd *cmd)
{
	char	*pwd;
	char	*old_pwd;

	old_pwd = getcwd(NULL, 0);
	pwd = NULL;
	if (!cmd->arguments[1])
	{
		pwd = go_home(pwd);
		update_pwd(old_pwd, pwd);
	}
	else if (chdir(cmd->arguments[1]) == 0)
	{
		pwd = getcwd(NULL, 0);
		update_pwd(old_pwd, pwd);
	}
	else
	{
		ft_putstr_fd("Minishell: cd: ", 2);
		ft_putstr_fd(cmd->arguments[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (1);
	}
	return (0);
}
