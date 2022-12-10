/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oessamdi <oessamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 07:37:39 by oessamdi          #+#    #+#             */
/*   Updated: 2022/12/02 14:14:56 by oessamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "parsing.h"

int	array_expand(char *str, int **new, int *x)
{
	int		i;
	int		j;
	char	*var_name;
	char	*var_value;

	var_name = get_varname(str, 1);
	var_value = get_varvalue(var_name);
	i = 0;
	j = *x;
	while (var_value[i])
	{
		if (j == 0)
			new[0][j] = new[0][j];
		else
			new[0][j] = new[0][j - 1];
		j++;
		i++;
	}
	*x = j;
	i = strlen(var_name);
	free(var_name);
	var_name = NULL;
	return (i);
}

int	array_exit(int **new, int *x)
{
	int		i;
	int		j;
	char	*nb;

	nb = ft_itoa(g_data->exit_status);
	i = 0;
	j = *x;
	while (nb[i])
	{
		if (j == 0)
			new[0][j] = new[0][j];
		else
			new[0][j] = new[0][j - 1];
		i++;
		j++;
	}
	*x = j;
	free(nb);
	nb = NULL;
	return (1);
}

int	*new_array(char **str, int **arr, char *new)
{
	int	i;
	int	j;
	int	*new_arr;

	i = 0;
	j = 0;
	new_arr = malloc(sizeof(int) * (strlen(new) + 1));
	new_arr[0] = arr[0][0];
	while (str[0][i])
	{
		if (str[0][i] == '$' && arr[0][i] != 1)
		{
			if (str[0][i + 1] == '?')
				i += array_exit(&new_arr, &j);
			else if (ft_isalnum(str[0][i + 1]) == 1)
				i += array_expand(&str[0][i], &new_arr, &j);
			else
				new_arr[j] = arr[0][i];
		}
		else
			new_arr[j] = arr[0][i];
		i++;
		j++;
	}
    free(arr[0]);
    arr[0] = NULL;
	return (new_arr);
}
