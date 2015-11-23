/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschilli <nschilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/04 11:15:18 by nschilli          #+#    #+#             */
/*   Updated: 2013/12/04 11:16:50 by nschilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*node;
	t_list	*tmp;

	node = *alst;
	if (alst && *alst && (*del))
	{
		while (node)
		{
			tmp = node;
			node = node->next;
			(*del)(tmp->content, tmp->content_size);
			free(tmp);
		}
		*alst = NULL;
	}
}
