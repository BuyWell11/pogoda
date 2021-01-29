#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <locale.h>
#include <string.h>
#include <time.h>
#define SIZE 50

typedef struct string_ {
	char s[SIZE];
}strings;

typedef struct _list {
	char listname[20];
	strings frase[8];
	int cur;
}list;

typedef struct day {
	int date[3];
	int nighttemp[2];
	int daytemp[2];
	int feelstemp[2];
	char fall[20];
	int windspeed[2];
	char windway[20];
	int gust[2];
	int pressure;
	char fact[20];
	char time_of_year[20];
	char month[20];
}weather;

typedef struct rates {
	int coldTempRate; // 5 - death, 4 - bad, 3 - oh, 2 - ok, 1 - nice
	int hotTempRate; // 5 - death, 4 - bad, 3 - oh, 2 - ok, 1 - nice
	int windSpeedRate; // 5 - death, 4 - bad, 3 - oh, 2 - ok, 1 - nice
	int pressureRate; // 0 - low, 1 - ok, 2 - high
} rate;



void makedic(list dic[], FILE* frases, int diccur) {
	char str[SIZE] = { 0 };
	int cur = 0;
	fgets(str, SIZE, frases);
	str[strlen(str) - 1] = '\0';
	strcpy(dic[diccur].listname, str);
	fgets(str, SIZE, frases);
	while (strcmp(str, "\n") != 0 && strcmp(str, dic[diccur].frase[cur-1].s) != 0) {
		str[strlen(str) - 1] = '\0';
		strcpy(dic[diccur].frase[cur].s, str);
		cur++;
		fgets(str, SIZE, frases);
	}
	dic[diccur].cur = cur;
}

char * findFrase(char name[], list dic[], int diccur) {
	char str[20] = { 0 };
	int random = 0;
	strcpy(str, name);
	for (int i = 0; i < diccur; i++)
	{
		if (strcmp(str, dic[i].listname) == 0) {
			random = rand() % dic[i].cur;
			return dic[i].frase[random].s;
		}
	}
}

void makesent(list dic[], weather days[], int diccur, rate rates[], int dayscur) {
	printf("%s ", findFrase("greeting", dic, diccur));
	printf("%s ", findFrase("places", dic, diccur));
	printf("%d %s.\n", days[dayscur].date[0], days[dayscur].month);
	if (strcmp(days[dayscur].fall, "снега") == 0)
		printf("%s%s %s осадки в виде %s.\n", findFrase("snow", dic, diccur), findFrase("connection", dic, diccur), findFrase("verbs", dic, diccur), days[dayscur].fall);
	if (strcmp(days[dayscur].fall, "дождя") == 0)
		printf("%s%s %s осадки в виде %s.\n", findFrase("rain", dic, diccur), findFrase("connection", dic, diccur), findFrase("verbs", dic, diccur), days[dayscur].fall);
	if (strcmp(days[dayscur].fall, "нет") == 0)
		printf("%s%s отсутствия осадков.\n", findFrase("no fall", dic, diccur), findFrase("no fall connect", dic, diccur));
	if (rates[dayscur].coldTempRate > rates[dayscur].hotTempRate) {
		switch (rates[dayscur].coldTempRate) {
		case 1:
			printf("%s%s температура воздуха составляет %d градусов днём и %d градусов ночью.\n", findFrase("bit cold", dic, diccur), findFrase("connection", dic, diccur), days[dayscur].daytemp[0], days[dayscur].nighttemp[0]);
			break;
		case 2:
		case 3:
			printf("%s%s температура воздуха составляет %d градусов днём и %d градусов ночью.\n", findFrase("cold", dic, diccur), findFrase("connection", dic, diccur), days[dayscur].daytemp[0], days[dayscur].nighttemp[0]);
			break;
		case 4:
		case 5:
			printf("%s%s температура воздуха составляет %d градусов днём и %d градусов ночью.\n", findFrase("very cold", dic, diccur), findFrase("connection", dic, diccur), days[dayscur].daytemp[0], days[dayscur].nighttemp[0]);
			break;
		}
	}
	if (rates[dayscur].hotTempRate > rates[dayscur].coldTempRate) {
		switch (rates[dayscur].hotTempRate) {
		case 1:
			printf("%s%s температура воздуха составляет %d градусов днём и %d градусов ночью.\n", findFrase("bit hot", dic, diccur), findFrase("connection", dic, diccur), days[dayscur].daytemp[0], days[dayscur].nighttemp[0]);
			break;
		case 2:
		case 3:
			printf("%s%s температура воздуха составляет %d градусов днём и %d градусов ночью.\n", findFrase("hot", dic, diccur), findFrase("connection", dic, diccur), days[dayscur].daytemp[0], days[dayscur].nighttemp[0]);
			break;
		case 4:
		case 5:
			printf("%s%s температура воздуха составляет %d градусов днём и %d градусов ночью.\n", findFrase("very hot", dic, diccur), findFrase("connection", dic, diccur), days[dayscur].daytemp[0], days[dayscur].nighttemp[0]);
			break;
		}
	}
	switch (rates[dayscur].windSpeedRate) {
	case 1:
		printf("%s%s скорость ветра составляет %d м/с.\n", findFrase("no wind", dic, diccur), findFrase("connection", dic, diccur), days[dayscur].windspeed[0]);
		break;
	case 2:
	case 3:
		printf("%s%s скорость ветра составляет %d м/с.\n", findFrase("wind", dic, diccur), findFrase("connection", dic, diccur), days[dayscur].windspeed[0]);
		break;
	case 4:
	case 5:
		printf("%s%s скорость ветра составляет %d м/с.\n", findFrase("strong wind", dic, diccur), findFrase("connection", dic, diccur), days[dayscur].windspeed[0]);
		break;
	}
	switch (rates[dayscur].pressureRate) {
	case 1:
		printf("%s%s давление равно %d паскалям.\n", findFrase("low pressure", dic, diccur), findFrase("connection", dic, diccur), days[dayscur].pressure);
		break;
	case 2:
		printf("%s%s давление равно %d паскалям.\n", findFrase("normal pressure", dic, diccur), findFrase("connection", dic, diccur), days[dayscur].pressure);
		break;
	case 3:
		printf("%s%s давление равно %d паскалям.\n", findFrase("high pressure", dic, diccur), findFrase("connection", dic, diccur), days[dayscur].pressure);
		break;
	}
}

int main() {
	setlocale(LC_ALL, "RUS");
	printf("Ща запущю погодь...\n");
	srand(time(NULL));
	weather days[SIZE];
	/*fras frase;*/
	list dic[SIZE];
	rate rates[SIZE];
	int cur = 0, dayscur = 0, diccur = 0;
	FILE* input;
	FILE* frases;
	input = fopen("input.txt", "rt");
	frases = fopen("frases.txt", "rt");
	char str[SIZE] = { 0 };
	char c = '0';
	while (c != EOF) {
		fscanf(input, "%d.%d.%d\t%d..%d\t%d..%d\t%d..%d\t", &days[cur].date[0],
			&days[cur].date[1],
			&days[cur].date[2],
			&days[cur].nighttemp[0],
			&days[cur].nighttemp[1],
			&days[cur].daytemp[0],
			&days[cur].daytemp[1],
			&days[cur].feelstemp[0],
			&days[cur].feelstemp[1]);
		fscanf(input, "%s", &str);
		if (strcmp(str, "снег"))
			strcpy(days[cur].fall, "снега");
		if (strcmp(str, "дождь"))
			strcpy(days[cur].fall, "дождя");
		if (strcmp(str, "нет"))
			strcpy(days[cur].fall, "нет");
		fscanf(input, "%s", &str);
		if (strlen(str) == 3) {
			sscanf(str, "%d-%d", &days[cur].windspeed[0], &days[cur].windspeed[1]);
		}
		else {
			sscanf(str, "%d", &days[cur].windspeed[0]);
		}
		fscanf(input, "%s", &days[cur].windway);
		fscanf(input, "%s", &str);
		if (strlen(str) == 3) {
			sscanf(str, "%d-%d", &days[cur].gust[0], &days[cur].gust[1]);
		}
		else {
			sscanf(str, "%d", &days[cur].gust[0]);
		}
		fscanf(input, "%d", &days[cur].pressure);
		c = fgetc(input);
		if (c == ' ') {
			fscanf(input, "%s", &days[cur].fact);
			c = fgetc(input);
		}
		switch (days[cur].date[1]) {
		case 1:
			strcpy(days[cur].month, "января");
			strcpy(days[cur].time_of_year, "зима");
			break;
		case 2:
			strcpy(days[cur].month, "февраля");
			strcpy(days[cur].time_of_year, "зима");
			break;
		case 3:
			strcpy(days[cur].month, "марта");
			strcpy(days[cur].time_of_year, "весна");
			break;
		case 4:
			strcpy(days[cur].month, "апреля");
			strcpy(days[cur].time_of_year, "весна");
			break;
		case 5:
			strcpy(days[cur].month, "мая");
			strcpy(days[cur].time_of_year, "весна");
			break;
		case 6:
			strcpy(days[cur].month, "июня");
			strcpy(days[cur].time_of_year, "лето");
			break;
		case 7:
			strcpy(days[cur].month, "июля");
			strcpy(days[cur].time_of_year, "лето");
			break;
		case 8:
			strcpy(days[cur].month, "августа");
			strcpy(days[cur].time_of_year, "лето");
			break;
		case 9:
			strcpy(days[cur].month, "сентября");
			strcpy(days[cur].time_of_year, "осень");
			break;
		case 10:
			strcpy(days[cur].month, "октября");
			strcpy(days[cur].time_of_year, "осень");
			break;
		case 11:
			strcpy(days[cur].month, "ноября");
			strcpy(days[cur].time_of_year, "осень");
			break;
		case 12:
			strcpy(days[cur].month, "декабря");
			strcpy(days[cur].time_of_year, "зима");
			break;
		}
		cur++;
	}
	dayscur = cur;
	cur = 0;
	while (!feof(frases)) {
		c = getc(frases);
		if (c == '-') {
			makedic(dic, frases, diccur);
			diccur++;
		}
	}
	fclose(input);
	fclose(frases);
	for (int dayCount = 0; dayCount < dayscur; ++dayCount)
	{
		// TEMP RATE
		if (days[dayCount].daytemp[0] >= 30) rates[dayCount].hotTempRate = 5;
		if (days[dayCount].daytemp[0] >= 20 && days[dayCount].daytemp[0] <= 29) rates[dayCount].hotTempRate = 4;
		if (days[dayCount].daytemp[0] >= 10 && days[dayCount].daytemp[0] <= 19) rates[dayCount].hotTempRate = 3;
		if (days[dayCount].daytemp[0] >= 5 && days[dayCount].daytemp[0] <= 9) rates[dayCount].hotTempRate = 2;
		if (days[dayCount].daytemp[0] == 0) rates[dayCount].hotTempRate = 1;

		if (days[dayCount].daytemp[0] <= -30) rates[dayCount].coldTempRate = 5;
		if (days[dayCount].daytemp[0] >= -29 && days[dayCount].daytemp[0] <= -20) rates[dayCount].coldTempRate = 4;
		if (days[dayCount].daytemp[0] >= -19 && days[dayCount].daytemp[0] <= -10) rates[dayCount].coldTempRate = 3;
		if (days[dayCount].daytemp[0] >= -9 && days[dayCount].daytemp[0] <= -5) rates[dayCount].coldTempRate = 2;
		if (days[dayCount].daytemp[0] == 0) rates[dayCount].coldTempRate = 1;

		// WIND RATE
		if (days[dayCount].windspeed[0] >= 33) rates[dayCount].windSpeedRate = 5;
		if (days[dayCount].windspeed[0] <= 32 && days[dayCount].windspeed[0] >= 25) rates[dayCount].windSpeedRate = 4;
		if (days[dayCount].windspeed[0] <= 24 && days[dayCount].windspeed[0] >= 15) rates[dayCount].windSpeedRate = 3;
		if (days[dayCount].windspeed[0] <= 14 && days[dayCount].windspeed[0] >= 6) rates[dayCount].windSpeedRate = 2;
		if (days[dayCount].windspeed[0] <= 5 && days[dayCount].windspeed[0] >= 0) rates[dayCount].windSpeedRate = 1;

		// PRESSURE RATE
		if (days[dayCount].pressure <= 740) rates[dayCount].pressureRate = 0;
		if (days[dayCount].pressure <= 759 && days[dayCount].pressure >= 741) rates[dayCount].pressureRate = 1;
		if (days[dayCount].pressure >= 760) rates[dayCount].pressureRate = 2;
	}
	makesent(dic, days, diccur, rates, 1);
}
