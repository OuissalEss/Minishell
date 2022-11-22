/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oessamdi <oessamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 15:37:34 by oessamdi          #+#    #+#             */
/*   Updated: 2022/11/22 16:03:19 by oessamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

void	args_quotes(t_cmd *lst)
{
	int			i;
	t_heredoc	*hlst;

	i = 0;
	while (lst->arguments && lst->arguments[i])
	{
		lst->arguments[i] = remove_quotes(lst->arguments[i]);
		i++;
	}
	hlst = lst->hdoc;
	while (hlst)
	{
		hlst->dlmt = remove_quotes(hlst->dlmt);
		hlst = hlst->next;
	}
}

// void	rm_q(char **str)
// {
// 	int	flag;
	
// 	flag = 0;
	
// }

void	rm_quotes(void)
{
	t_cmd		*lst;
	void		*tmp;

	lst = g_data->commands;
	while (lst)
	{
		tmp = lst->cmd_name;
		lst->cmd_name = remove_quotes(lst->cmd_name);
		args_quotes(lst);
		//edit_args(lst);
		lst = lst->next_cmd;
	}
}
