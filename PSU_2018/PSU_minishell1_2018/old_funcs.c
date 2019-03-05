/*
** EPITECH PROJECT, 2019
** old_funcs.c
** File description:
** recovery
*/

int launch_program(pid_t pid, char *to_run, char **av, char **env)
{
    int parent = getpid();

    if (pid != 0) {
        wait(&parent);
        if (is_str(to_run, "/usr/bin/clear") == 1)
            return (0);
        my_putstr("Program terminated.\n");
        my_putstr("Status:  ");
        if (parent == 139)
            my_putstr(strsignal(SIGSEGV));
        else
            my_putstr("OK");
        my_putstr("\n");
    } else
        execve(to_run, av, env);
}
