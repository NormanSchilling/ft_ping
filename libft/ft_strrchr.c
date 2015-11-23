/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschilli <nschilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/21 13:26:46 by nschilli          #+#    #+#             */
/*   Updated: 2013/11/22 12:59:58 by nschilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*cc;

	cc = NULL;
	while (*s)
	{
		if (*s == (char)c)
			cc = (char *)s;
		s++;
	}
	if (*s == (char)c)
		cc = (char *)s;
	return (cc);
}
