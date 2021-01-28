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

int main() {
	setlocale(LC_ALL, "RUS");
	printf("ўа запущю погодь...\n");
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
		fscanf(input, "%d.%d.%d\t%d..%d\t%d..%d\t%d..%d\t%s\t", &days[cur].date[0],
			&days[cur].date[1],
			&days[cur].date[2],
			&days[cur].nighttemp[0],
			&days[cur].nighttemp[1],
			&days[cur].daytemp[0],
			&days[cur].daytemp[1],
			&days[cur].feelstemp[0],
			&days[cur].feelstemp[1],
			&days[cur].fall);
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
			strcpy(days[cur].month, "€нвар€", SIZE);
			strcpy(days[cur].time_of_year, "зима", SIZE);
			break;
		case 2:
			strcpy(days[cur].month, "феврал€", SIZE);
			strcpy(days[cur].time_of_year, "зима", SIZE);
			break;
		case 3:
			strcpy(days[cur].month, "марта", SIZE);
			strcpy(days[cur].time_of_year, "весна", SIZE);
			break;
		case 4:
			strcpy(days[cur].month, "апрел€", SIZE);
			strcpy(days[cur].time_of_year, "весна", SIZE);
			break;
		case 5:
			strcpy(days[cur].month, "ма€", SIZE);
			strcpy(days[cur].time_of_year, "весна", SIZE);
			break;
		case 6:
			strcpy(days[cur].month, "июн€", SIZE);
			strcpy(days[cur].time_of_year, "лето", SIZE);
			break;
		case 7:
			strcpy(days[cur].month, "июл€", SIZE);
			strcpy(days[cur].time_of_year, "лето", SIZE);
			break;
		case 8:
			strcpy(days[cur].month, "августа", SIZE);
			strcpy(days[cur].time_of_year, "лето", SIZE);
			break;
		case 9:
			strcpy(days[cur].month, "сент€бр€", SIZE);
			strcpy(days[cur].time_of_year, "осень", SIZE);
			break;
		case 10:
			strcpy(days[cur].month, "окт€бр€", SIZE);
			strcpy(days[cur].time_of_year, "осень", SIZE);
			break;
		case 11:
			strcpy(days[cur].month, "но€бр€", SIZE);
			strcpy(days[cur].time_of_year, "осень", SIZE);
			break;
		case 12:
			strcpy(days[cur].month, "декабр€", SIZE);
			strcpy(days[cur].time_of_year, "зима", SIZE);
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
}