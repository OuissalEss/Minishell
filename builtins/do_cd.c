/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaajour <slaajour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 18:37:35 by slaajour          #+#    #+#             */
/*   Updated: 2022/12/04 02:51:23 by slaajour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../execution.h"

void	go_home(char *pwd)
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
			g_data->env->value = pwd;
		g_data->env = g_data->env->next_var;
	}
	g_data->env = head;
}

void	do_cd(void)
{
	char	*pwd;
	char	*old_pwd;

	old_pwd = getcwd(NULL, 0);
	pwd = NULL;
	if (!g_data->commands->arguments[1])
	{
		go_home(pwd);
		update_pwd(old_pwd, pwd);
	}
	else if (chdir(g_data->commands->arguments[1]) == 0)
	{
		pwd = getcwd(NULL, 0);
		update_pwd(old_pwd, pwd);
	}
	else
	{
		printf("Minishell: cd: %s: No such file or directory\n",
			g_data->commands->arguments[1]);
	}
}
