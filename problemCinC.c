#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h>
char allHobby[20][30];
int total_numberof_hobby=0;
char allDepartments[10][10];
int total_numberof_department=0;
int currentId=0;
struct Student
{
    char name[30];
    char ID[15];
    char hobbies[100];
    char department[10];
};

struct Student allStudents[1000];
int total_numberof_student=0;

void taking_all_hobby()
{
    FILE *fp1=fopen("hobby.txt","r");

    char test[30];
    total_numberof_hobby=0;
    while(fscanf(fp1,"%[^\n]",test)!=EOF)
    {
        char spaceR;
        fscanf(fp1,"%c",&spaceR);
        strcpy(allHobby[total_numberof_hobby],test);
        total_numberof_hobby++;
    }
    fclose(fp1);
}

void displayAllHobby()
{
    printf("all Hobbies : \n");
    for(int i=0; i<total_numberof_hobby; i++)
    {
        printf("%d : %s\n",i+1,allHobby[i]);
    }
}

void taking_all_departments()
{
    FILE *fp1=fopen("department.txt","r");

    char test[30];
    total_numberof_department=0;
    while(fscanf(fp1,"%[^\n]",test)!=EOF)
    {
        char spaceR;
        fscanf(fp1,"%c",&spaceR);
        strcpy(allDepartments[total_numberof_department],test);
        total_numberof_department++;
    }
    fclose(fp1);
}

void displayAllDepartment()
{
    printf("all Departments : \n");
    for(int i=0; i<total_numberof_department; i++)
    {
        printf("%d %s\n",i+1,allDepartments[i]);
    }
}


void taking_all_students()
{
    FILE *fp1=fopen("studentInfo.txt","r");

    char test[30];
    total_numberof_student=0;
    while(fscanf(fp1,"%[^\n]",test)!=EOF)
    {
        char spaceR;
        fscanf(fp1,"%c",&spaceR);

        strcpy(allStudents[total_numberof_student].ID,test);

        fscanf(fp1,"%[^\n]",allStudents[total_numberof_student].name);
        fscanf(fp1,"%c",&spaceR);

        fscanf(fp1,"%[^\n]",allStudents[total_numberof_student].department);
        fscanf(fp1,"%c",&spaceR);

        fscanf(fp1,"%[^\n]",allStudents[total_numberof_student].hobbies);
        fscanf(fp1,"%c",&spaceR);
        fscanf(fp1,"%c",&spaceR);
        total_numberof_student++;
    }
    fclose(fp1);

}

void displayAllStudents()
{
    printf("ID         Name                 Department      Hobbies\n");
    for(int i=0; i<total_numberof_student; i++)
    {
        printf("%-10s %-20s %-15s %-20s\n",allStudents[i].ID,allStudents[i].name,allStudents[i].department,allStudents[i].hobbies);
    }
}




int getCurrentId()
{
    FILE *fp1=fopen("currentId.txt","r");

    int id;
    fscanf(fp1,"%d",&id);
    // printf("current id : %d\n",id);
    fclose(fp1);
    return id;

}




void DisplayMenu()
{
    // system("cls");
    printf("======================== Student Information Manegement System ========================\n");
    printf("----------------------------Main Menu --------------------------------------------------\n");
    printf("1. Enter Student Information \n");
    printf("2. Update Student Information\n");
    printf("3. Display all Student information\n");
    printf("4. To exit from the system.\n");
}
void UpdateStudentInfoTable()
{

    FILE *fp1=fopen("studentInfo.txt","w");

    for(int i=0; i<total_numberof_student; i++)
    {
        fprintf(fp1,"%s\n%s\n%s\n%s\n",allStudents[i].ID,allStudents[i].name,allStudents[i].department,allStudents[i].hobbies);
        if(i!=total_numberof_student-1)fprintf(fp1,"\n");
    }
    fclose(fp1);
}

void EnterStudentInfo()
{
    printf("Enter the name of the student : ");
    char name[30];
    scanf("%[^\n]",name);
    char newLine;
    scanf("%c",&newLine);
    struct Student newStudent;
    strcpy(newStudent.name,name);
    printf("Enter a valid Department (1/2 or 3 etc..): ");
    while(1)
    {
        displayAllDepartment();
        int key;
        scanf("%d",&key);
        char newLine;
        scanf("%c",&newLine);
        if(key>total_numberof_department || key<=0)
        {
            // system("cls");
            printf("Please Enter a valid Department key .");
            continue;
        }
        strcpy(newStudent.department,allDepartments[key-1]);
        break;
    }

    int totalHobby;
    printf("please Enter the total Number of Hobbies : ");
    scanf("%d",&totalHobby);

    scanf("%c",&newLine);
    // int currentHobby=0;
    char currentHobbies[101];
    for(int i=0; i<totalHobby; i++)
    {


        printf("Enter a valid %d no Hobby (1/2 or 3 etc..): ",i+1);
        while(1)
        {
            displayAllHobby();
            int key;
            scanf("%d",&key);

            char newLine;
            scanf("%c",&newLine);
            if(key>total_numberof_hobby || key<=0)
            {
                // system("cls");
                printf("Please Enter a valid hobby key .");
                continue;
            }
            if(i==0)
                strcpy(currentHobbies,allHobby[key-1]);
            else
            {
                strcat(currentHobbies,",");
                strcat(currentHobbies,allHobby[key-1]);
            }
            break;
        }
    }


    strcpy(newStudent.hobbies,currentHobbies);

    char curId[100]="BDCOM";
    char ext='0'+currentId;
    curId[5]=ext;
    strcpy(newStudent.ID,curId);


    printf("The current student is : ");
    printf("%-10s %-20s %-15s %-20s\n",newStudent.ID,newStudent.name,newStudent.department,newStudent.hobbies);


    strcpy(allStudents[total_numberof_student].ID,newStudent.ID);
    strcpy(allStudents[total_numberof_student].name,newStudent.name);
    strcpy(allStudents[total_numberof_student].department,newStudent.department);
    strcpy(allStudents[total_numberof_student].hobbies,newStudent.hobbies);
    total_numberof_student++;

    currentId++;

    FILE *fp1=fopen("currentId.txt","w");
    fprintf(fp1,"%d",currentId);
    fclose(fp1);

    UpdateStudentInfoTable();



}

void displayUpdateMenu()
{
    printf("======================== Student Information Manegement System ========================\n");
    printf("----------------------------Update Student Information Menu ---------------------------\n");
    printf("1. update Hobby \n");
    printf("2. Update Department\n");


}
void allStudentsToUpdate()
{
    printf("Please select the student id from the left : \n");
    for(int i=0; i<total_numberof_student; i++)
    {
        printf("%d : %-10s %-20s %-15s %-20s\n",i+1,allStudents[i].ID,allStudents[i].name,allStudents[i].department,allStudents[i].hobbies);
    }
}

void updateHobby()
{
    while(1)
    {
        allStudentsToUpdate();
        int theId;
        scanf("%d",&theId);
        char newLine;
        scanf("%c",&newLine);

        if(theId>total_numberof_student || theId<=0)
        {
            printf("please a valid student no.\n");
            continue;
        }

        int totalHobby;
        printf("please Enter the total Number of Hobbies : ");
        scanf("%d",&totalHobby);

        scanf("%c",&newLine);
        // int currentHobby=0;
        char currentHobbies[101];
        for(int i=0; i<totalHobby; i++)
        {


            printf("Enter a valid %d no Hobby (1/2 or 3 etc..): ",i+1);
            while(1)
            {
                displayAllHobby();
                int key;
                scanf("%d",&key);

                char newLine;
                scanf("%c",&newLine);
                if(key>total_numberof_hobby || key<=0)
                {
                    // system("cls");
                    printf("Please Enter a valid hobby key .");
                    continue;
                }
                if(i==0)
                    strcpy(currentHobbies,allHobby[key-1]);
                else
                {
                    strcat(currentHobbies,",");
                    strcat(currentHobbies,allHobby[key-1]);
                }
                break;
            }
        }

        strcpy(allStudents[theId-1].hobbies,currentHobbies);
        break;

    }

    UpdateStudentInfoTable();

}

void updateDepartment()
{
    while(1)
    {
        allStudentsToUpdate();
        int theId;
        scanf("%d",&theId);
        char newLine;
        scanf("%c",&newLine);

        if(theId>total_numberof_student || theId<=0)
        {
            printf("please a valid student no.\n");
            continue;
        }

        printf("Enter a valid Department (1/2 or 3 etc..): ");
        while(1)
        {
            displayAllDepartment();
            int key;
            scanf("%d",&key);
            char newLine;
            scanf("%c",&newLine);
            if(key>total_numberof_department || key<=0)
            {
                // system("cls");
                printf("Please Enter a valid Department key .");
                continue;
            }

            printf("Updating student no : %d\n",key);
            strcpy(allStudents[theId-1].department,allDepartments[key-1]);
            //strcpy(newStudent.department,allDepartments[key-1]);
            break;
        }

        // strcpy(allStudents[theId].hobbies,currentHobbies);
        break;

    }

    UpdateStudentInfoTable();

}


void updateStudnetInfoMenu()
{


    while(1)
    {
        displayUpdateMenu();
        int option;
        scanf("%d",&option);
        char newLine;
        scanf("%c",&newLine);

        if(option==1)
        {
            updateHobby();
            break;
        }
        else if(option==2)
        {
            updateDepartment();
            break;
        }
        else
        {
            printf("Please Enter a valid key!\n");
        }
    }


}
void MainOperation()
{
    taking_all_students();
    //displayAllStudents();
    while(1)
    {
        //system("cls");
        DisplayMenu();
        int option;
        scanf("%d",&option);
        char newLine;
        scanf("%c",&newLine);

        if(option==1)
        {
            EnterStudentInfo();
        }
        else if(option==2)
        {
            updateStudnetInfoMenu();
        }
        else if(option==3)
        {
            displayAllStudents();
        }
        else if(option==4)
            break;
        else
        {
            system("cls");
            printf("Please Enter a valid key!\n");

        }


    }
}

int main()
{
//    FILE *fp1=fopen("studentInfo.txt","r");
//    fclose(fp1);
    taking_all_hobby();
    //displayAllHobby();
    taking_all_departments();
    //displayAllDepartment();
    currentId=getCurrentId();

    MainOperation();


    return 0;

}
