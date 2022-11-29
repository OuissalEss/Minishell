/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oessamdi <oessamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 10:49:05 by oessamdi          #+#    #+#             */
/*   Updated: 2022/11/29 11:23:04 by oessamdi         ###   ########.fr       */
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
