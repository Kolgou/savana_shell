#include "../minishell.h"
#include <signal.h>

static void sigint_handler(int sig)
{
    (void)sig;
    printf("\n");
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

static void sigquit_handler(int sig)
{
    (void)sig;
}

void setup_signal_handling(void)
{
    struct sigaction sa_int;
    struct sigaction sa_quit;

    sa_int.sa_handler = sigint_handler;
    sa_int.sa_flags = SA_RESTART;
    sigemptyset(&sa_int.sa_mask);
    sigaction(SIGINT, &sa_int, NULL);

    sa_quit.sa_handler = sigquit_handler;
    sa_quit.sa_flags = SA_RESTART;
    sigemptyset(&sa_quit.sa_mask);
    sigaction(SIGQUIT, &sa_quit, NULL);
}

// Ajout d'une fonction pour dupliquer l'environnement
char **duplicate_env(char **env)
{
    int count = 0;
    int i = 0;
    char **dup;

    while (env[count])
        count++;
    dup = malloc(sizeof(char *) * (count + 1));
    if (!dup)
        return (NULL);
    while (i < count)
    {
        dup[i] = ft_strdup(env[i]);
        i++;
    }
    dup[count] = NULL;
    return (dup);
}

int	main(__attribute__((unused)) int ac, __attribute__((unused)) char **av, char **env)
{
    char **my_env;

    my_env = duplicate_env(env);
    if (!my_env)
    {
        perror("duplication de l'environement");
        return (1);
    }
    setup_signal_handling();
    using_history();
    while (1)
    {
		if (!build_prompt(my_env))
			break ;
    }
    rl_clear_history();
    return (0);
}
