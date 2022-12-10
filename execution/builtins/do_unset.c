/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oessamdi <oessamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 20:24:42 by slaajour          #+#    #+#             */
/*   Updated: 2022/12/10 06:06:21 by oessamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	supprimer_node(int pos)
{
	t_env	*head;
	t_env	*tmp;

	head = g_data->env;
	tmp = g_data->env;
	if (pos == 0)
	{
		g_data->env = head->next_var;
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

int	valid(char	*str)
{
	int	j;

	j = 0;
	if (is_alpha(str[0]) == 0)
		return (-1);
	while (str[j])
	{
		if (ft_isalnum(str[j]) == 0)
			return (-1);
		j++;
	}
	return (1);
}

int	do_unset(t_cmd *cmd)
{
	int		i;

	if (!cmd->arguments[1])
		return (0);
	else
	{
		i = 1;
		while (cmd->arguments[i])
		{
			if (valid(cmd->arguments[i]) == 1)
				remove_node(cmd->arguments[i]);
			else
			{
				ft_putstr_fd("Minishell: unset: `", cmd->outfile);
				ft_putstr_fd(cmd->arguments[i], cmd->outfile);
				ft_putstr_fd("`: not a valid identifier\n", cmd->outfile);
				return (1);
			}
			i++;
		}
	}
	return (0);
}
