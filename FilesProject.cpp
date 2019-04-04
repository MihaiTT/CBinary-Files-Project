// C Project where the user can add information to a file based on the following layout,and do certain
// operations with that information, like writing it to a different file, estimate the average based on
// a certaint criterium, printing to the standard output etc
// STUDENT:
// ID		NAME		SURNAME		GROUP		CLASS		YEAR		GRADES

//TODO: ADD DATA VALIDATION
//TODO: ADD GUI
#include <stdio.h>
#include <string.h>
typedef struct {				//we define the way user data is stored
	int id;
	char name[20];
	char surname[20];
	char s_class[5];			//couln't name "class"
	int group;
	int year;
	int grades[5];

} Student ;
void creation(char NameOfFile[])										//we create the binary file based on the user input
{
	printf("\n");
	printf("The name of the file is : %s\n",NameOfFile);												// !TODO : add data validation
	printf("\n");
	FILE *f;
	int i;
	Student s1;
	f = fopen(NameOfFile, "wb");
	printf("Please enter the ID of the student. The id can only be a NUMBER, without any other characters added. \n");
	printf("Example: 5 ; 4 ; 17 \n");
	printf("\n");
	scanf("%d", &s1.id,sizeof(s1.id));
	fflush(stdin);
	while (!feof(stdin))					//We add data until the user presses "CTRL+z + enter" 3 times in a row
	{
		printf("\n");
		printf("Adding data...\n");
		printf("To stop, press 'CTRL + z + enter' 3 times in a row\n");
		printf("\n");
		printf("Please enter the --NAME-- of the student. Please make the first letter uppercase,and the rest of the name lowercase.\n");
		printf("Example: Name ; Otti ; Nume \n");
		printf("\n");
		scanf("%s", &s1.name,sizeof(s1.name));
		printf("\n");
		printf("Please enter the --SURNAME-- of the student. Please make the FIRST LETTER UPPERCASE, and the rest of the surname lowercase.\n");
		printf("Example: Surname ; Mihaita ; Prenume \n");
		printf("\n");
		scanf("%s", &s1.surname, sizeof(s1.surname));
		printf("\n");
		printf("Please enter the --GROUP-- of the student. The group of the student can only be a NUMBER, without any other characters added.\n");
		printf("Example: 1008 ; 3 ; 500 ; 17 \n");
		printf("\n");
		scanf("%d", &s1.group, sizeof(s1.group));
		printf("\n");
		printf("Please enter the --CLASS-- of the student. The class of the student can only be an UPPERCASE LETTER, without any other characters added.\n");
		printf("Example: A ; B ; Z \n");
		printf("\n");
		scanf("%s", &s1.s_class, sizeof(s1.s_class));
		printf("\n");
		printf("Please enter the --YEAR-- of the student. The year of the student can only be a NUMBER.\n");
		printf("Example: 1 ; 2 ; 3 \n");
		printf("\n");
		scanf("%d", &s1.year, sizeof(s1.year));
		printf("\n");
		printf("Please enter the --GRADES-- of the student. The grades of the student can only be NUMBERS and should range from 1 to 10\n");
		printf("Example: 10 ; 5 ; 4 \n");	
		printf("\n");														//let's say every student can have 5 grades
		for (i = 0; i < 5; i++)
		{
			printf("Please enter grade number %d\n", i + 1);		//since i starts at 0, we ask for grade i+1
			printf("\n");
			scanf("%d", &s1.grades[i]);
			printf("\n");
		}
		printf("All data fields for this student are completed. To stop, press 'CTRL + z + enter' 3 times in a row\n");
		printf("\n");
		fwrite(&s1, sizeof(s1), 1, f);
		printf("Please enter the ID of the student. The id can only be a NUMBER, without any other characters added. \n");
		printf("Example: 5 ; 4 ; 17 \n");
		printf("\n");
		scanf("%d", &s1.id);
		// we go back to the start of the while if the user didnt press CTRL+z+enter 3 times in a row


	}
	fclose(f);			// we are done with the file in this function,so we close it
}
void screen_display(char NameOfFile[])					//printing the data to the screen
{
	FILE *f;
	int i;
	Student s1;
	f = fopen(NameOfFile, "rb");
	if (f)
	{
		fseek(f, 0, 0);
		printf("Displaying the content of the file...\n");
		printf("=================================================== DATA ============================================================\n");
		printf("     ID     |    NAME     |     SURNAME     |     CLASS     |     GROUP     |     YEAR     |     GRADES     \n");
		fread(&s1, sizeof(Student), 1, f);
		while (!feof(f))
		{
			printf("%12d|%13s|%17s|%15s|%15d|%14d|", s1.id, s1.name, s1.surname, s1.s_class, s1.group, s1.year);		//formating the output by trial and error mostly
			for (i = 0; i < 5 ; i++)
				printf("%3d; ",s1.grades[i]);
			printf("\n");
			fread(&s1, sizeof(Student), 1, f);
		}
	}
	printf("\n");
	fclose(f);

}
void sort_by_year(char NameOfFile[])									//sorting data by year
{
	FILE *f;
	f = fopen(NameOfFile, "rb+");
	Student s1, s2;
	int n, i, j;
	if (f) {
		fseek(f, 0, 2);
		n = ftell(f) / sizeof(s1);
		for (i = 0; i < n - 1; i++)
			for (j = i; j < n; j++)
			{
				fseek(f, i * sizeof(s1), 0);
				fread(&s1, sizeof(s1), 1, f);
				fseek(f, j * sizeof(s2), 0);
				fread(&s2, sizeof(s2), 1, f);
				if (s1.year > s2.year)
				{
					fseek(f, i * sizeof(s2), 0);
					fwrite(&s2, sizeof(s2), 1, f);
					fseek(f, j * sizeof(s1), 0);
					fwrite(&s1, sizeof(s1), 1, f);
				}
			}
		fclose(f);
		printf("Data was sorted by year.\n");
		printf("\n");
	}
}
void sort_by_group(char NameOfFile[])							//sorting the data by group
{
	FILE *f;
	f = fopen(NameOfFile, "rb+");
	Student s1, s2;
	int n, i, j;
	if (f) {
		fseek(f, 0, 2);
		n = ftell(f) / sizeof(s1);
		for (i = 0; i < n - 1; i++)
			for (j = i; j < n; j++)
			{
				fseek(f, i * sizeof(s1), 0);
				fread(&s1, sizeof(s1), 1, f);
				fseek(f, j * sizeof(s2), 0);
				fread(&s2, sizeof(s2), 1, f);
				if (s1.group > s2.group)
				{
					fseek(f, i * sizeof(s2), 0);
					fwrite(&s2, sizeof(s2), 1, f);
					fseek(f, j * sizeof(s1), 0);
					fwrite(&s1, sizeof(s1), 1, f);
				}
			}
		fclose(f);
	}
	printf("Data was sorted by group.\n");
	printf("\n");
}
void sort_by_fullname(char NameOfFile[])			//we need to concatenate the Name with the Surname in order to sort via Full Name
{
	FILE *f;
	f = fopen(NameOfFile, "rb+");
	Student s1, s2;
	int n, i, j;
	char t[50], fullname1[80], y[50], fullname2[80];
	if (f) {
		fseek(f, 0, 2);
		n = ftell(f) / sizeof(s1);
		for (i = 0; i < n - 1; i++)
			for (j = i; j < n; j++)
			{
				fseek(f, i * sizeof(s1), 0);
				fread(&s1, sizeof(s1), 1, f);
				fseek(f, j * sizeof(s2), 0);
				fread(&s2, sizeof(s2), 1, f);
				strcpy(t, s1.surname);
				strcpy(fullname1, s1.name);
				strcat(fullname1, t);		//we obtained the full name for the first student
				strcpy(y, s2.surname);
				strcpy(fullname2, s2.name);
				strcat(fullname2, y);     //we obtained the full name for the second student
				if (strcmp(fullname1, fullname2) > 0)		//strcmp(s1,s2) returns a value greater than 0 if s1 has a greater value than s2
				{
					fseek(f, i * sizeof(s2), 0);
					fwrite(&s2, sizeof(s2), 1, f);
					fseek(f, j * sizeof(s1), 0);
					fwrite(&s1, sizeof(s1), 1, f);
				}
			}

	}
	printf("Data was sorted by name.\n");
	printf("\n");
	fclose(f);
}
void sort_by_id(char NameOfFile[])							//sorting the data by id
{
	FILE *f;
	f = fopen(NameOfFile, "rb+");
	Student s1, s2;
	int n, i, j;
	if (f) {
		fseek(f, 0, 2);
		n = ftell(f) / sizeof(s1);
		for (i = 0; i < n - 1; i++)
			for (j = i; j < n; j++)
			{
				fseek(f, i * sizeof(s1), 0);
				fread(&s1, sizeof(s1), 1, f);
				fseek(f, j * sizeof(s2), 0);
				fread(&s2, sizeof(s2), 1, f);
				if (s1.id > s2.id)
				{
					fseek(f, i * sizeof(s2), 0);
					fwrite(&s2, sizeof(s2), 1, f);
					fseek(f, j * sizeof(s1), 0);
					fwrite(&s1, sizeof(s1), 1, f);
				}
			}
		fclose(f);
	}
	printf("Data was sorted by id.\n");
	printf("\n");
}
void sort_by_class(char NameOfFile[])							//sorting the data by class name
{
	FILE *f;
	f = fopen(NameOfFile, "rb+");
	Student s1, s2;
	int n, i, j;
	if (f) {
		fseek(f, 0, 2);
		n = ftell(f) / sizeof(s1);
		for (i = 0; i < n - 1; i++)
			for (j = i; j < n; j++)
			{
				fseek(f, i * sizeof(s1), 0);
				fread(&s1, sizeof(s1), 1, f);
				fseek(f, j * sizeof(s2), 0);
				fread(&s2, sizeof(s2), 1, f);
				if (strcmp(s1.s_class,s2.s_class)>0)
				{
					fseek(f, i * sizeof(s2), 0);
					fwrite(&s2, sizeof(s2), 1, f);
					fseek(f, j * sizeof(s1), 0);
					fwrite(&s1, sizeof(s1), 1, f);
				}
				
			}
		fclose(f);
	}
	printf("Data was sorted by class name.\n");
	printf("\n");
}
void sort_by_grades(char NameOfFile[])							//sorting the data by grades, lowest to highest;
{																//we considider a student to have better grades than another student if the sum of the grades is higher
	FILE *f;
	f = fopen(NameOfFile, "rb+");
	Student s1, s2;
	int n, i, j,k,grades_sum[2];			//we create a grades_sum[] vector where grades_sum[0]=sum of s1 grades, grades_sum[1]=sum of s2 grades;
	if (f) {
		fseek(f, 0, 2);
		n = ftell(f) / sizeof(s1);
		for (i = 0; i < n - 1; i++)
			for (j = i; j < n; j++)
			{
				fseek(f, i * sizeof(s1), 0);
				fread(&s1, sizeof(s1), 1, f);
				fseek(f, j * sizeof(s2), 0);
				fread(&s2, sizeof(s2), 1, f);
				grades_sum[0] = 0; grades_sum[1] = 0;      //we make the sum of grades 0 at the start of each iteration
				for (k = 0; k < 5; k++)
				{
					grades_sum[0] = grades_sum[0] + s1.grades[k];
					grades_sum[1] = grades_sum[1] + s2.grades[k];
				}
				if (grades_sum[0]>grades_sum[1])
				{
					fseek(f, i * sizeof(s2), 0);
					fwrite(&s2, sizeof(s2), 1, f);
					fseek(f, j * sizeof(s1), 0);
					fwrite(&s1, sizeof(s1), 1, f);
				}

			}
		fclose(f);
	}
	printf("Data was sorted by grades.\n");
	printf("\n");
}
void display_by_id(char NameOfFile[])						//we display all the students that have a specific ID
{
	FILE *f;
	f = fopen(NameOfFile, "rb");
	Student s1;
	int search_id, i;
	printf("\n");
	printf("Please introduce the id you are searching for \n");
	printf("\n");
	scanf("%d", &search_id);
	printf("\n");
	int ok = 0;
	if (f)
	{
		fread(&s1, sizeof(s1), 1, f);
		while (!feof(f))
		{
			if (s1.id == search_id)
			{
				printf("     ID     |    NAME     |     SURNAME     |     CLASS     |     GROUP     |     YEAR     |     GRADES     \n");
				printf("%12d|%13s|%17s|%15s|%15d|%14d|", s1.id, s1.name, s1.surname, s1.s_class, s1.group, s1.year);		
				for (i = 0; i < 5; i++)
					printf("%3d; ", s1.grades[i]);
				printf("\n");
				ok = 1;
			}

			fread(&s1, sizeof(s1), 1, f);
		}
		fclose(f);
		printf("\n");
		if (ok == 0) { printf("There is no student with the id %d \n", search_id); printf("\n"); }
	}
}
void display_by_class(char NameOfFile[])						//we display all the students that have a specific class
{
	FILE *f;
	f = fopen(NameOfFile, "rb");
	Student s1;
	int  i;
	char search_class[5];
	printf("\n");
	printf("Please introduce the class you are searching for \n");
	printf("\n");
	scanf("%s", &search_class);
	printf("\n");
	int ok = 0;
	if (f)
	{
		fread(&s1, sizeof(s1), 1, f);
		while (!feof(f))
		{
			if (strcmp(s1.s_class,search_class)==0)
			{
				printf("     ID     |    NAME     |     SURNAME     |     CLASS     |     GROUP     |     YEAR     |     GRADES     \n");
				printf("%12d|%13s|%17s|%15s|%15d|%14d|", s1.id, s1.name, s1.surname, s1.s_class, s1.group, s1.year);
				for (i = 0; i < 5; i++)
					printf("%3d; ", s1.grades[i]);
				printf("\n");
				ok = 1;
			}

			fread(&s1, sizeof(s1), 1, f);
		}
		fclose(f);
		printf("\n");
		if (ok == 0) { printf("There is no student with the class %s \n", search_class); printf("\n"); }
	}
}
void display_by_group(char NameOfFile[])						//we display all the students that have a specific group
{
	FILE *f;
	f = fopen(NameOfFile, "rb");
	Student s1;
	int search_group, i;
	printf("\n");
	printf("Please introduce the group you are searching for \n");
	printf("\n");
	scanf("%d", &search_group);
	printf("\n");
	int ok = 0;
	if (f)
	{
		fread(&s1, sizeof(s1), 1, f);
		while (!feof(f))
		{
			if (s1.group == search_group)
			{
				printf("     ID     |    NAME     |     SURNAME     |     CLASS     |     GROUP     |     YEAR     |     GRADES     \n");
				printf("%12d|%13s|%17s|%15s|%15d|%14d|", s1.id, s1.name, s1.surname, s1.s_class, s1.group, s1.year);
				for (i = 0; i < 5; i++)
					printf("%3d; ", s1.grades[i]);
				printf("\n");
				ok = 1;
			}

			fread(&s1, sizeof(s1), 1, f);
		}
		fclose(f); printf("\n");
		if (ok == 0) { printf("There is no student with the group %d \n", search_group); printf("\n"); }
	}
}
void display_by_year(char NameOfFile[])						//we display all the students that have a specific year
{
	FILE *f;
	f = fopen(NameOfFile, "rb");
	Student s1;
	int search_year, i;
	printf("\n");
	printf("Please introduce the year you are searching for \n");
	printf("\n");
	scanf("%d", &search_year);
	printf("\n");
	int ok = 0;
	if (f)
	{
		fread(&s1, sizeof(s1), 1, f);
		while (!feof(f))
		{
			if (s1.year == search_year)
			{
				printf("     ID     |    NAME     |     SURNAME     |     CLASS     |     GROUP     |     YEAR     |     GRADES     \n");
				printf("%12d|%13s|%17s|%15s|%15d|%14d|", s1.id, s1.name, s1.surname, s1.s_class, s1.group, s1.year);
				for (i = 0; i < 5; i++)
					printf("%3d; ", s1.grades[i]);
				printf("\n");
				ok = 1;
			}

			fread(&s1, sizeof(s1), 1, f);
		}
		fclose(f); printf("\n");
		if (ok == 0) { printf("There is no student with the year %d \n", search_year); printf("\n"); }
	}
}
void display_by_name(char NameOfFile[])						//we display all the students that have a specific name (not to be confused with fullname,we have another function for that)
{
	FILE *f;
	f = fopen(NameOfFile, "rb");
	Student s1;
	int  i;
	char search_name[20];
	printf("\n");
	printf("Please introduce the name you are searching for \n");
	printf("\n");
	scanf("%s", &search_name);
	printf("\n");
	int ok = 0;
	if (f)
	{
		fread(&s1, sizeof(s1), 1, f);
		while (!feof(f))
		{
			if (strcmp(s1.name, search_name) == 0)
			{
				printf("     ID     |    NAME     |     SURNAME     |     CLASS     |     GROUP     |     YEAR     |     GRADES     \n");
				printf("%12d|%13s|%17s|%15s|%15d|%14d|", s1.id, s1.name, s1.surname, s1.s_class, s1.group, s1.year);
				for (i = 0; i < 5; i++)
					printf("%3d; ", s1.grades[i]);
				printf("\n");
				ok = 1;
			}

			fread(&s1, sizeof(s1), 1, f);
		}
		fclose(f); printf("\n");
		if (ok == 0) { printf("There is no student with the name %s \n", search_name); printf("\n"); }
	}
}
void display_by_surname(char NameOfFile[])						//we display all the students that have a specific surname (not to be confused with fullname,we have another function for that)
{
	FILE *f;
	f = fopen(NameOfFile, "rb");
	Student s1;
	int  i;
	char search_surname[20];
	printf("\n");
	printf("Please introduce the surname you are searching for \n");
	printf("\n");
	scanf("%s", &search_surname);
	printf("\n");
	int ok = 0;
	if (f)
	{
		fread(&s1, sizeof(s1), 1, f);
		while (!feof(f))
		{
			if (strcmp(s1.surname, search_surname) == 0)
			{
				printf("     ID     |    NAME     |     SURNAME     |     CLASS     |     GROUP     |     YEAR     |     GRADES     \n");
				printf("%12d|%13s|%17s|%15s|%15d|%14d|", s1.id, s1.name, s1.surname, s1.s_class, s1.group, s1.year);
				for (i = 0; i < 5; i++)
					printf("%3d; ", s1.grades[i]);
				printf("\n");
				ok = 1;
			}

			fread(&s1, sizeof(s1), 1, f);
		}
		fclose(f); printf("\n");
		if (ok == 0) { printf("There is no student with the surname %s \n", search_surname); printf("\n"); }
	}
}
void display_by_fullname(char NameOfFile[])						//we display all the students that have a specific fullname(by concatenating name+surname)
{
	FILE *f;
	f = fopen(NameOfFile, "rb");
	Student s1;
	int  i;
	char search_fullname[80],t[50],fullname[80];
	printf("\n");
	printf("Please introduce the full name of the student you are searching for, without white spaces \n");
	printf("Example: OttiMihaita ; NameSurname \n");
	printf("\n");
	scanf("%s", &search_fullname);
	printf("\n");
	int ok = 0;
	if (f)
	{
		fread(&s1, sizeof(s1), 1, f);
		while (!feof(f))
		{
			strcpy(t, s1.surname);
			strcpy(fullname, s1.name);
			strcat(fullname, t);
			if (strcmp(fullname, search_fullname) == 0)
			{
				printf("     ID     |    NAME     |     SURNAME     |     CLASS     |     GROUP     |     YEAR     |     GRADES     \n");
				printf("%12d|%13s|%17s|%15s|%15d|%14d|", s1.id, s1.name, s1.surname, s1.s_class, s1.group, s1.year);
				for (i = 0; i < 5; i++)
					printf("%3d; ", s1.grades[i]);
				printf("\n");
				ok = 1;
			}

			fread(&s1, sizeof(s1), 1, f);
		}
		fclose(f); printf("\n");
		if (ok == 0) { printf("There is no student with the full name %s \n", search_fullname); printf("\n"); }
	}
}
void display_in_text_file(char NameOfFile[])							//instead of displaying to the screen, we create a new file with the data content	
{
	FILE *f,*g;
	int i;
	Student s1;
	f = fopen(NameOfFile, "rb");
	g = fopen("data.txt", "w");
	if (f)
	{
		fseek(f, 0, 0);
		fprintf(g,"Displaying the content of the file...\n");
		printf("\n");   
		fprintf(g,"=================================================== DATA ============================================================\n");
		fprintf(g,"     ID     |    NAME     |     SURNAME     |     CLASS     |     GROUP     |     YEAR     |     GRADES     \n");
		fread(&s1, sizeof(Student), 1, f);
		while (!feof(f))
		{
			fprintf(g,"%12d|%13s|%17s|%15s|%15d|%14d|", s1.id, s1.name, s1.surname, s1.s_class, s1.group, s1.year);		//formating the output by trial and error mostly
			for (i = 0; i < 5; i++)
				fprintf(g,"%3d; ", s1.grades[i]);
			fprintf(g,"\n");
			fread(&s1, sizeof(Student), 1, f);
		}
	}
	fclose(f); fclose(g);
}
void choose_option(char NameOfFile[])				//tried to create an "interface" for the user to pick what he wants to do, so he doesn't have to re-run the program
													//or interact with the code, only with the cmd
{
	int main_option, display_option, sort_option;							//we create option variables for every function "type"
	printf("Please type the option of the function you want to execute.\n");
	printf("The option will be typed as a number, without any added characters. Example: 1\n");
	printf("\n");
	printf("0. Back/Stop. \n");
	printf("1. Create data (pick this option first if you don't have any students already added) \n");
	printf("2. Display data (pick for detailed options) \n");
	printf("3. Sort data (pick for detailed options) \n");
	printf("\n");
	scanf("%d", &main_option);
	printf("\n");
	while (main_option!=0)
	{
		
		if (main_option == 1) creation(NameOfFile);
		if (main_option == 2)
		{
			printf("Please type the option of the function you want to execute.\n");
			printf("The option will be typed as a number, without any added characters. Example: 1\n");
			printf("\n");
			printf("0. Back/Stop. \n");
			printf("1. Display all data on the screen \n");
			printf("2. Display all data in a text file \n");
			printf("3. Display students by id \n");
			printf("4. Display students by name \n");
			printf("5. Display students by surname \n");
			printf("6. Display students by full name \n");
			printf("7. Display students by class \n");
			printf("8. Display students by group \n");
			printf("\n");
			scanf("%d", &display_option);
			printf("\n");
			while (display_option!=0)
			{
				if (display_option == 1) screen_display(NameOfFile);
				if (display_option == 2) display_in_text_file(NameOfFile);
				if (display_option == 3) display_by_id(NameOfFile);
				if (display_option == 4) display_by_name(NameOfFile);
				if (display_option == 5) display_by_surname(NameOfFile);
				if (display_option == 6) display_by_fullname(NameOfFile);
				if (display_option == 7) display_by_class(NameOfFile);
				if (display_option == 8) display_by_group(NameOfFile);
				printf("Please type the option of the function you want to execute.\n");
				printf("The option will be typed as a number, without any added characters. Example: 1\n");
				printf("\n");
				printf("0. Back/Stop. \n");
				printf("1. Display all data on the screen \n");
				printf("2. Display all data in a text file \n");
				printf("3. Display students by id \n");
				printf("4. Display students by name \n");
				printf("5. Display students by surname \n");
				printf("6. Display students by full name \n");
				printf("7. Display students by class \n");
				printf("8. Display students by group \n");
				printf("\n");
				scanf("%d", &display_option);
				printf("\n");
			}
		}
		if (main_option == 3)
		{
			printf("Please type the option of the function you want to execute.\n");
			printf("The option will be typed as a number, without any added characters. Example: 1\n");
			printf("\n");
			printf("0. Back/Stop. \n");
			printf("1. Sort students by id \n");
			printf("2. Sort students by name \n");
			printf("3. Sort students by class \n");
			printf("4. Sort students by group \n");
			printf("5. Sort students by year \n");
			printf("6. Sort students by grades (worst to best) \n");
			printf("\n");
			scanf("%d", &sort_option);
			printf("\n");
			while (sort_option!=0)
			{
				if (sort_option == 1) sort_by_id(NameOfFile);
				if (sort_option == 2) sort_by_fullname(NameOfFile);
				if (sort_option == 3) sort_by_class(NameOfFile);
				if (sort_option == 4) sort_by_group(NameOfFile);
				if (sort_option == 5) sort_by_year(NameOfFile);
				if (sort_option == 6) sort_by_grades(NameOfFile);
				printf("Please type the option of the function you want to execute.\n");
				printf("The option will be typed as a number, without any added characters. Example: 1\n");
				printf("\n");
				printf("0. Back/Stop. \n");
				printf("1. Sort students by id \n");
				printf("2. Sort students by name \n");
				printf("3. Sort students by class \n");
				printf("4. Sort students by group \n");
				printf("5. Sort students by year \n");
				printf("6. Sort students by grades (worst to best) \n");
				printf("\n");
				scanf("%d", &sort_option);
				printf("\n");
			}
		}


		printf("Please type the option of the function you want to execute.\n");
		printf("The option will be typed as a number, without any added characters. Example: 1\n");
		printf("\n");
		printf("0. Back/Stop. \n");
		printf("1. Create data (pick this option first if you don't have any students already added): \n");
		printf("2. Display data (pick for detailed options) \n");
		printf("3. Sort data (pick for detailed options) \n");
		printf("\n");
		scanf("%d", &main_option);
		printf("\n");
	}
}
int main()
{
	char NameOfFile[20];
	strcpy(NameOfFile, "data.dat");
	choose_option(NameOfFile);
	return 0;
}
