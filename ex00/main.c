

t_dictionary	parse_dictionary(char *str)
{
	t_dictionary	dictionary;
	int				line_count;
	int				i;
	char			*line;
	char			**key_value_pair;

	line_count = 0;
	i = 0;
	str = eliminate_blank_line(str);
	line_count = count_line(str);
	dictionary.keys = malloc(sizeof(int) * line_count);
	dictionary.values = malloc(sizeof(char *) * line_count);
	line = strtok(str, "\n");
	while (line != NULL)
	{
		key_value_pair = ft_split(line, ":");
		dictionary.keys[i] = ft_atoi(trim(key_value_pair[0]));
		dictionary.values[i] = trim(key_value_pair[1]);
		free(key_value_pair);
		line = strtok(NULL, "\n");
		i++;
	}
	return (dictionary);
}
