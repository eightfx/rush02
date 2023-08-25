#include <unistd.h>

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

// 引数として文字列（辞書ファイルの中身）を受け取り、それが辞書のルールに基づいている場合は1、基づいていない場合は0を返す
// ex: 「42 :: forty-two」は [a number][0 to n spaces]:[0 to n spaces][any printable characters]\nという記述に則っていないので0
int		is_valid_dict(char *str);

void	print_dict_error(void)
{
	write(1, "Dict Error\n", 11);
}
