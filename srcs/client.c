/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkafanov <tkafanov@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 10:34:28 by tkafanov          #+#    #+#             */
/*   Updated: 2024/07/05 12:34:41 by tkafanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

bool	g_response_received;

static bool	is_process_id_valid(char *pid_str, int process_id)
{
	int	i;

	i = 0;
	while (pid_str[i])
	{
		if (!ft_isdigit(pid_str[i++]))
			return (ft_printf(ERR_MESS_DIGIT, STDERR_FILENO), false);
	}
	if (process_id > MAX_PID || ft_strlen(pid_str) > 7)
		return (ft_printf(ERR_MESS_PID, STDERR_FILENO), false);
	return (true);
}

static bool	is_string_valid(char *str)
{
	if (!str[0])
		return (ft_printf(ERR_MESS_EMPTY, STDERR_FILENO), false);
	return (true);
}

static void	response(int signo)
{
	(void)signo;
	ft_printf(" response received\n", STDOUT_FILENO);
	g_response_received = true;
}

static void	send_symbol(int process_id, char symbol)
{
	int 		i;

	i = 7;
	while (i >= 0)
	{
		ft_printf("%d", STDOUT_FILENO, (symbol >> i) % 2);
		if ((symbol >> i) % 2 == 0)
		{
			if (kill(process_id, SIGUSR1) == -1)
				exit(1);
		}
		else
		{
			if (kill(process_id, SIGUSR2) == -1)
				exit(1);
		}
		i--;
		g_response_received = false;
		if (!g_response_received)
		{
			sleep(10);
			if (!g_response_received)
			{
				ft_printf("Error! No response was received from the server!\n", STDERR_FILENO);
				exit(1);
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
		ft_printf("%d", STDOUT_FILENO, (len >> i) % 2);
		if ((len >> i) % 2 == 0)
		{
			if (kill(process_id, SIGUSR1) == -1)
				exit(1);
		}
		else
		{
			if (kill(process_id, SIGUSR2) == -1)
				exit(1);
		}
		i--;
		g_response_received = false;
		if (!g_response_received)
		{
			sleep(10);
			if (!g_response_received)
			{
				ft_printf("Error! No response was received from the server!\n", STDERR_FILENO);
				exit(1);
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
		ft_printf("\n", STDOUT_FILENO);
		message++;
	}
	send_symbol(process_id, *message);
}

int	main(int ac, char **av)
{
	int	process_id;

	if (ac == 3)
	{
		process_id = ft_atoi(av[1]);
		if (!is_process_id_valid(av[1], process_id))
			return (ERROR);
		if (!is_string_valid(av[2]))
			return (ERROR);
		signal(SIGUSR1, response);
		send_message(process_id, av[2]);
	}
	else
		return (ft_printf(ERR_MESS_ARGS, STDERR_FILENO), ERROR);
	return (SUCCESS);
}
