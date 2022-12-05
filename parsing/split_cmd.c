/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oessamdi <oessamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 10:55:36 by oessamdi          #+#    #+#             */
/*   Updated: 2022/12/05 00:42:59 by oessamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "parsing.h"

int	get_count(char *str, int *arr)
{
	int		i;
	int		c;

	i = 0;
	c = 1;
	while (str[i])
	{
		if (str[i] == '|' && arr[i] == 0)
			c++;
		i++;
	}
	return (c);
}

char	**split_cmds(char *str, int *arr)
{
	int		i;
	int		c;
	char	**cmds;

	c = get_count(str, arr);
	cmds = malloc(sizeof(char *) * (c + 1));
	i = 0;
	while (i < c + 1)
		cmds[i++] = NULL;
	i = 0;
	c = 0;
	while (str[i])
	{
		if (str[i] == '|' && arr[i] == 0)
			c++;
		else
			cmds[c] = ft_charjoin(cmds[c], str[i]);
			i++;
	}
	cmds[c + 1] = NULL;
	return (cmds);
}
