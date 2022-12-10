/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaajour <slaajour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 12:44:15 by slaajour          #+#    #+#             */
/*   Updated: 2022/12/10 12:44:18 by slaajour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	count_path(char *str)
{
	int		i;
	int		c;

	i = 0;
	c = 1;
	while (str && str[i])
	{
		if (str[i] == ':')
			c++;
		i++;
	}
	return (c);
}

char	**add_slash(char **path, char *cmd_name)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (path && path[i])
	{
		path[i] = ft_charjoin(path[i], '/');
		j = 0;
		while (cmd_name[j])
			path[i] = ft_charjoin(path[i], cmd_name[j++]);
		i++;
	}
	return (path);
}

void	free_path(char **path)
{
	int	i;

	i = 0;
	while (path[i])
	{
		free(path[i]);
		path[i] = NULL;
		i++;
	}
}
