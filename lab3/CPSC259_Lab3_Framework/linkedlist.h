/*
 File:         linkedlist.h
 Purpose:      Prototypes for a linked list implementation
 Author:       Randy Ren
 Student #s:   56695331
 CWLs:         rren05
 Date:         Saturday October 12th, 2024
 */

#pragma once

/* Define the airplane structure */
typedef struct airplane {
    int flight_number;            // Flight number (integer)
    char* city_origin;            // Pointer to a string for the origin city
    char* city_destination;       // Pointer to a string for the destination city
    int priority;                 // Priority level (integer)
    int maximum_speed_kph;        // Maximum speed in kph (integer)
    int cruising_altitude;        // Cruising altitude (integer)
    int capacity;                 // Capacity of the airplane (integer)
} airplane;

/* Define the node structure for the linked list */
typedef struct node {
    airplane plane;               // The airplane data stored in the node
    struct node* next;            // Pointer to the next node in the list
} node;

/* Prototypes for in-lab functions */
node* create_linked_list();
node* create_node(airplane plane);
node* prepend_node(node* list, node* new_node);
node* delete_node(node* list);

/* Prototypes for take-home functions */
int get_length(node* list);
node* delete_list(node* list);
void print_node(node* node_to_print);
void print_list(node* list_to_print);
node* reverse(node* list);
node* remove_from_list(node* list, char* destination_city);
node* retrieve_nth(node* list, int ordinality);
node* insert_nth(node* list, node* node_to_insert, int ordinality);
