/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaajour <slaajour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 20:23:36 by slaajour          #+#    #+#             */
/*   Updated: 2022/12/04 07:48:21 by slaajour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../execution.h"
#include "../parsing/parsing.h"

void	display_export(void)
{
	t_env	*head;

	head = g_data->env;
	while (head)
	{
		if (head->var)
		{
			ft_putstr("declare -x ");
			ft_putstr(head->var);
			if (head->value)
			{
				printf("=\"");
				ft_putstr(head->value);
				printf("\"");
			}
		}
		printf("\n");
		head = head->next_var;
	}
}

int	is_valid(char	*str)
{
	int	j;

	j = 0;
	if (is_alpha(str[0]) == 0)
		return (-1);
	while (str[j] && str[j] != '=')
	{
		if (ft_isalnum(str[j]) == 0)
			return (-1);
		j++;
	}
	return (1);
}

t_env	*creat_env(char *str)
{
	int		i;
	t_env	*env;

	env = malloc(sizeof(t_env));
	i = 0;
	env->var = NULL;
	env->value = NULL;
	while (str[i] && str[i] != '=')
		env->var = ft_charjoin(env->var, str[i++]);
	if (str[i] != '\0')
	{
		env->value = ft_charjoin(env->value, '\0');
		i++;
	}
	while (str[i])
		env->value = ft_charjoin(env->value, str[i++]);
	env->next_var = NULL;
	return (env);
}

void	do_export(void)
{
	t_cmd	*head;
	t_env	*tmp;
	int		i;

	if (!g_data->commands->arguments[1])
		display_export();
	i = 1;
	head = g_data->commands;
	while (head->arguments[i])
	{
		if (is_valid(head->arguments[i]) == 1)
		{
			tmp = creat_env(head->arguments[i]);
			env_add_back(&g_data->env, tmp);
		}
		else
			printf("Minishell: export: `%s': not a valid identifier\n",
				head->arguments[i]);
		i++;
	}
}
