/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkafanov <tkafanov@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 10:34:28 by tkafanov          #+#    #+#             */
/*   Updated: 2024/07/15 09:48:06 by tkafanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

bool	g_response_received;

static void	response(int signo, siginfo_t *info, void *useless)
{
	(void)info;
	(void)useless;
	if (signo == SIGUSR2)
	{
		ft_printf(MESS_SUCCESS, STDOUT_FILENO);
		exit(SUCCESS);
	}
	g_response_received = true;
}

static void	send_symbol(int process_id, char symbol)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		g_response_received = false;
		if ((symbol >> i) % 2 == 0)
		{
			if (kill(process_id, SIGUSR1) == -1)
				exit(ERROR);
		}
		else
			if (kill(process_id, SIGUSR2) == -1)
				exit(ERROR);
		i--;
		while (!g_response_received)
		{
			sleep(5);
			if (!g_response_received)
			{
				ft_printf(ERR_MESS_RESP, STDERR_FILENO);
				exit(ERROR);
			}
		}
	}
}

static void	send_len(int process_id, int len)
{
	int	i;

	i = 31;
	while (i >= 0)
	{
		g_response_received = false;
		if ((len >> i) % 2 == 0)
		{
			if (kill(process_id, SIGUSR1) == -1)
				exit(ERROR);
		}
		else
			if (kill(process_id, SIGUSR2) == -1)
				exit(ERROR);
		i--;
		while (!g_response_received)
		{
			sleep(5);
			if (!g_response_received)
			{
				ft_printf(ERR_MESS_RESP, STDERR_FILENO);
				exit(ERROR);
			}
		}
	}
}

static void	send_message(int process_id, char *message)
{
	send_len(process_id, ft_strlen(message));
	while (*message)
	{
		send_symbol(process_id, *message);
		message++;
	}
	send_symbol(process_id, *message);
}

int	main(int ac, char **av)
{
	struct sigaction	sa;
	int					process_id;

	if (ac == 3)
	{
		ft_memset(&sa, 0, sizeof(sa));
		sa.sa_sigaction = response;
		sa.sa_flags = SA_SIGINFO;
		sigemptyset(&sa.sa_mask);
		process_id = ft_atoi(av[1]);
		if (!is_process_id_valid(av[1], process_id))
			return (ERROR);
		if (!is_string_valid(av[2]))
			return (ERROR);
		if (sigaction(SIGUSR1, &sa, NULL) == -1
			|| sigaction(SIGUSR2, &sa, NULL) == -1)
			return (ERROR);
		send_message(process_id, av[2]);
	}
	else
		return (ft_printf(ERR_MESS_ARGS, STDERR_FILENO), ERROR);
	return (SUCCESS);
}
