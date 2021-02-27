#include "readline.h"

void	reset_exit(int status);

/*! \fn set_new_user_in
 *  \b Компонента  \b : readline \n
 *  \b Назначение  \b : Записывает в глобальную строку user_in строку str \n
 *  \param[in] str строка для записи в user_in
 */
void	set_new_user_in(const char *str)
{
	size_t len;

	len = ft_strlen(str) / MIN_CMD_LENGTH;
	rp(NULL)->max_len = MIN_CMD_LENGTH * (len + 1);
	free(rp(NULL)->user_in);
	if (!(rp(NULL)->user_in = (char*)xmalloc(sizeof(char) * rp(NULL)->max_len)))
		reset_exit(1);
	ft_strcpy(rp(NULL)->user_in, str);
	rp(NULL)->len = ft_strlen(rp(NULL)->user_in);
	rp(NULL)->index = rp(NULL)->len;
}
