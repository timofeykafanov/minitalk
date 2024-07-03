/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkafanov <tkafanov@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 10:34:28 by tkafanov          #+#    #+#             */
/*   Updated: 2024/07/03 16:58:41 by tkafanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"
#include <signal.h>
#include <unistd.h>

static bool is_process_id_valid(char *pid_str, int process_id)
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

static bool is_string_valid(char *str)
{
	if (!str[0])
		return (ft_printf(ERR_MESS_EMPTY, STDERR_FILENO), false);
	return (true);
}

void	response(int signo)
{
	(void)signo;
	ft_printf(" response received\n", STDOUT_FILENO);
}

void	send_message(int process_id, char *message)
{
	int	i;

	while(*message)
	{
		i = 7;
		while (i >= 0)
		{
			ft_printf("%d", STDOUT_FILENO, (*message >> i) % 2);
			if ((*message >> i) % 2 == 0)
				kill(process_id, SIGUSR1);
			else
				kill(process_id, SIGUSR2);
			i--;
			signal(SIGUSR1, response);
			pause();
		}
		ft_printf("\n", STDOUT_FILENO);
		message++;
	}
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
		send_message(process_id, av[2]);
	}
	else
		return (ft_printf(ERR_MESS_ARGS, STDERR_FILENO), ERROR);
	return (SUCCESS);
}
