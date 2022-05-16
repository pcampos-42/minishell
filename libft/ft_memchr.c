/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas-ma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 09:07:04 by lucas-ma          #+#    #+#             */
/*   Updated: 2021/10/21 16:17:34 by lucas-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned int	index;
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	index = 0;
	while (index < n)
	{
		if (ptr[index] == (unsigned char)c)
			return (ptr + index);
		index++;
	}
	return (NULL);
}
