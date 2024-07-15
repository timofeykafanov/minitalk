/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkafanov <tkafanov@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 08:09:53 by tkafanov          #+#    #+#             */
/*   Updated: 2024/07/15 08:10:19 by tkafanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

bool	is_process_id_valid(char *pid_str, int process_id)
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

bool	is_string_valid(char *str)
{
	if (!str[0])
		return (ft_printf(ERR_MESS_EMPTY, STDERR_FILENO), false);
	return (true);
}
