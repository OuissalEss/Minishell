/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oessamdi <oessamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 10:48:41 by oessamdi          #+#    #+#             */
/*   Updated: 2022/12/02 14:40:48 by oessamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "check_error.h"

int	skip_white_spaces(char *str, int i, t_errflags *flags)
{
	if (flags->dlmt == 1 && str[i] == ' ')
		flags->dlmt = 0;
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] == '\0' && i > 0)
		i--;
	return (i);
}

char	*get_name(char *str, int *j)
{
	int		i;
	char	*name;

	i = *j;
	name = NULL;
	while (str[i] && str[i] == ' ')
		i++;
	while (str[i])
	{
		if ((str[i] == ' ' || str[i] == '|' || str[i] == '<'
				|| str[i] == '>' ) && quotes(str, i) == 0)
			break ;
		name = ft_charjoin(name, str[i]);
		if (str[i])
			i++;
	}
	name = ft_charjoin(name, '\0');
	*j = i;
	return (name);
}

void	open_hdocs(t_errflags *f)
{
	char		*str;
	t_heredoc	*h;

	h = f->hdocs;
	while (h)
	{
		while (1)
		{
			str = readline(">");
			if (str == NULL || strcmp(str, h->dlmt) == 0)
				break ;
			free(str);
			str = NULL;
		}
		h = h->next;
	}
}
