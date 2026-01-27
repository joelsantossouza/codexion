/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_error_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 13:49:52 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/27 14:42:05 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdint.h>
#include "errors.h"

const char	*get_error_str(uint32_t error_code)
{
	if (error_code == ARGC_ERROR)
		return (ARGC_ERROR_MSG);
	if (error_code == SCHEDULER_ERROR)
		return (SCHEDULER_ERROR_MSG);
	if (error_code == NONNUMERIC_ERROR)
		return (NONNUMERIC_ERROR_MSG);
	if (error_code == NEGATIVE_INT_ERROR)
		return (NEGATIVE_INT_ERROR_MSG);
	if (error_code == INT_OVERFLOW_ERROR)
		return (INT_OVERFLOW_ERROR_MSG);
	return (NULL);
}
