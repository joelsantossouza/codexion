/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion_parser_internal.h                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 19:21:57 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/28 16:23:23 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_PARSER_INTERNAL_H
# define CODEXION_PARSER_INTERNAL_H

# include <stdbool.h>
# include "codexion_parser.h"

# define INT_MAX	"2147483647"
# define PROGRAM_USAGE \
	"Usage:\n" \
	" - <number_of_coders>\n" \
	" - <time_to_burnout>\n" \
	" - <time_to_compile>\n" \
	" - <time_to_debug>\n" \
	" - <time_to_refactor>\n" \
	" - <number_of_compiles_required>\n" \
	" - <dongle_cooldown>\n" \
	" - <scheduler (\'fifo\' | \'edf\')>\n"

bool	is_str_numeric(const char *str);
int		nbrcmp(const char *nbr1, const char *nbr2);

#endif
