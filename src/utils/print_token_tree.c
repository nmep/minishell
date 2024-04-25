/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_token_tree.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 08:32:07 by picatrai          #+#    #+#             */
/*   Updated: 2024/03/12 18:22:24 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_expand(t_expand *expand)
{
	int	index;

	index = 0;
	printf(" expand ");
	while (expand != NULL)
	{
		printf("/ %d ", expand->act);
		expand = expand->next;
	}
	printf(" || ");
}

void	ft_printf_2d(char **str, t_expand **expand)
{
	int	index;

	printf("args-> ");
	index = 0;
	while (str[index])
	{
		printf("%s ", str[index]);
		(void)expand;
		if (expand != NULL)
			ft_print_expand(expand[index]);
		index++;
	}
	printf("\n");
}

void	ft_print_lst_exec(t_lst_exec *lst_exec)
{
	printf("exec\n");
	while (lst_exec != NULL)
	{
		if (lst_exec->args == NULL)
			printf("args NULL\n");
		else
			ft_printf_2d(lst_exec->args, lst_exec->expand);
		printf("in  -> %d\n", lst_exec->fd_in);
		printf("out -> %d\n\n", lst_exec->fd_out);
		lst_exec = lst_exec->next;
	}
}

void	ft_print_tree(t_tree *tree)
{
	if (tree == NULL)
		return ;
	if (tree->type == EXEC_LIST)
	{
		ft_print_lst_exec(tree->lst_exec);
	}
	else if (tree->type == OPPERATOR_AND)
	{
		printf("AND\n");
	}
	else if (tree->type == OPPERATOR_OR)
	{
		printf("OR\n");
	}
	if (tree->left_child != NULL)
	{
		printf("left child\n");
		ft_print_tree(tree->left_child);
	}
	if (tree->right_child != NULL)
	{
		printf("right child\n");
		ft_print_tree(tree->right_child);
	}
	return ;
}

void	ft_print_token(t_token **token)
{
	if (*token == NULL)
	{
		return ;
	}
	while ((*token)->prev != NULL)
		*token = (*token)->prev;
	printf("size %d\n\n", ft_lstsize(*token));
	while ((*token)->next != NULL)
	{
		printf("%s | %d |\n", (*token)->str, (*token)->type);
		ft_print_expand((*token)->expand);
		*token = (*token)->next;
	}
	printf("%s | %d |\n", (*token)->str, (*token)->type);
	ft_print_expand((*token)->expand);
	while ((*token)->prev != NULL)
		*token = (*token)->prev;
}
