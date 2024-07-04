/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkafanov <tkafanov@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 10:34:34 by tkafanov          #+#    #+#             */
/*   Updated: 2024/07/04 16:12:45 by tkafanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

t_data	g_data;

void	sig_usr(int signo, siginfo_t *info, void *useless)
{
	static int	count = 0;
	static char	symbol = 0;

	(void)useless;
	if (signo == SIGUSR1)
	{
		symbol = symbol << 1;
		kill(info->si_pid, SIGUSR1);
		count++;
	}
	else if (signo == SIGUSR2)
	{
		symbol = (symbol << 1) | 1;
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

	ft_bzero(&g_data, sizeof(g_data));
	ft_printf("Process ID: %d\n", STDOUT_FILENO, getpid());
	sa.sa_sigaction = sig_usr;
	sa.sa_flags = SA_SIGINFO;
	sigfillset(&set);
	sa.sa_mask = set;
	if (sigaction(SIGUSR1, &sa, NULL) == -1
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
		return (ERROR);
	while (1)
	{
		g_data.bits++;
		if (g_data.bits <= 32)
		{
			g_data.size = (g_data.size * 2) + g_data.last_bit;
		}
		pause();
	}
	return (SUCCESS);
}
