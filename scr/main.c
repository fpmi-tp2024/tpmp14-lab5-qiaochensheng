/* main.c */
/* Author: {вместо скобок ввести свои имя и фамилию} */
/* lab4_zadacha2 */
#include <sqlite3.h> #include <stdio.h> #include <stdlib.h> #include 
"students.h"
#define TRUE 1
#define FALSE 0
int main(int argc, const char * argv[]) {
sqlite3 *db;
int rc = sqlite3_open("src/students.db", &db); if (rc != SQLITE_OK)
{
fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
return 1; }
while(TRUE) {
printf("Menu to manage the database (src/students.db):\n"); printf("1. 
SELECT records\n");
printf("2. INSERT records\n");
printf("3. DELETE records\n");
printf("4. Exit\n");
25
int choice = 0;
        scanf("%d", &choice);
        int exitBool = 0;
        int option = 0;
switch(choice) {
case 1: selectRecords(db); break;
case 2: insertNewRecord(db); break;
case 3: deleteRecord(db); break;
case 4:
exitBool = 1;
break; default:
printf("No option which was selected\n");
}
if(exitBool == TRUE) {
break; }
}
    sqlite3_close(db);
return 0; }
