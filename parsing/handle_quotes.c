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

#include "../minishell.h"
#include "parsing.h"

void	init_var(int *j, char **str, int **arr)
{
	if (arr[0][0] == 0)
	{
		str[0][0] = str[0][0];
		*j = 1;
	}
}

void	handle_quotes(char **str, int **arr)
{
	int	i;
	int	j;
	int	*new;

	new = malloc(sizeof(int) * strlen(str[0]));
	init_var(&j, str, arr);
	if (arr[0][0] == 0)
		new[0] = arr[0][0];
	i = 1;
	while (str[0][i] && str[0][0])
	{
		if (!(arr[0][i] > 0 && arr[0][i - 1] == 0)
			&& !(arr[0][i] == 0 && arr[0][i - 1] > 0))
		{
			new[j] = arr[0][i];
			str[0][j++] = str[0][i];
		}
		i++;
	}
	str[0][j] = '\0';
	free(arr[0]);
	arr[0] = NULL;
	arr[0] = new;
}
