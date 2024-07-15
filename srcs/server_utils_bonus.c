/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkafanov <tkafanov@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 09:31:32 by tkafanov          #+#    #+#             */
/*   Updated: 2024/07/15 09:40:03 by tkafanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

int	receive_len(int signo, int len)
{
	if (signo == SIGUSR1)
		return (len * 2);
	else if (signo == SIGUSR2)
		return (len * 2 + 1);
	return (len);
}

void	handle_len(int signo, int *len, int *bits, char **str)
{
	*len = receive_len(signo, *len);
	if (*bits == 32)
	{
		*str = (char *)malloc((*len + 1) * sizeof(char));
		if (!str)
		{
			ft_printf(ERR_MESS_ALLOC, STDERR_FILENO);
			exit(ERROR);
		}
		*len = 0;
	}
	(*bits)++;
}

void	handle_symbol(char *symbol, int *counter, int signo)
{
	if (signo == SIGUSR1)
		*symbol = *symbol * 2;
	else if (signo == SIGUSR2)
		*symbol = *symbol * 2 + 1;
	(*counter)++;
}

void	handle_end(char **str, int *bits, siginfo_t *info)
{
	ft_printf("%s\n", STDOUT_FILENO, *str);
	free(*str);
	*bits = 1;
	if (kill(info->si_pid, SIGUSR2) == -1)
	{
		ft_printf(ERR_MESS_SIG, STDERR_FILENO);
		exit(ERROR);
	}
}

void	handle_kill_protection(int bits, char **str)
{
	ft_printf(ERR_MESS_SIG, STDERR_FILENO);
	if (bits >= 32)
		free(*str);
	exit(ERROR);
}
