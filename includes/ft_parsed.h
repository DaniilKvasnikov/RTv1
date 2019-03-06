#ifndef FT_PARSED_H
#define FT_PARSED_H

void			ft_add_object(t_mydata *mydata, char *name, char *content);
char			*get_content(char *line, int type);
void			ft_parser(t_data **mydata);
char			*ft_get_info(char *line, char **p, char **name, int t);
void			ft_read_file(t_mydata *mydata);
t_point			ft_get_vector(char *value);
void			ft_parse_object(t_parsed **obj, char *line);
void			ft_parsed_to_obj(t_data **data);
unsigned int	ft_atoh(char *ap);
float			ft_atof(const char *s);

#endif
