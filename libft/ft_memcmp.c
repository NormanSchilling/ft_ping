/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschilli <nschilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/22 11:04:17 by nschilli          #+#    #+#             */
/*   Updated: 2015/02/24 14:22:26 by nschilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	if (n && *((unsigned char *)s1) == *((unsigned char *)s2))
		return (ft_memcmp(s1 + 1, s2 + 1, n - 1));
	if (n)
		return (*((unsigned char *)s1) - *((unsigned char *)s2));
	return (0);
}
