/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oessamdi <oessamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 10:48:31 by oessamdi          #+#    #+#             */
/*   Updated: 2022/11/21 10:48:32 by oessamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

int	array_size(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

int	add_args2(char *str, int i)
{
	t_cmd	*last;
	int		j;
	int		size;
	char	**args;

	last = get_last(g_data->commands);
	size = array_size(last->arguments);
	args = malloc(sizeof(char *) * (size + 2));
	j = 0;
	while (last->arguments[j])
	{
		args[j] = last->arguments[j];
		j++;
	}
	args[j] = NULL;
	args[j] = get_name(str, &i);
	args[j + 1] = NULL;
	free(last->arguments);
	last->arguments = NULL;
	last->arguments = args;
	return (i);
}

char	*expand_and_quotes(char	*str)
{
	//printf("expand and quotes\n");
	return (str);
}

int	add_args(char *str, int i)
{
	t_cmd	*last;

	last = get_last(g_data->commands);
	if (last->cmd_name == NULL)
	{
		last->arguments = malloc(sizeof(char *) * 2);
		last->arguments[0] = NULL;
		while (str[i] && ((str[i] != ' ' && str[i] != '|' && str[i] != '<'
					&& str[i] != '>' ) || quotes(str, i) != 0))
		{
			last->cmd_name = ft_charjoin(last->cmd_name, str[i]);
			last->arguments[0] = ft_charjoin(last->arguments[0], str[i]);
			i++;
		}
		last->cmd_name = ft_charjoin(last->cmd_name, '\0');
		last->arguments[0] = ft_charjoin(last->arguments[0], '\0');
		last->arguments[1] = NULL;
	}
	else
		i = add_args2(str, i);
	last->cmd_name = expand_and_quotes(last->cmd_name);
	last->arguments[0] = expand_and_quotes(last->arguments[0]);
	i--;
	return (i);
}

void	start_parsing(char *str)
{
	int			i;

	i = 0;
	add_cmd();
	while (str[i])
	{
		i = skip_whitespace(str, i);
		if (str[i] == '|')
			add_cmd();
		else if (str[i] == '<' || str[i] == '>')
			i = handle_redirections(str, i);
		else
			i = add_args(str, i);
		i++;
	}
}
