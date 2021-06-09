#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

typedef struct  s_cmd
{
    int is_child;
	pid_t		pid;
	int			pipe[2];
	char		**args;
    int end;
    struct  s_cmd *next;
}               t_cmd;


int execute(char **args, char **env)
{
    pid_t pid;

    pid = fork();
    if (pid == 0)
    {
        if (execve(args[0], args, env) == -1)
            exit(123);
    }
    waitpid (pid, NULL, 0);
    return (0);
}

int gwr;
// int num = 2;
int infile = 0;
int outfile = 0;
int background = 0;
int num = 3;

int pipes(t_cmd *cmds, char **env)
{
    int tmpin = dup(0);
    int tmpout = dup(1);

    int fdin;

    if (infile)
    {
        fdin = open("tmp", O_RDONLY, 0);
    }
    else 
    {
        // Use default input
        fdin = dup(tmpin);
    }

    int ret;
    int fdout;
    for (int i = 0; i < num; i++) 
    {
        //redirect input
        dup2(fdin, 0);
        close(fdin);

        //setup output
        if (i == num - 1)
        { 
            // Last simple command 
            if (outfile)
            {
                fdout = open("tmp", O_WRONLY, 0644);
            }
            else
            {
                // Use default output
                fdout = dup(tmpout);
            }
        } 
        else 
        {
            // Not last 
            //simple command
            //create pipe
            int fdpipe[2];
            pipe(fdpipe);
            fdout = fdpipe[1];
            fdin = fdpipe[0];
        }

        // Redirect output
        dup2(fdout, 1);
        close(fdout);
 
        // Create child process
        ret = fork();
        if (ret == 0)
        {
            // write(tmpout, cmds[i].args[0], strlen(cmds[i].args[0]));
            // write(tmpout, "\n", 1);
            // printf("%s\n", cmds[i].args[0]);
            execve(cmds[i].args[0], cmds[i].args, env);
            perror("failed exec");
            _exit(1);
        }
    } 
 
    //restore in/out defaults
    dup2(tmpin, 0);
    dup2(tmpout, 1);
    close(tmpin);
    close(tmpout);

    if (!background) 
    {
        // Wait for last command
        waitpid(ret, NULL, 0);
    }
    return (0);
}

int main(int argc, char **argv, char **env)
{
    t_cmd cmds[4];

    char *ls[] = {"/bin/ls", 0};
    char *grep[] = {"/usr/bin/grep", "lib", 0};
    char *wc[] = {"/usr/bin/wc", "-l", 0};

    cmds[0].args = ls;
    cmds[1].args = grep;
    cmds[2].args = wc;
    cmds[3].args = 0;

    cmds[0].end = 0;
    cmds[1].end = 0;
    cmds[2].end = 1;

    cmds[0].is_child = 0;
    cmds[1].is_child = 1;
    cmds[2].is_child = 1;

    cmds[0].next = &cmds[1];
    cmds[1].next = &cmds[2];
    cmds[2].next = &cmds[3];

    gwr = dup(1);

    pipes(cmds, env);
 
    return (4);
}