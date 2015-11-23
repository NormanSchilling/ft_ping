/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschilli <nschilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/04 11:31:14 by nschilli          #+#    #+#             */
/*   Updated: 2013/12/04 11:33:22 by nschilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstrev(t_list **begin)
{
	t_list	*head;
	t_list	*tmp;
	t_list	*tmp1;

	head = *begin;
	tmp = NULL;
	while (head != NULL)
	{
		tmp1 = tmp;
		tmp = head;
		head = head->next;
		tmp->next = tmp1;
	}
	*begin = tmp;
}
