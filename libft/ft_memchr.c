/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschilli <nschilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/22 10:28:00 by nschilli          #+#    #+#             */
/*   Updated: 2013/11/22 12:15:38 by nschilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	if (n)
	{
		if (*((unsigned char *)s) == (unsigned char)c)
			return ((void *)s);
		else
			return (ft_memchr(++s, c, --n));
	}
	return (NULL);
}
