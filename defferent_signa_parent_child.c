/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defferent_signa_parent_child.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 11:24:22 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/05/26 11:27:03 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void parentSignalHandler(int signum) {
    printf("Parent: Received SIGINT signal. Ignoring it.\n");
}

void childSignalHandler(int signum) {
    printf("Child: Received SIGINT signal. Exiting.\n");
    exit(0);
}

int main() {
    pid_t pid;

    // Install signal handlers for parent and child processes
    signal(SIGINT, parentSignalHandler);

    pid = fork();

    if (pid < 0) 
	{
        fprintf(stderr, "Fork failed.\n");
        return 1;
    }
	else if (pid == 0) 
	{
        // Child process
        signal(SIGINT, childSignalHandler);
        printf("Child: PID=%d\n", getpid());
        while (1) {
            // Child process will keep running until it receives SIGINT
            sleep(10);
        }
    }
	else 
	{
        // Parent process
        printf("Parent: PID=%d\n", getpid());
        printf("Press Ctrl+C to send SIGINT signal.\n");

        // Parent process will wait for the child process to terminate
        wait(NULL);
        printf("Parent: Child process terminated.\n");
    }
    return 0;
}