#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 50

struct student {
    char id[20];
    char name[30];
    int marks[5];
};


int isValidID(char id[]) {
    for (int i = 0; id[i] != '\0'; i++) {  
        if (!isalnum(id[i]))
            return 0;
    }
    return 1;
}


int isValidName(char name[]) {
    for (int i = 0; name[i] != '\0'; i++) { 
        if (!isalpha(name[i]))           
            return 0;
    }
    return 1;
}


int isDuplicateID(struct student s[], int count, char id[]) {
    for (int i = 0; i < count; i++) {
        if (strcmp(s[i].id, id) == 0)
            return 1;
    }
    return 0;
}

int main() {
    FILE *fp;
    struct student s[MAX];
    int n, count = 0;

    fp = fopen("students.txt", "r");
    if (fp == NULL) {
        printf("FILE NOT FOUND\n");
        return 1;
    }

    fscanf(fp, "%d", &n);

    for (int i = 0; i < n; i++) {
        char id[20], name[30];
        int marks[5];
        int valid = 1;

        fscanf(fp, "%s %s", id, name);

        for (int j = 0; j < 5; j++) {
            fscanf(fp, "%d", &marks[j]);
        }

        if (!isValidID(id)) {
            printf("INVALID ID: %s\n", id);
            valid = 0;
        }

        if (!isValidName(name)) {
            printf("INVALID NAME: %s\n", name);
            valid = 0;
        }

        if (isDuplicateID(s, count, id)) {
            printf("DUPLICATE ID FOUND: %s\n", id);
            valid = 0;
        }

        for (int j = 0; j < 5; j++) {
            if (marks[j] < 0 || marks[j] > 100) {
                printf("INVALID MARKS for ID %s\n", id);
                valid = 0;
                break;
            }
        }

        if (valid) {
            strcpy(s[count].id, id);
            strcpy(s[count].name, name);
            for (int j = 0; j < 5; j++) {
                s[count].marks[j] = marks[j];
            }
            count++;
            printf("RECORD ACCEPTED: %s\n", id);
        }
    }

    fclose(fp);
    printf("\nTOTAL VALID RECORDS = %d\n", count);

    return 0;
}
