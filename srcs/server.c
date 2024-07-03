/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkafanov <tkafanov@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 10:34:34 by tkafanov          #+#    #+#             */
/*   Updated: 2024/07/03 17:02:46 by tkafanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"


void	sig_usr(int signo, siginfo_t *info, void *context)
{
	static int	count = 0;
	static char	symbol = 0;

	(void)context;
	if (signo == SIGUSR1)
	{
		symbol = symbol * 2;
		kill(info->si_pid, SIGUSR1);
		count++;
	}
	else if (signo == SIGUSR2)
	{
		symbol = symbol * 2 + 1;
		kill(info->si_pid, SIGUSR1);
		count++;
	}
	if (count == 8)
	{
		ft_printf("%c", STDOUT_FILENO, symbol);
		count = 0;
		symbol = 0;
	}
}

int	main(void)
{
	struct sigaction	sa;
	sigset_t			set;

	ft_printf("Process ID: %d\n", STDOUT_FILENO, getpid());
	sa.sa_sigaction = sig_usr;
	sa.sa_flags = SA_SIGINFO;
	sigfillset(&set);
    sa.sa_mask = set;

	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (SUCCESS);
}
