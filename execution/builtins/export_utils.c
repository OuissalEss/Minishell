/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oessamdi <oessamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 20:23:36 by slaajour          #+#    #+#             */
/*   Updated: 2022/12/10 06:06:13 by oessamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	is_valid(char	*str)
{
	int	j;

	j = 0;
	if (is_alpha(str[0]) == 0)
		return (-1);
	while (str[j] && str[j] != '=')
	{
		if (ft_isalnum(str[j]) == 0)
		{
			if (!(str[j] == '+' && str[j + 1] == '='))
				return (-1);
		}
		j++;
	}
	return (1);
}

char	*env_name(char *str, int *add)
{
	int		i;
	char	*name;

	i = 0;
	name = NULL;
	while (str[i] && str[i] != '=')
	{
		if (str[i] == '+' && str[i + 1] == '=')
		{
			*add = 1;
			break ;
		}
		name = ft_charjoin(name, str[i]);
		i++;
	}
	return (name);
}

char	*env_value(char *str)
{
	int		i;
	char	*value;

	i = 0;
	value = NULL;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] != '\0')
	{
		value = ft_charjoin(value, '\0');
		i++;
	}
	while (str[i])
		value = ft_charjoin(value, str[i++]);
	return (value);
}

int	exist_env(char *name)
{
	t_env	*head;

	head = g_data->env;
	while (head)
	{
		if (ft_strcmp(head->var, name) == 1)
			return (1);
		head = head->next_var;
	}
	return (0);
}
