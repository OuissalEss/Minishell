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
				i += expand(&str[i], &new);
			else
				new = ft_charjoin(new, str[i]);
		}
		else
			new = ft_charjoin(new, str[i]);
		i++;
	}
	return (new);
}
