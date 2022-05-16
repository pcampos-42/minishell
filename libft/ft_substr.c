/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas-ma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 10:58:24 by lucas-ma          #+#    #+#             */
/*   Updated: 2021/10/21 16:06:53 by lucas-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	index;

	if (!s)
		return (NULL);
	if (!len || ft_strlen(s) < start)
		return (ft_strdup(""));
	if (ft_strlen(s) - start > len)
		ptr = (char *)malloc((len + 1) * sizeof(char));
	else
		ptr = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	index = 0;
	while (index < len && s[start + index])
	{
		ptr[index] = s[start + index];
		index++;
	}
	ptr[index] = '\0';
	return (ptr);
}
