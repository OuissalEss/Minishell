/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oessamdi <oessamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 18:36:09 by oessamdi          #+#    #+#             */
/*   Updated: 2022/11/25 18:36:48 by oessamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

char	*expand_dollar(char *str)
{
	int		i;
	char	*new;
	char	*var_name;

	i = 0;
	new = NULL;
	new = ft_charjoin(new, '\0');
	while (str[i])
	{
		if (str[i] == '$' && quotes(str, i) != 1)
		{
			if (str[i + 1] == '?')
				new = ft_strjoin(new, ft_itoa(g_data->exit_status));
			var_name = get_varname(str, i + 1);
			new = ft_strjoin(new, strdup(get_varvalue(var_name)));
			i += strlen(var_name);
			free(var_name);
			var_name = NULL;
		}
		else
			new = ft_charjoin(new, str[i]);
		i++;
	}
	return (new);
}
