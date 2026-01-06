/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 13:49:52 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/06 16:10:36 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_errors.h"
#include <stdlib.h>

const char *parsing_error(unsigned int error_code)
{
	if (error_code == ARGC_ERROR)
		return (ARGC_ERROR_MSG);
	if (error_code == SCHEDULER_ERROR)
		return (SCHEDULER_ERROR_MSG);
	if (error_code == NONNUMERIC_ERROR)
		return (NONNUMERIC_ERROR_MSG);
	if (error_code == NEGATIVE_INT_ERROR)
		return (NEGATIVE_INT_ERROR_MSG);
	if (error_code == INT_OVERFLOW)
		return (INT_OVERFLOW_MSG);
	return (NULL);
}
