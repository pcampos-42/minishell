#include "libft/libft.h"
#include <stdio.h>

void	get_env(t_list **env, char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
		ft_lstadd_back(env, ft_lstnew(envp[i]));
}

void	print_env(t_list *env, int fd)
{
	t_list	*tmp;

	tmp = env;
	while (tmp)
	{
		ft_putendl_fd(tmp->content, fd);
		tmp = tmp->next;
	}
}

char	**ft_seperate(char *str, char c)
{
	char	**matrix;
	int		a;

	a = 0;
	while(str[a] != c)
		a++;
	matrix = malloc(sizeof(char *) * 3);
	matrix[0] = ft_substr(str, 0, a + 1);
	matrix[1] = ft_substr(str, a + 1, ft_strlen(str));
	return (matrix);
}

void	export_func(void *branch, t_list **env)
{
	char	**tmp;
	char	*newvar;

	tmp = ft_seperate(((char **)(branch))[1], '=');
	newvar = ft_strjoin(tmp[0], tmp[1]);
	printf("%s\n\n", newvar);
	ft_lstadd_back(env, ft_lstnew(newvar));
}

int main(int ac, char **av, char **envp)
{
	t_list	*env;
	(void)ac;
	(void)av;
	get_env(&env, envp);
	export_func(av, &env);
	print_env(env, 1);
}