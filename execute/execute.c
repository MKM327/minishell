#include "execute.h"

int	execute(t_node *head, char **env)
{
	if (ft_strncmp(head->command->command, "pwd", 3) == 0)
		pwd(env);
	if (ft_strncmp(head->command->command, "cd", 2) == 0)
		cd(head->command->arguments[0], env);
	if (ft_strncmp(head->command->command, "echo", 4) == 0)
		echo(head);
	if (ft_strncmp(head->command->command, "env", 3) == 0)
		print_env(env);
	if (ft_strncmp(head->command->command, "export", 6) == 0)
		export(head->command->arguments, env);
	if (ft_strncmp(head->command->command, "unset", 5) == 0)
		unset(env, head->command->arguments);
	if (ft_strncmp(head->command->command, "exit", 4) == 0)
		ft_exit(head->command->arguments);
	return (0);
}
