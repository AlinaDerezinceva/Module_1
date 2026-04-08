#ifndef STRUCTURES_H
#define STRUCTURES_H

typedef struct {
    char fio[100];
    char job[50];
    char phone[50];
    char email[50];
    char links[100];
} Contact;

typedef struct {
    Contact *contacts;
    int size;
} ContactsArray;

typedef enum { 
    FIELD_JOB, 
    FIELD_PHONE, 
    FIELD_EMAIL, 
    FIELD_LINKS 
} Field;

#endif