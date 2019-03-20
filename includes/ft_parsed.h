/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsed.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrankly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 21:04:50 by jfrankly          #+#    #+#             */
/*   Updated: 2019/03/19 21:04:51 by jfrankly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PARSED_H
# define FT_PARSED_H

void			ft_create_and_add_object
				(t_mydata *mydata, char *name, char *content);
char			*get_content(char *line, int type);
void			ft_parser(t_mydata **mydata, int fd);
char			*ft_get_info(char *line, char **p, char **name, int t);
void			ft_read_file(t_mydata *mydata, int fd);
t_point			ft_get_vector(char *value);
void			ft_parse_object(t_parsed **obj, char *line);
void			ft_parsed_to_obj(t_data **data);
unsigned int	ft_atoh(char *ap);
float			ft_atof(const char *s);
void			ft_parse_lights(t_data **data);
void			ft_parse_error(char *msg);
int				ft_count_chars(char *str, char c);

#endif
