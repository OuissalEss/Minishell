/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaajour <slaajour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 20:24:42 by slaajour          #+#    #+#             */
/*   Updated: 2022/12/05 06:19:13 by slaajour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../execution.h"

void	supprimer_node(int pos)
{
	t_env	*head;
	t_env	*tmp;

	head = g_data->env;
	tmp = g_data->env;
	if (pos == 0)
	{
		head = head->next_var;
		free(tmp);
		tmp = NULL;
	}
	else
	{
		while (pos != 0)
		{
			head = tmp;
			tmp = tmp->next_var;
			pos--;
		}
		head->next_var = tmp->next_var;
		free(tmp);
		tmp = NULL;
	}
}

void	remove_node(char *str)
{
	t_env	*head;
	int		i;

	head = g_data->env;
	i = 0;
	while (head)
	{
		if (!ft_strncmp(str, head->var, ft_strlen(head->var)))
		{
			supprimer_node(i);
			break ;
		}
		i++;
		head = head->next_var;
	}
}

void	do_unset(void)
{
	t_cmd	*head;
	int		i;

	head = g_data->commands;
	if (!head->arguments[1])
		return ;
	else
	{
		i = 1;
		while (head->arguments[i])
		{
			if (is_valid(head->arguments[i]) == 1)
				remove_node(head->arguments[i]);
			else
				printf("Minishell: unset: `%s': not a valid identifier\n",
					head->arguments[i]);
			i++;
		}
	}
}
