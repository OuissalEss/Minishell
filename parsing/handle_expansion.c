/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oessamdi <oessamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 07:37:39 by oessamdi          #+#    #+#             */
/*   Updated: 2022/11/29 12:01:10 by oessamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "minishell.h"

int	expand(char *str, int *arr, char **new)
{
	int		i;
	char	*n;
	char	*var_name;
	char	*var_value;

	var_name = get_varname(str, 1);
	var_value = get_varvalue(var_name);
	n = *new;
	i = 0;
	while (var_value[i])
	{
		n = ft_charjoin(n, var_value[i]);
		i++;
	}
	*new = n;
	i = strlen(var_name);
	free(var_name);
	var_name = NULL;
	return (i);
}

int expand_exit(char *str, int *arr, char **new)
{
    int     i;
    char    *nb;
	char	*n;

    nb = ft_itoa(g_data->exit_status);
	i = 0;
	n = *new;
	while (str[i])
	{
		n = ft_charjoin(n, nb[i]);
		i++;
	}
	*new = n;
    free(nb);
	nb = NULL;
	return (2);
}

char	*handle_expansion(char **str, int **arr)
{
	int		i;
	char	*new;
	char	*var_name;
	char	*var_value;

	i = 0;
	new = NULL;
	while (str[0][i])
	{
		if (str[0][i] == '$' && arr[0][i] == 0)
		{
			if (str[0][i + 1] == '?')
                i += expand_exit(&str[0][i], &arr[0][i], &new);
			else if (ft_isalnum(str[0][i + 1]) == 1)
				i += expand(&str[0][i], &arr[0][i], &new);
		}
		else
			new = ft_charjoin(new, str[0][i]);
		i++;
	}
	new = ft_charjoin(new, '\0');
	return (new);
}
