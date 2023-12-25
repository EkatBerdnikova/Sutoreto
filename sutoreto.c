#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#define N 8
int vivod(int a[N][N]);
int proverka(int a[N][N], int b[N][N], int n, int m);
int file(int a[N][N], int b[N][N]);
int povtorstr(int a[N][N], int n, int m);
int povtorstolb(int a[N][N], int n, int m);
int kolvo(int a[N][N]);
int reit(int k);
void main()
{
	setlocale(LC_ALL, "RUS");
	int v, n, k, m = 0;
	int a[N][N];//массив для исходного поля
	int b[N][N];//массив для результирующего поля

	file(a, b); //занесение данных в массивы из файла
	printf("Игра-головоломка Суторето");
	do {
		printf("\nВыберите\n1)Правила головоломки\n2)Начать раунд\n3)Создать уровень\n4)Выйти\n\n");
		scanf("%d", &v);
		printf("\n\n");
		switch (v) {
		case 1:
			puts("\nНеобходимо заполнить числами пустые клетки таким образом, чтобы в промежутках между закрашенными клетками по горизонтали и по вертикали образовывались наборы последовательных чисел, но не обязательно стоящих по порядку (например,2-3-4)\n");
			break;
		case 2:
			vivod(a);//вывод исходного поля
			printf("\nЧтобы выйти, введите номер строки = 0");
			do {
				printf("\nВведите номер строки - ");
				scanf("%d", &n);
				getchar();
				if (n == 0) break;
				printf("\nВведите номер столбца - ");
				scanf("%d", &m);
				getchar();
				printf("\nВведите ответ - ");
				scanf("%d", &a[n - 1][m - 1]);
				printf("\n");
				proverka(a, b, n - 1, m - 1);//проверка решения
				vivod(a);
				kolvo(a);//подсчет количества оставшихся незаполненных клеток
			} while (n != 0);
			printf("\nПоставьте оценку игре\n");
			scanf("%d", &k);
			reit(k); //занесение оценки в файл с рейтингом
			break;
		case 3:
			printf("\n\n");
			printf("Создание исходного поля...\n");
			printf("Чтобы обозначить пустую ячейку вводите 0, чтобы закрашенную - 10\n\n");
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < N; j++) {
					printf("[%d][%d] = ", i + 1, j + 1);
					scanf("%d", &a[i][j]); //ввод значения в ячейку массива
				}
				printf("|\n");
			}
			vivod(a);
			printf("\nСоздание результирующего поля...\n");
			printf("Чтобы обозначить пустую ячейку вводите 0, чтобы закрашенную - 10\n\n");
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < N; j++) {
					printf("[%d][%d] = ", i + 1, j + 1);
					scanf("%d", &b[i][j]);
				}
				printf("|\n");
			}
			vivod(b);
			break;
		case 4:
			printf("\nЗавершение......\n");
			break;
		default:
			printf("Неизвестная команда, попробуйте снова");
			continue;
		}
	} while (v != 4);
}
int vivod(int a[N][N]) {
	printf("   ");
	for (int i = 0; i < N; i++) {
		printf("| %d", i + 1);
	}
	printf("|\n");
	printf("___|__|__|__|__|__|__|__|__|\n");
	for (int i = 0; i < N; i++)
	{
		printf("%d__", i + 1);
		for (int j = 0; j < N; j++)
		{
			if (a[i][j] == 0)
				printf("|__");
			else {
				if (a[i][j] == 10)
					printf("|##");
				else
					printf("|_%d", a[i][j]);
			}
		}
		printf("|\n");
	};
	return 0;
}
int proverka(int a[N][N], int b[N][N], int n, int m) {
	if (a[n][m] < 10) {
		if (a[n][m] == b[n][m]) {
			printf("\nВерный ход!\n");
			return 1;
		}
		else {
			printf("\nНеверный ход!\n\n");
			if ((povtorstr(a, n, m)) || (povtorstolb(a, n, m))) {
				printf("Обнаружены повторения цифры \n\n");
			}
			a[n][m] = 0;
			return 0;
		}
	}
	else {
		printf("Принимаются значения <10\n");
		a[n][m] = 0;
		return 0;
	}
}
int file(int a[N][N], int b[N][N]) {
	char fname1[20] = "nachalnoepole.txt";
	FILE* nachpole;
	char fname2[20] = "rezultpole.txt";
	FILE* rezpole;
	if (((nachpole = fopen(fname1, "r")) == NULL) || ((rezpole = fopen(fname2, "r")) == NULL))
	{
		printf("Ошибка открытия файла для записи");
		return 0;
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			fscanf(nachpole, "%d ", &a[i][j]);
			fscanf(rezpole, "%d ", &b[i][j]);
		}
	}
	fclose(nachpole);
	fclose(rezpole);
	return 1;
}
int povtorstr(int a[N][N], int n, int m) {
	//Проверка строк
	int p[N] = { 0 };
	for (int i = 0; i < N; i++) {
		if (a[n][i] == 10) {
			for (int j = 0; j < N; j++) {
				p[j] = 0;
			}
		}
		if (p[a[n][i]] == 1) {
			return 1;

		}
		if ((a[n][i] != 0) && (a[n][i] != 10)) {
			p[a[n][i]] = 1;
		}
		else {
			p[a[n][i]] = 0;
		}
	}
	return 0;
}
int povtorstolb(int a[N][N], int n, int m) {
	//Проверка столбцов
	int p[N] = { 0 };
	for (int i = 0; i < N; i++) {
		if (a[i][m] == 10) {
			for (int j = 0; j < N; j++) {
				p[j] = 0;
			}

		}
		if (p[a[i][m]] == 1) {
			return 1;

		}
		if ((a[i][m] != 0) && (a[i][m] != 10)) {
			p[a[i][m]] = 1;
		}
		else {
			p[a[i][m]] = 0;
		}
	}
	return 0;
}
int kolvo(int a[N][N]) {
	int cnt = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (a[i][j] == 0) {
				cnt++;
			}
		}
	}
	if (cnt == 0) {
		printf("\nВы победили!\n");
		return 1;
	}

	else {
		printf("Осталось заполнить %d клеток\n", cnt);
		return 0;
	}
}
int reit(int k) {
	char fname3[20] = "reiting.txt";
	FILE* reiting;
	if ((reiting = fopen(fname3, "a")) == NULL)
	{
		printf("Ошибка открытия файла для записи");
		return 0;
	}
	fprintf(reiting, "Оценка: %d\n", k);
	fclose(reiting);
	return 1;
}