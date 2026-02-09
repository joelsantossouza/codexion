/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 13:13:00 by joesanto          #+#    #+#             */
/*   Updated: 2026/02/09 13:14:34 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "errors.h"

void	error(enum e_exit_status err_code)
{
	const char	*err_msg = get_error_msg(err_code);

	fprintf(stderr, "%s", err_msg);
}
