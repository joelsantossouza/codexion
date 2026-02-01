/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_error_msg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 13:49:52 by joesanto          #+#    #+#             */
/*   Updated: 2026/02/01 18:46:35 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdint.h>
#include "errors.h"

const char	*get_error_msg(enum e_exit_status err_code)
{
	if (err_code == ERR_PARSER_ARGC)
		return (ERR_PARSER_ARGC_MSG);
	if (err_code == ERR_PARSER_SCHEDULER)
		return (ERR_PARSER_SCHEDULER_MSG);
	if (err_code == ERR_PARSER_NOT_DIGIT)
		return (ERR_PARSER_NOT_DIGIT_MSG);
	if (err_code == ERR_PARSER_NEG_INT)
		return (ERR_PARSER_NEG_INT_MSG);
	if (err_code == ERR_PARSER_OVERFLOW)
		return (ERR_PARSER_OVERFLOW_MSG);
	if (err_code == ERR_PARSER_MAX_CODERS)
		return (ERR_PARSER_MAX_CODERS_MSG);
	return (NULL);
}
