/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oessamdi <oessamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 18:36:09 by oessamdi          #+#    #+#             */
/*   Updated: 2022/12/02 14:06:37 by oessamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../parsing.h"
#include "check_error.h"

char	*get_varnamed(char *str, int i)
{
	int		i1;
	int		j;
	char	*var_name;

	i1 = i;
	while (str[i] && ft_isalnum(str[i]) != 0)
		i++;
	var_name = malloc(sizeof(char) * (i - i1 + 1));
	j = 0;
	while (str[i1] && ft_isalnum(str[i1]) != 0)
		var_name[j++] = str[i1++];
	var_name[j] = '\0';
	return (var_name);
}

int	expandd(char *str, char **new)
{
	int		i;
	char	*n;
	char	*var_name;
	char	*var_value;

	var_name = get_varnamed(str, 1);
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

char	*expand_dollar(char *str)
{
	int		i;
	char	*new;

	if (str == NULL)
		return (NULL);
	i = 0;
	new = NULL;
	new = ft_charjoin(new, '\0');
	while (str[i])
	{
		if (str[i] == '$' && quotes(str, i) != 1)
		{
			if (str[i + 1] == '?')
				i += expand_exit(&new);
			else if (ft_isalnum(str[i + 1]) == 1)
				i += expandd(&str[i], &new);
			else
				new = ft_charjoin(new, str[i]);
		}
		else
			new = ft_charjoin(new, str[i]);
		i++;
	}
	return (new);
}
