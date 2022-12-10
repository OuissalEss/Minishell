/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oessamdi <oessamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 07:28:15 by oessamdi          #+#    #+#             */
/*   Updated: 2022/12/08 09:44:21 by oessamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "parsing.h"

void	write_in_file(char *str, t_red *r)
{
	int		*arr;
	char	*tmp;

	arr = malloc(sizeof(int) * (strlen(str) + 1));
	set_arr(str, &arr);
	tmp = str;
	if (r->expand == 0)
		tmp = handle_expansion(&str, &arr);
	ft_putstr_fd(tmp, r->fd[1]);
	ft_putchar_fd('\n', r->fd[1]);
	if (r->expand == 0)
	{
		free(tmp);
		tmp = NULL;
	}
}

void	hdoc2(char	**str)
{
	if (*str != NULL)
		free(*str);
}

int	open_hdoc(t_red *r)
{
	char	*str;

	if (pipe(r->fd) < 0)
	{
		printf("%s\n", strerror(errno));
		return (-1);
	}
	while (1)
	{
		str = readline(">");
		if (str == NULL || strcmp(str, r->file_name) == 0)
		{
			hdoc2(&str);
			str = NULL;
			break ;
		}
		else
			write_in_file(str, r);
		if (str != NULL)
			free(str);
		str = NULL;
	}
	close(r->fd[1]);
	return (0);
}
