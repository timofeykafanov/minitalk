/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkafanov <tkafanov@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 09:07:09 by tkafanov          #+#    #+#             */
/*   Updated: 2024/07/05 11:58:11 by tkafanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include "../libft/libft.h"
# include <threads.h>
# include <signal.h>

#include <stdio.h>

# define MAX_PID 4194304

# define ERR_MESS_ARGS	"Error! Incorrect number of arguments!\n"
# define ERR_MESS_DIGIT	"Error! Process ID contains non digit character!\n"
# define ERR_MESS_PID	"Error! Process ID can not be greater than 4194304!\n"
# define ERR_MESS_EMPTY	"Error! Message string is empty!\n"

typedef struct s_data
{
    char	*string;
	int		size;
	int		bits;
	int		last_bit;
}	t_data;

#endif // MINITALK_H
