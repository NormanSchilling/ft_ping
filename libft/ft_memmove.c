/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschilli <nschilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/22 10:08:47 by nschilli          #+#    #+#             */
/*   Updated: 2013/12/04 10:47:55 by nschilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *s1, const void *s2, size_t n)
{
	size_t	i;
	char	tmp[n];
	char	*s;

	i = 0;
	s = (char *)s1;
	while (i < n)
		tmp[i++] = *((char *)s2++);
	while (i--)
		s[i] = tmp[i];
	return (s1);
}
