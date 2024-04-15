/* students.c */
/* Author: {ввести вместо скобок свои имя и фамилию} */
/* lab4_zadacha2 */

#include <sqlite3.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h> 
#include "students.h"

#define TRUE 1
#define FALSE 0

// Insert new records into an existing table
void insertNewRecord(sqlite3 *db)
{
	char *err_msg = 0;

        printf("1. Insers values to the students table\n");
        printf("2. Insert values to the subjects table\n"); 

	int choice = 0;
        scanf("%d", &choice);

        char sql[1000] = "INSERT INTO ";
        char str[100];
	
	switch(choice)
	{
	case 1: 
	  strcat(sql,
	  "students(FirstName,LastName,Group_id,height,weight,age) 
	  VALUES("); 
	  printf("Enter FirstName\n");
          strcat(sql,"'");
          scanf("%s", str);
	  strcat(sql, str);
	  strcat(sql, "', '"); 
	  printf("Enter last name\n"); 
	  scanf("%s", str);
	  strcat(sql, str);
	  strcat(sql, "', "); 
	  printf("Enter group number\n"); 
	  scanf("%s", str);
	  strcat(sql, str);
	  strcat(sql, ", "); 
	  printf("Enter height\n"); 
	  scanf("%s", str);
	  strcat(sql, str);
	  strcat(sql, ", "); 
	  printf("Enter weight\n"); 
	  scanf("%s", str);
	  strcat(sql, str); 
	  strcat(sql, ", "); 
	  printf("Enter age\n"); 
	  scanf("%s", str); 
	  strcat(sql, str); 
	  strcat(sql, ");"); 
	  break;
	case 2:
	  strcat(sql, "subjects(Title) VALUES("); 
	  printf("Enter subject name\n"); 
	  strcat(sql, "'");
	  scanf("%s", str); 
	  strcat(sql, str); 
	  strcat(sql, "');"); 
	  break;
	default:
	  printf("No option selected\n");
    }
 int rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

 if (rc != SQLITE_OK ) 
      {
	fprintf(stderr, "SQL error: %s\n", err_msg); 
	sqlite3_free(err_msg);
	return;
      } 	
}

// Delete records from an existing table
void deleteRecord(sqlite3 *db)
{
	char *err_msg = 0;

	printf("1. Delete values from the students table\n");
	printf("2. Delete values from the marks table\n");

    	int choice = 0;
    	scanf("%d", &choice);
	char sql[1000] = "DELETE from ";
	char str[100];

	int option = 0;
	switch(choice) 
	{
	   case 1:
		strcat(sql, "students where "); 
		printf("1. Delete by id\n"); 
		printf("2. Delete by Last Name\n"); 
		scanf("%d", &option);
		if (option == 1)
		{
			printf("Enter id\n"); 
			scanf("%s", str); 
			strcat(sql, "Student_id="); 
			strcat(sql, str);
		}
		else if (option == 2) 
		{
			printf("Enter Last Name\n"); 
			strcat(sql, "LastName='"); 
			scanf("%s", str); 
			strcat(sql, str); 
			strcat(sql, "'");
		}
		strcat(sql, ";"); 
		break;
	     case 2:	
		strcat(sql, "marks where "); 
		printf("1. Delete by Student id\n"); 
		printf("2. Delete by Subject id\n"); 
		scanf("%d", &option);
		if (option == 1)
	        {
			printf("Enter Student id\n"); 
			scanf("%s", str);
 			strcat(sql, "Student_id=");
                	strcat(sql, str);
                }
		else if (option == 2) 
		{
		printf("Enter Subject Id\n");
                scanf("%s", str);
                strcat(sql, "Subject_id=");
                strcat(sql, str);
		}
		strcat(sql, ";"); 
		break;
		default:
		printf("No option selected\n");
    		}
 int rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
if (rc != SQLITE_OK ) {
fprintf(stderr, "SQL error: %s\n", err_msg); sqlite3_free(err_msg);
return;
} }
// Print Selected records
void PrintSelect(sqlite3_stmt *res, int count)
{
while(TRUE) {
        int step = sqlite3_step(res);
if (step == SQLITE_ROW) {
for(int i = 0; i < count; i++) {
if (i == 7) {continue; }
                printf("%s ", sqlite3_column_text(res, i));
            }
printf("\n"); }
else
{
break;
} }
}
// Select records from an existing table
void selectRecords(sqlite3 *db)
{
sqlite3_stmt *res;
printf("1. Select values from the students table\n");
printf("2. Select values from the subjects table\n"); int choice = 0;
    scanf("%d", &choice);
    char sql[1000] = "SELECT * from ";
    char str[100];
    int option = 0;
int rc = 0;
switch(choice) {
case 1:
strcat(sql, "students");
printf("1. Select all table\n");
printf("2. Select records by id\n"); printf("3. Select records by last 
name\n"); scanf("%d", &option);
switch (option) { case 1:
        rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
if (rc == SQLITE_OK) {
            int idx = sqlite3_bind_parameter_index(res,
            int value = atoi(str);
            sqlite3_bind_int(res, idx, value);
        }
else
{
fprintf(stderr, "Failed to execute statement: %s\
n", sqlite3_errmsg(db)); }
"@id");
PrintSelect(res, 7); sqlite3_finalize(res); break;
case 2:
printf("Enter Student id\n");
scanf("%s", str);
strcat(sql, " where Student_id = @id");
rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
if (rc == SQLITE_OK) {
        int idx = sqlite3_bind_parameter_index(res,
        int value = atoi(str);
        sqlite3_bind_int(res, idx, value);
    }
else
{
fprintf(stderr, "Failed to execute statement: %s\
n", sqlite3_errmsg(db)); }
PrintSelect(res, 7); 20
"@lname");
NULL);
    sqlite3_finalize(res);
break; case 3:
printf("Enter last name\n");
scanf("%s", str);
strcat(sql, " where LastName like @lname"); rc = sqlite3_prepare_v2(db, 
sql, -1, &res, 0);
if (rc == SQLITE_OK) {
        int idx = sqlite3_bind_parameter_index(res,
        sqlite3_bind_text(res, idx, str, strlen(str),
}
else
{
fprintf(stderr, "Failed to execute statement: %s\
n", sqlite3_errmsg(db)); }
PrintSelect(res, 7); sqlite3_finalize(res); break;
default:
printf("No option selected\n"); break;
}
break; case 2:
strcat(sql, "subjects"); printf("1. Select all table\n"); scanf("%d", 
&option);
switch (option) {
case 1:
rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
if (rc == SQLITE_OK) {
int idx = sqlite3_bind_parameter_index(res,"@id");
int value = atoi(str);
                        sqlite3_bind_int(res, idx, value);
                    }
else
{
fprintf(stderr, "Failed to execute statement: %s\
n", sqlite3_errmsg(db)); }
PrintSelect(res, 2); sqlite3_finalize(res); break;
default:
printf("No option selected\n"); break;
}
break; default:
printf("No option selected\n");
} 
}	
