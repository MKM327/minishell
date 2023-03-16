#include "minishell.h"

void	ctrl_c(int sig) // yazmayınca cast hatası verebiliyo
{
	(void)sig;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	/*

    ioctl () sistem çağrısı , temel alınan cihazı yönetir
    fd bağımsız değişkeni bir olmalıdır dosya tanıtıcıyı açın.
    İkinci argüman, cihaza bağlı bir istek kodudur.
    üçüncü bağımsız değişken, belleğe yazılmamış bir işaretçidir.
    */
	write(1, "\033[A", 3);
	// printf("\033c");

	/*
    C'de sıfır ile başlayan sayılar sekizli sayılardır. 8 tabanındaki sayılar.
    Yaptığı şey,
	sekizlik sayı 33ve ardından a ile temsil edilen karakteri yazdırmaktır 'c'.
    ASCII kodlamasında sekizlik sayı , terminal kontrol dizileri için
    ortak bir önek olan (kaçış) 33karakteridir ESC.
    */
}

void	ctrl_d(char *input)
{
	if (!input)
	{
		printf("\nexit\n");
		free(input);
		exit(1);
	}
}