/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oessamdi <oessamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 10:55:36 by oessamdi          #+#    #+#             */
/*   Updated: 2022/11/27 17:39:17 by oessamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "minishell.h"

void	*ft_calloc(size_t size)
{
	char **cmds;
	int i;

	cmds = malloc(sizeof(char *) * size);
	i = 0;
	while (i < size)
		cmds[i++] = NULL;
	return (cmds);
}

int	get_count(char *str, int **arr)
{
	int		i;
	int		c;

	i = 0;
	c = 1;
	while (str[i])
	{
		if (str[i] == '|' && arr[0][i] == 0)
			c++;
		i++;
	}
	return (c);
}

char	**split_cmds(char *str, int **arr)
{
	int		i;
	int		c;
	char	**cmds;

	c = get_count(str, arr);
	cmds = ft_calloc(sizeof(char *) * (c + 1));
	i = 0;
	c = 0;
	while (str[i])
	{
		if (str[i] == '|' && arr[0][i] == 0)
			c++;
		else
			cmds[c] = ft_charjoin(cmds[c], str[i]);
		i++;
	}
	cmds[c + 1] = NULL;
	return (cmds);
}
