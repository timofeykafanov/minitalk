/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkafanov <tkafanov@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 10:34:34 by tkafanov          #+#    #+#             */
/*   Updated: 2024/07/15 09:39:56 by tkafanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

static void	sig_usr(int signo, siginfo_t *info, void *useless)
{
	static int	bits = 1;
	static int	len = 0;
	static int	counter = 0;
	static char	*str;
	static char	symbol;

	(void)useless;
	if (bits <= 32)
		handle_len(signo, &len, &bits, &str);
	else
		handle_symbol(&symbol, &counter, signo);
	if (counter == 8)
	{
		str[len] = symbol;
		counter = 0;
		if (symbol == '\0')
			return (handle_end(&str, &bits, info));
		symbol = 0;
		len++;
	}
	if (kill(info->si_pid, SIGUSR1) == -1)
		handle_kill_protection(bits, &str);
}

int	main(void)
{
	struct sigaction	sa;
	sigset_t			set;

	ft_printf(PID, STDOUT_FILENO, getpid());
	sa.sa_sigaction = sig_usr;
	sa.sa_flags = SA_SIGINFO;
	sigfillset(&set);
	sa.sa_mask = set;
	if (sigaction(SIGUSR1, &sa, NULL) == -1
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
		return (ERROR);
	while (1)
		pause();
	return (SUCCESS);
}
