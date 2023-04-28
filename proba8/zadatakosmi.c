/*8. u mapi data.txt su studenti spremljeni npr.
Sabic Krizan	7.2.2001
Glumac Kristijan	3.11.2002

zadatak je unit sve studente u vezanu listu..ispisat listu sortiranu po datumu rodenja od najstarijeg do najmladeg.
zatim korisnik unosi ime i ispisuju mu se svi studenti s tim imenom i njihovi datumi rodenja.
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Datum {

	int dan, mjesec, godina;

};

struct _osobe;
typedef struct _osobe osobe;
typedef osobe* position;

struct _osobe {

	char prezime[20];
	char ime[20];
	struct Datum datumrodenja;

	position next;
};

int CitajDat(position head);
int UnosUListu(position head, char prezime[20], char ime[20], struct Datum datrod);
int IspisListe(position head);
int PronadiIme(position head, char unos[20]);


int main()
{
	osobe head;
	head.next = NULL;

	int result;
	char unos[20];

	result = CitajDat(&head);
	result = IspisListe(&head);
	printf("\nunesite neko od ovih imena \n");
	scanf("%s", unos);
	result = PronadiIme(&head, unos);


	return 0;
}

int CitajDat(position head)
{
	char buffer[1024] = "\0";
	char prezime[20] = "\0";
	char ime[20] = "\0";
	struct Datum datum;

	FILE* file;
	file = fopen("data.txt", "r");
	if (file == NULL)
	{
		printf("nije se otvorila");
		return -1;
	}

	while (!feof(file))
	{
		strcpy(buffer, "\0");
		strcpy(prezime, "\0");
		strcpy(ime, "\0");

		fgets(buffer, 1024 - 1, file);

		if (strlen(buffer) > 1)
		{

			sscanf(buffer, "%s %s %d.%d.%d", prezime, ime, &datum.dan, &datum.mjesec, &datum.godina);
			int result = UnosUListu(head, prezime, ime, datum);
			if (result == -1)
			{
				printf("nije se spremilo u listu");
				fclose(file);
				return -1;
			}
		}
	}

	fclose(file);
	return 0;
}

int UnosUListu(position head, char prezime[20], char ime[20], struct Datum datrod)
{
	position temp;
	temp = (position)malloc(sizeof(osobe));

	int  f = 0;
	if (temp == NULL)
	{
		printf("nije se alociralo");
		return -1;
	}

	strcpy(temp->prezime, prezime);
	strcpy(temp->ime, ime);
	temp->datumrodenja.dan = datrod.dan;
	temp->datumrodenja.mjesec = datrod.mjesec;
	temp->datumrodenja.godina = datrod.godina;

	if (head->next != NULL)
	{
		while (head->next != NULL && f == 0)
		{
			if (head->next->datumrodenja.godina > temp->datumrodenja.godina)
			{
				f = 1;
			}
			else if (head->next->datumrodenja.godina == temp->datumrodenja.godina)
			{
				if (head->next->datumrodenja.mjesec > temp->datumrodenja.mjesec)
				{
					f = 1;
				}
				else if (head->next->datumrodenja.mjesec == temp->datumrodenja.mjesec)
				{
					if (head->next->datumrodenja.dan > temp->datumrodenja.dan)
					{
						f = 1;
					}
					else
					{
						head = head->next;
					}
				}
				else
				{
					head = head->next;
				}
			}
			else
			{
				head = head->next;
			}
		}
	}

	temp->next = head->next;
	head->next = temp;
	return 0;
}

int IspisListe(position head)
{
	head = head->next;

	while (head != NULL)
	{
		printf("%s %s\t %d.%d.%d\n", head->prezime, head->ime, head->datumrodenja.dan, head->datumrodenja.mjesec, head->datumrodenja.godina);
		head = head->next;
	}
	return 0;
}

int PronadiIme(position head, char unos[20])
{
	while (head->next != NULL)
	{
		head = head->next;
		if (_stricmp(unos, head->ime) == 0)
		{
			printf("%s %s %d.%d.%d\n", head->prezime, head->ime, head->datumrodenja.dan, head->datumrodenja.mjesec, head->datumrodenja.godina);
		}
	}


	return 0;
}