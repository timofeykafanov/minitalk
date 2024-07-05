/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkafanov <tkafanov@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 10:34:34 by tkafanov          #+#    #+#             */
/*   Updated: 2024/07/05 14:16:46 by tkafanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"
#include <unistd.h>

t_data	g_data;

void	sig_usr(int signo, siginfo_t *info, void *useless)
{
	// static int	count = 0;
	// static char	symbol = 0;

	(void)useless;
	// (void)signo;
	usleep(1000);
	kill(info->si_pid, SIGUSR1);
	// if (g_data.bits <= 32)
	// 	return ;

	if (signo == SIGUSR1)
	{
		g_data.last_bit = 0;
		// symbol = symbol << 1;
		// count++;
	}
	else if (signo == SIGUSR2)
	{
		g_data.last_bit = 1;
		// symbol = (symbol << 1) | 1;
		// count++;
	}
	// if (count == 8)
	// {
	// 	ft_printf("%c", STDOUT_FILENO, symbol);
	// 	count = 0;
	// 	symbol = 0;
	// }
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
		if (g_data.bits > 32)
			return (0);
		if (g_data.bits <= 32)
		{
			ft_printf("last bit = %d\n", STDOUT_FILENO, g_data.last_bit);
			g_data.size = g_data.size * 2 + g_data.last_bit;
		}
		ft_printf("len = %d\n", STDOUT_FILENO, g_data.size);
		ft_printf("bits = %d\n", STDOUT_FILENO, g_data.bits);
		g_data.bits++;
		pause();
	}
	return (SUCCESS);
}
