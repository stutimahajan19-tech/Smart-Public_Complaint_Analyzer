#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "complaint_ds.h"

void addComplaint(ComplaintNode** head)
{
    ComplaintNode* newNode;

    newNode = (ComplaintNode*)malloc(sizeof(ComplaintNode));

    if (newNode == NULL)
    {
        printf("Memory allocation failed.\n");
        return;
    }

    printf("\n========== REGISTER COMPLAINT ==========\n");

    printf("Enter Complaint ID: ");
    scanf("%d", &newNode->complaintID);
    getchar();

    printf("Enter Citizen Name: ");
    fgets(newNode->citizenName, 100, stdin);
    newNode->citizenName[strcspn(newNode->citizenName, "\n")] = '\0';

    printf("Enter Category: ");
    fgets(newNode->category, 50, stdin);
    newNode->category[strcspn(newNode->category, "\n")] = '\0';

    printf("Enter Description: ");
    fgets(newNode->description, 200, stdin);
    newNode->description[strcspn(newNode->description, "\n")] = '\0';

    printf("Enter Location: ");
    fgets(newNode->location, 100, stdin);
    newNode->location[strcspn(newNode->location, "\n")] = '\0';

   int priorityChoice;

printf("Select Priority:\n");
printf("1. High\n");
printf("2. Medium\n");
printf("3. Low\n");

printf("Enter your choice: ");
scanf("%d", &priorityChoice);
getchar();

if (priorityChoice == 1)
{
    strcpy(newNode->priority, "High");
    newNode->priorityValue = 3;
}
else if (priorityChoice == 2)
{
    strcpy(newNode->priority, "Medium");
    newNode->priorityValue = 2;
}
else if (priorityChoice == 3)
{
    strcpy(newNode->priority, "Low");
    newNode->priorityValue = 1;
}
else
{
    printf("Invalid priority. Setting priority to Low.\n");

    strcpy(newNode->priority, "Low");
    newNode->priorityValue = 1;
}
    strcpy(newNode->status, "Pending");
    strcpy(newNode->department, "Not Assigned");
    strcpy(newNode->employee, "Not Assigned");

    newNode->next = NULL; 

    if (*head == NULL)
    {
        *head = newNode;
    }
    else
    {
        ComplaintNode* current = *head;

        while (current->next != NULL)
        {
            current = current->next;
        }

        current->next = newNode;
    }

printf("\nComplaint registered successfully!\n");
printf("Status: %s\n", newNode->status);
printf("Department: %s\n", newNode->department);
}

void displayComplaints(ComplaintNode* head)
{
    ComplaintNode* current = head;

    if (head == NULL)
    {
        printf("\nNo complaints found.\n");
        return;
    }

    while (current != NULL)
    {
        printf("\n-----------------------------\n");
        printf("Complaint ID: %d\n", current->complaintID);
        printf("Citizen Name: %s\n", current->citizenName);
        printf("Category: %s\n", current->category);
        printf("Description: %s\n", current->description);
        printf("Location: %s\n", current->location);
        printf("Priority: %s\n", current->priority);
        printf("Status: %s\n", current->status);
        printf("Department: %s\n", current->department);
        printf("Employee: %s\n", current->employee);
        current = current->next;
    }
}

void searchComplaint(ComplaintNode* head, int id)
{
    ComplaintNode* current = head;

    while (current != NULL)
    {
        if (current->complaintID == id)
        {
            printf("\n========== COMPLAINT FOUND ==========\n");
            printf("Complaint ID: %d\n", current->complaintID);
            printf("Citizen Name: %s\n", current->citizenName);
            printf("Category: %s\n", current->category);
            printf("Description: %s\n", current->description);
            printf("Location: %s\n", current->location);
            printf("Priority: %s\n", current->priority);
            printf("Status: %s\n", current->status);
            printf("Department: %s\n", current->department);
            printf("Employee: %s\n", current->employee);

            return;
        }

        current = current->next;
    }

    printf("\nComplaint not found.\n");
}
void updateStatus(ComplaintNode* head, int id, const char newStatus[])
{
    ComplaintNode* current = head;

    while (current != NULL)
    {
        if (current->complaintID == id)
        {
            strcpy(current->status, newStatus);

            printf("\nComplaint status updated successfully!\n");
            printf("New Status: %s\n", current->status);

            return;
        }

        current = current->next;
    }

    printf("\nComplaint not found.\n");
}
void assignDepartment(ComplaintNode* head, int id, const char newDepartment[])
{
    ComplaintNode* current = head;

    while (current != NULL)
    {
        if (current->complaintID == id)
        {
            strcpy(current->department, newDepartment);

            printf("\nDepartment assigned successfully!\n");
            printf("Department: %s\n", current->department);

            return;
        }

        current = current->next;
    }

    printf("\nComplaint not found.\n");
}
void assignEmployee(ComplaintNode* head, int id, const char newEmployee[])
{
    ComplaintNode* current = head;

    while (current != NULL)
    {
        if (current->complaintID == id)
        {
            strcpy(current->employee, newEmployee);

            printf("\nEmployee assigned successfully!\n");
            printf("Employee: %s\n", current->employee);

            return;
        }

        current = current->next;
    }

    printf("\nComplaint not found.\n");
}
void insertPriorityQueue(PriorityNode** front, ComplaintNode* complaint)
{
    PriorityNode* newNode;
    PriorityNode* current;

    newNode = (PriorityNode*)malloc(sizeof(PriorityNode));

    if (newNode == NULL)
    {
        printf("Memory allocation failed.\n");
        return;
    }

    newNode->complaint = complaint;
    newNode->next = NULL;

    if (*front == NULL ||
        complaint->priorityValue > (*front)->complaint->priorityValue)
    {
        newNode->next = *front;
        *front = newNode;
        return;
    }

    current = *front;

    while (current->next != NULL &&
           current->next->complaint->priorityValue >= complaint->priorityValue)
    {
        current = current->next;
    }

    newNode->next = current->next;
    current->next = newNode;
}
void displayPriorityQueue(PriorityNode* front)
{
    PriorityNode* current = front;

    if (front == NULL)
    {
        printf("\nPriority Queue is empty.\n");
        return;
    }

    printf("\n========== PRIORITY QUEUE ==========\n");

    while (current != NULL)
    {
        printf("\nComplaint ID: %d\n",
               current->complaint->complaintID);

        printf("Priority: %s\n",
               current->complaint->priority);

        printf("Description: %s\n",
               current->complaint->description);

        printf("Status: %s\n",
               current->complaint->status);

        current = current->next;
    }
}
void sortComplaintsByPriority(ComplaintNode* head)
{
    ComplaintNode* current;
    ComplaintNode* compare;

    if (head == NULL)
    {
        printf("\nNo complaints to sort.\n");
        return;
    }

    current = head;

    while (current != NULL)
    {
        compare = current->next;

        while (compare != NULL)
        {
            if (current->priorityValue < compare->priorityValue)
            {
                int temp = current->priorityValue;

                current->priorityValue = compare->priorityValue;
                compare->priorityValue = temp;

                char tempPriority[20];

                strcpy(tempPriority, current->priority);
                strcpy(current->priority, compare->priority);
                strcpy(compare->priority, tempPriority);
            }

            compare = compare->next;
        }

        current = current->next;
    }

    printf("\nComplaints sorted by priority successfully!\n");
}