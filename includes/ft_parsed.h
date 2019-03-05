#ifndef FT_PARSED_H
#define FT_PARSED_H

char			*get_content(char *line, int type);
void			ft_parser(t_data **mydata);
char			*ft_get_info(char *line, char **p, char **name, int t);
void			ft_read_file(t_mydata *mydata);
t_point			ft_get_vector(char *value);
void			ft_parse_object(t_parsed *obj, char *line);

#endif
