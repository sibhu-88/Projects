#include "header.h"

void menu1()
{

	printf("\n\t****STUDENT RECORD MENU****\n\n");
	printf("\t  a/A : Add New Record\n");
	printf("\t  d/D : Delete A Record\n");
	printf("\t  s/S : Show The List\n");
	printf("\t  m/M : Modify A Record\n");
	printf("\t  v/V : Save\n");
	printf("\t  e/E : Exit\n");
	printf("\t  t/T : Sort The List\n");
	printf("\t  l/L : Delete All The Records\n");
	printf("\t  r/R : Reverse The List\n\n");
	printf("\t  Enter Your Choice : ");
}

void menu2()
{
	printf("\t  R/r : Enter Roll To Delete\n");
	printf("\t  N/n : Enter Name To Delete\n");
	printf("\t  Enter : ");
}

void menu3()
{
	printf("\t  Enter Which Record To Search Fo Nodification\n");
	printf("\t  R/r : To Search A RollNo\n");
	printf("\t  N/n : To Search A Name\n");
	printf("\t  P/P : To Search A percentage\n");
	printf("\t  Enter : ");
}

void menu4()
{
	printf("\t  S/s : Save And Exit\n");
	printf("\t  E/e : Exit Without Saving\n");
	printf("\t  Enter : ");
}

void menu5()
{
	printf("\t  N/n : Sort With Name\n");
	printf("\t  P/p : Sort With Percentage\n");
	printf("\t  Enter : ");
}

int main()
{
	char op;
	SDB *hptr = 0;
	Read_records_from_file(&hptr);
	while (1)
	{
		system("clear");
		menu1();
		scanf(" %c", &op);

		op = tolower(op);
		switch (op)
		{
		case 'a':
			Add_new_record(&hptr);
			break;
		case 'd':
			Delete_record(&hptr);
			break;
		case 's':
			Show_list(hptr);
			break;
		case 'm':
			Modify_record(&hptr);
			break;
		case 'v':
			Save_record(hptr);
			break;
		case 'e':
			Exit(hptr);
			break;
		case 't':
			Sort_list(hptr);
			break;
		case 'l':
			Delete_all_record(&hptr);
			break;
		case 'r':
			Reverse_list(hptr);
			break;
		default:
			printf("Invalid option.");
		}
		sleep(1);
	}
}

void Read_records_from_file(SDB **ptr)
{
	FILE *file = fopen("student.xls", "r");
	if (file == NULL)
	{
		*ptr = NULL;
		return;
	}

	char line[256];
	fgets(line, sizeof(line), file);

	while (fgets(line, sizeof(line), file))
	{
		SDB *temp = (SDB *)malloc(sizeof(SDB));
		char name[50];

		sscanf(line, "%d\t%[^\t]\t%d", &temp->rollno, name, &temp->percentage);
		strcpy(temp->name, name);

		temp->next = NULL;

		if (*ptr == NULL)
		{
			*ptr = temp;
		}
		else
		{
			SDB *last = *ptr;
			while (last->next != NULL)
				last = last->next;
			last->next = temp;
		}
	}

	fclose(file);
	sleep(1);
}

int count(SDB *ptr)
{
	int count = 0;

	while (ptr != 0)
	{
		ptr = ptr->next;
		count++;
	}
	return count;
}

void Exit(SDB *ptr)
{
	char op;
	menu4();
	scanf(" %c", &op);
	op = tolower(op);
	switch (op)
	{
	case 's':
		Save_record(ptr);
		break;
	case 'c':
		break;
	}
	printf("Exit From the Student DataBase\n");
	exit(0);
}
