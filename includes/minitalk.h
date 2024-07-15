/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkafanov <tkafanov@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 09:07:09 by tkafanov          #+#    #+#             */
/*   Updated: 2024/07/15 09:45:08 by tkafanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include "../libft/libft.h"
# include <threads.h>
# include <signal.h>

# define MAX_PID 4194304

# define PID "Process ID: %d\n"

# define ERR_MESS_ARGS	"Error! Incorrect number of arguments!\n"
# define ERR_MESS_DIGIT	"Error! Process ID contains non digit character!\n"
# define ERR_MESS_PID	"Error! Process ID can not be greater than 4194304!\n"
# define ERR_MESS_EMPTY	"Error! Message string is empty!\n"
# define ERR_MESS_ALLOC	"Error! Allocation failed!\n"
# define ERR_MESS_RESP	"Error! No response was received from the server!\n"
# define ERR_MESS_SIG	"Error! Something went wrong with signals!\n"
# define MESS_SUCCESS	"Server successfully received the message!\n"

// client_utils.c

bool	is_process_id_valid(char *pid_str, int process_id);
bool	is_string_valid(char *str);

// server_utils.c

int		receive_len(int signo, int len);
void	handle_len(int signo, int *len, int *bits, char **str);
void	handle_symbol(char *symbol, int *counter, int signo);
void	handle_end(char **str, int *bits, siginfo_t *info);
void	handle_kill_protection(int bits, char **str);

#endif // MINITALK_H
