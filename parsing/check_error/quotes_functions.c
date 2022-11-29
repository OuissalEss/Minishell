/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oessamdi <oessamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 10:49:05 by oessamdi          #+#    #+#             */
/*   Updated: 2022/11/24 16:43:15 by oessamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

int	quotes(const char *str, int x)
{
	int	i;
	int	sflag;
	int	dflag;

	i = 0;
	sflag = 0;
	dflag = 0;
	while (i <= x)
	{
		if (str[i] == '\"' && sflag == 0 && dflag == 0)
			dflag = 1;
		else if (str[i] == '\"' && dflag == 1)
			dflag = 0;
		else if (str[i] == '\'' && dflag == 0 && sflag == 0)
			sflag = 1;
		else if (str[i] == '\'' && sflag == 1)
			sflag = 0;
		i++;
	}
	if (sflag == 1)
		return (1);
	if (dflag == 1)
		return (2);
	return (0);
}

char	*remove_quotes(char *str)
{
	int		i;
	int		j;
	char	*new_str;

	i = 0;
	j = 0;
	if (str == NULL)
		return (NULL);
	new_str = malloc(sizeof(char) * strlen(str) + 1);
	while (str[i])
	{
		if (!(str[i] == '\"' && quotes(str, i) != 1)
			&& !(str[i] == '\'' && quotes(str, i) != 2))
			new_str[j++] = str[i];
			//new_arr[j] = arr[i];
		i++;
	}
	new_str[j] = '\0';
	free(str);
	str = NULL;
	return (new_str);
}
