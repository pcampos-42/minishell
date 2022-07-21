#include "libft/libft.h"
#include <stdio.h>

void	export_func(void *branch)
{
	char	**tmp;

	tmp = ft_split(((char **)(branch))[1], '=');
	printf("%s\n", tmp[1]);
}

int main(int ac, char **av)
{
	(void)ac;
	export_func(av);
}