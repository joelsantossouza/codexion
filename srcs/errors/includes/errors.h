/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 13:10:53 by joesanto          #+#    #+#             */
/*   Updated: 2026/02/09 13:17:01 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

enum	e_exit_status
{
	SUCCESS = 0,

	ERR_PARSER_ARGC,
	ERR_PARSER_SCHEDULER,
	ERR_PARSER_NOT_DIGIT,
	ERR_PARSER_NEG_INT,
	ERR_PARSER_OVERFLOW,
	ERR_PARSER_MAX_CODERS,

	ERR_LOG_INVALID_EVENT,
	ERR_LOG_SIM_STOPPED,

	ERR_DONGLES_INIT,
	ERR_CODERS_INIT,

	ERR_THREAD_INIT
};

# define ERR_PARSER_ARGC_MSG		"Error: Wrong number of arguments\n"
# define ERR_PARSER_SCHEDULER_MSG	"Error: Invalid scheduler. Use \'fifo\' or \'edf\'\n"
# define ERR_PARSER_NOT_DIGIT_MSG	"Error: Input contains non-digit characters\n"
# define ERR_PARSER_NEG_INT_MSG		"Error: Input contains negative integers\n"
# define ERR_PARSER_OVERFLOW_MSG	"Error: Value exceeds integer limits\n"
# define ERR_PARSER_MAX_CODERS_MSG	"Error: Value exceeds MAX_CODERS limits\n"

# define ERR_DONGLES_INIT_MSG		"Error: Failed to initialize dongles\n"
# define ERR_CODERS_INIT_MSG		"Error: Failed to initialize coders\n"

# define ERR_THREAD_INIT_MSG		"Error: Failed to create thread\n"

const char	*get_error_msg(enum e_exit_status err_code);
void		error(enum e_exit_status err_code);

#endif
