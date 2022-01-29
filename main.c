#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int addCourse(){
    char courseno[10];
    char coursename[20];
    char grade[5];
    int year;
    int sem;
    printf("Enter name of Course: ");
    scanf("%s",&coursename);
    printf("Enter Course Number: ");
    scanf("%s", &courseno);
    printf("Enter Year of Study: ");
    scanf("%d", &year);
    printf("Enter Semester Number (1,2): ");
    scanf("%d", &sem);
    printf("Enter Grade of Course:  ");
    scanf("%s", &grade);

    FILE *fptr;
    fptr = fopen("./coursename.txt","a");
    if(fptr == NULL)
   {
      printf("Error!");   
      exit(1);             
   }
    fprintf(fptr,"%s\n",coursename);
    fclose(fptr);
    

    fptr = fopen("./courseno.txt","a");
    if(fptr == NULL)
   {
      printf("Error!");   
      exit(1);             
   }
    fprintf(fptr,"%s\n",courseno);
    fclose(fptr);


    fptr = fopen("./year_sem.txt","a");
    if(fptr == NULL)
   {
      printf("Error!");   
      exit(1);             
   }
    fprintf(fptr,"%d",year);
    fprintf(fptr,"%d\n",sem);
    fclose(fptr);

    fptr = fopen("./grades.txt","a");
    if(fptr == NULL)
   {
      printf("Error!");   
      exit(1);             
   }
    fprintf(fptr,"%s\n",grade);
    fclose(fptr);

    return 0;
}
char _grade(char courseNo[]){
    char search[10];
    char grade[5];
    FILE *fptr;
    int lineno =0;
    int flag=0;
    fptr = fopen("./courseno.txt","r");
    while (!feof(fptr)) {
        lineno++;
        fscanf(fptr,"%s",&search);
        if(strcmp(search,courseNo) == 0){
            printf("Match Found\n");
            flag=1;
            break;
        }
    }
    if(flag==0)
        printf("No Match Found\n");
    fclose(fptr);

    fptr = fopen("./grades.txt","r");
        while (--lineno>=0) {
        fscanf(fptr,"%s",&grade);
    }
    
    fclose(fptr);
    printf("Your grade is %s\n\n",grade);
    // return grade;
    return grade[0];
}

char grade(){
    char courseno[10];
    printf("Enter Course Number: ");
    
    scanf("%s", &courseno);
    _grade(courseno);
    return '0';
}

float _calculate_GPA(int year,int sem){
    FILE *fptr;
    float gpa =0;
    int linenos[10];    //assuming at max 10 courses per semester
    fptr = fopen("./year_sem.txt","r");
    int lineno=0;
    int search;
    int flag=0;
    int count =0;
    for(int i=0;i<10;i++)
        linenos[i] =0;
    while (!feof(fptr)) {
        lineno++;
        fscanf(fptr,"%d",&search);
        if(search%10==sem && search/10==year){
            // printf("Year/Sem Match Found\n");
            linenos[count++] = lineno; 
            // printf("LINE NOS: %d\n",lineno);
            flag=1;
        }
    }
     if(flag==0){
        printf("No Year/Sem Match Found\n");
        return 0;
     }
    fclose(fptr);

    lineno =0;
    char search2[10];
    fptr = fopen("./grades.txt","r");
    char grades[10][5];
    while (!feof(fptr)) {
        lineno++;
        fscanf(fptr,"%s",&search2);
        for(int j =0;j<count;j++){
            if(lineno == linenos[j]){
                // printf("Year/Sem Match Found\n");
                strcpy(grades[j],search2);
                printf("\nCourse %d : %s \n",j,grades[j]);
                // break;
            }
        }
    }
    int clearcourses=0;
    for(int p=0;p<count;p++){
        if(strcmp(grades[p],"A")==0)
            gpa+=10;
        else if(strcmp(grades[p],"A-")==0)
            gpa+=9;
        else if(strcmp(grades[p],"B")==0)
            gpa+=8;
        else if(strcmp(grades[p],"B-")==0)
            gpa+=7;
        else if(strcmp(grades[p],"C")==0)
            gpa+=6;
        else if(strcmp(grades[p],"C-")==0)
            gpa+=5;
        else if(strcmp(grades[p],"D")==0)
            gpa+=4;
        else if(strcmp(grades[p],"CLR")==0)
            clearcourses++;
    }
    // printf("G1%d",gpa);
    gpa = gpa/(count-clearcourses);
    // printf("G2%d",gpa);
    printf("GPA: %f\n\n",gpa);
    return gpa;
}

float calculate_GPA(){
    int year;
    int sem;
    printf("Enter Year: ");
    scanf("%d", &year);
    printf("Enter Semester: ");

    scanf("%d", &sem);
    return _calculate_GPA(year,sem);
}

float calculate_CGPA(){
    return calculate_GPA();
}

int main(){
    int flag=0;
    while(flag==0){
        int choice = 0;
        printf("######Welcome to ERP#####\n\n");
        printf("1. Add a course\n");
        printf("2. View grades in a course\n");
        printf("3. View Semester GPA\n");
        printf("4. View Cumulative GPA\n");
        printf("5. Logout\n");
        scanf("%d",&choice);
        switch (choice)
        {
        case 1:
            addCourse();
            break;
        case 2:
            grade();
            break;
        case 3:
            calculate_GPA();
            break;
        case 4:
            calculate_CGPA();
            break;
        case 5:
            flag=1;
            break;
        default:
            printf("Invalid Input Selected, Choose Again\n\n");
            break;
        }
    }
    return 0;
}
