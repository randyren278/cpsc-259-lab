/*
 File:         linkedlist.c
 Purpose:      Implements the linked list functions whose prototypes
               are declared in the linked_list.h header file
 Author:       Randy Ren
 Student #s:   56695331
 CWLs:         rren05
 Date:         Saturday October 12th, 2024
 */

#define _CRT_SECURE_NO_WARNINGS

/* Preprocessor directives */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"

/******************************************************************
 PLEASE EDIT THIS FILE
 Comments that start with // should be replaced with code
 Comments that are surrounded by * are hints
 ******************************************************************/

/* Create an empty linked list */
node* create_linked_list() {
    return NULL;  // Empty list is represented by NULL
}

/* Create a new node */
node* create_node(airplane plane) {
    node* new_node = (node*)malloc(sizeof(node));
    if (new_node == NULL) {
        return NULL;  // Memory allocation failed
    }

    // Copy airplane data into the new node
    new_node->plane.flight_number = plane.flight_number;
    new_node->plane.priority = plane.priority;
    new_node->plane.maximum_speed_kph = plane.maximum_speed_kph;
    new_node->plane.cruising_altitude = plane.cruising_altitude;
    new_node->plane.capacity = plane.capacity;

    // Copy string attributes
    new_node->plane.city_origin = strdup(plane.city_origin);
    new_node->plane.city_destination = strdup(plane.city_destination);

    new_node->next = NULL;    // Set next pointer to NULL
    return new_node;
}

/* Prepend a node to the linked list */
node* prepend_node(node* list, node* new_node) {
    new_node->next = list;  // New node points to the current head
    return new_node;        // Return the new node as the new head
}

/* Delete the first node in the linked list */
node* delete_node(node* list) {
    if (list == NULL) {
        return NULL;  // If the list is empty, nothing to delete
    }
    node* temp = list;  // Store the current head
    list = list->next;  // Move the head to the next node
    free(temp->plane.city_origin); // Free the dynamically allocated strings
    free(temp->plane.city_destination);
    free(temp);         // Free memory of the removed node
    return list;        // Return the updated list
}

/* Get the length of the linked list */
int get_length(node* list) {
    int count = 0;
    node* current = list;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

/* Delete the entire linked list */
node* delete_list(node* list) {
    node* current = list;
    while (current != NULL) {
        node* next = current->next;  // Store the next node
        free(current->plane.city_origin); // Free the dynamically allocated strings
        free(current->plane.city_destination);
        free(current);               // Free the current node
        current = next;              // Move to the next node
    }
    return NULL;  // Return NULL as the list is now empty
}

/* Print the information of a single node */
void print_node(node* node_to_print) {
    if (node_to_print == NULL) {
        printf("The node is empty\n");
        return;
    }
    printf("Flight Number: %d\n", node_to_print->plane.flight_number);
    printf("Origin: %s\n", node_to_print->plane.city_origin);
    printf("Destination: %s\n", node_to_print->plane.city_destination);
    printf("Priority: %d\n", node_to_print->plane.priority);
    printf("Max Speed: %d kph\n", node_to_print->plane.maximum_speed_kph);
    printf("Altitude: %d meters\n", node_to_print->plane.cruising_altitude);
    printf("Capacity: %d passengers\n", node_to_print->plane.capacity);
}

/* Print the entire linked list */
void print_list(node* list_to_print) {
    if (list_to_print == NULL) {
        printf("The list is empty\n");
        return;
    }
    node* current = list_to_print;
    while (current != NULL) {
        print_node(current);
        current = current->next;  // Move to the next node
    }
}

/* Reverse the order of the linked list */
node* reverse(node* list) {
    node* prev = NULL;
    node* current = list;
    node* next = NULL;
    while (current != NULL) {
        next = current->next;  // Store the next node
        current->next = prev;  // Reverse the pointer
        prev = current;        // Move prev and current one step forward
        current = next;
    }
    return prev;  // Return the new head of the reversed list
}

/* Remove all nodes with a matching destination city */
node* remove_from_list(node* list, char* destination_city) {
    node* current = list;
    node* prev = NULL;

    while (current != NULL) {
        // If the current node's destination matches the target city
        if (strcmp(current->plane.city_destination, destination_city) == 0) {
            // If we are removing the head of the list
            if (prev == NULL) {
                list = current->next;  // Move the head to the next node
            } else {
                prev->next = current->next;  // Link previous node to next node
            }

            // Save the next node before freeing current
            node* temp = current;
            current = current->next;  // Move to the next node before freeing

            // Free the memory associated with the removed node
            free(temp->plane.city_origin);
            free(temp->plane.city_destination);
            free(temp);
        } else {
            // Move previous and current pointers forward if no removal occurs
            prev = current;
            current = current->next;
        }
    }
    return list;
}

/* Retrieve the nth node from the linked list */
node* retrieve_nth(node* list, int ordinality) {
    int count = 1;
    node* current = list;
    while (current != NULL && count < ordinality) {
        current = current->next;
        count++;
    }
    return (count == ordinality) ? current : NULL;
}

/* Insert a node at a specific position in the linked list */
node* insert_nth(node* list, node* node_to_insert, int ordinality) {
    if (ordinality == 1) {
        return prepend_node(list, node_to_insert);
    }

    int count = 1;
    node* current = list;
    while (current != NULL && count < ordinality - 1) {
        current = current->next;
        count++;
    }

    if (current != NULL) {
        node_to_insert->next = current->next;
        current->next = node_to_insert;
    }

    return list;
}
