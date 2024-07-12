/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkafanov <tkafanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 10:34:34 by tkafanov          #+#    #+#             */
/*   Updated: 2024/07/12 10:10:09 by tkafanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

static int	receive_len(int signo, int len)
{
	if (signo == SIGUSR1)
		return (len * 2);
	else if (signo == SIGUSR2)
		return (len * 2 + 1);
	return (len);
}

void	sig_usr(int signo, siginfo_t *info, void *useless)
{
	static int	bits = 1;
	static int	len = 0;
	static int	counter = 0;
	static char	*str;
	static char	symbol;

	(void)useless;
	if (bits <= 32)
	{
		len = receive_len(signo, len);
		if (bits == 32)
		{
			str = (char *)malloc((len  + 1) * sizeof(char));
			if (!str)
			{
				ft_printf("Error! Allocation failed!\n", STDERR_FILENO);
				exit(ERROR);
			}
			len = 0;
		}
		bits++;
	}
	else
	{
		if (signo == SIGUSR1)
			symbol = symbol * 2;
		else if (signo == SIGUSR2)
			symbol = symbol * 2 + 1;
		counter++;
	}
	if (counter == 8)
	{
		str[len] = symbol;
		counter = 0;
		if (symbol == '\0')
		{
			ft_printf("%s\n", STDOUT_FILENO, str);
			free(str);
			bits = 1;
			kill(info->si_pid, SIGUSR2);
			return ;
		}
		symbol = 0;
		len++;
	}
	kill(info->si_pid, SIGUSR1);
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
	if (sigaction(SIGUSR1, &sa, NULL) == -1
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
		return (ERROR);
	while (1)
		pause();
	return (SUCCESS);
}
