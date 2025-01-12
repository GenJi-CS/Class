#include <stdio.h>
#include <stdlib.h>

struct Node
{
	struct Node *prev;
	int data;
	struct Node *next;
} *head; 

void displayInstructions();
void print();
void insertAtFront( int );
void insertAtBack( int );
void insertAtArbitraryLocation( int, int );
void removeFromFront();
void removeFromBack();
void removeByValue( int );
void removeByLocation( int );
struct Node *search( int );
struct Node *getNewNode( int );
void sort();
int length();
void reverse();
int isEmpty();

main()
{
	head = NULL; 
	
	int choice; 
	
	do
	{
		displayInstructions();
		scanf( "%d", &choice );
		
		switch ( choice ) 
		{
			case 1:
			{
				int value;
				
				printf( "Enter an integer: " );
				scanf( "%d", &value );
				
				insertAtFront( value );
				print(); 
				break;
			}
			case 2:
			{
				int value;
		
				printf( "Enter an integer: " );
				scanf( "%d", &value );
				
				insertAtBack( value );
				print(); 
				break;
			}
			case 3:
			{
				int value, location;

				printf( "Enter an integer and an insert location: ");
				scanf( "%d %d", &value, &location );

				insertAtArbitraryLocation( value, location );
				print(); 
				break;
			}
			case 4:
			{
				removeFromFront();
				print(); 
				break;
			}
			case 5:
			{
				removeFromBack();
				print(); 
				break;
			}
			case 6:
			{
				int location;

				printf( "Enter a location for deletion: " );
				scanf( "%d", &location );

				removeByLocation( location );
				print( ); 
				break;
			}
			case 7:
			{
				int value;

				printf( "Enter an integer: " );
				scanf( "%d", &value );

				removeByValue( value );
				print(); 
				break;
			}
			case 8:
			{
				sort();
				print();
				break;
			}
			case 9:
			{
				print(); 
				break;
			}
		} 
	} while ( choice < 10 ); 
} 

void insertAtFront( int value )
{
	struct Node *newNode = getNewNode( value );

	if ( isEmpty() ) 	
		head = newNode;
	else
	{
		newNode->next = head;
		newNode->prev = NULL; 
		
		head = newNode;
	}
} 

void insertAtBack( int value )
{
	struct Node *newNode = getNewNode( value );

	if ( isEmpty() ) 
		head = newNode;
	else 
	{
		struct Node *currentPtr = head;
		
		while ( currentPtr->next != NULL ) 
			currentPtr = currentPtr->next;
		
		currentPtr->next = newNode;
		newNode->prev = currentPtr;
	} 
} 

void insertAtArbitraryLocation( int value, int location )
{
	struct Node *newNode = getNewNode( value );

	if ( location == 1 )
		insertAtFront( value );
	else if ( location == length() + 1 )
		insertAtBack( value );
	else
	{
		struct Node *currentPtr = head;

		for ( int i = 1; i < location - 1; i++ )
			currentPtr = currentPtr->next;

		newNode->next = currentPtr->next;
		currentPtr->next = newNode;
		
		newNode->prev = currentPtr;
		( newNode->next )->prev = newNode;
	} 
} 

void removeFromFront()
{
	if ( isEmpty() ) 
		printf( "List is empty. Cannot remove.\n" );
	else if ( head->next == NULL ) 
		head = NULL; 
	else 
	{
		struct Node *delNode = head;

		head = head->next; 
		head->prev = NULL;

		free( delNode );
	} 
} 

void removeFromBack()
{
	if ( isEmpty() ) 
		printf( "List is empty. Cannot remove.\n" );
	else if ( head->next == NULL ) 
		removeFromFront();
	else 
	{
		struct Node *delPtr = head; 
		
		while ( delPtr->next != NULL ) 
			delPtr = delPtr->next;

		struct Node *prevPtr = delPtr->prev; 
		
		prevPtr->next = NULL;
		delPtr->prev = NULL;

		free( delPtr );
	}
} 

void removeByLocation( int location )
{
	if ( location < 1 || location > length() )
		printf( "Invalid location" );
	else if ( location == 1 )
		removeFromFront();
	else if ( location == length() )
		removeFromBack();
	else
	{
		struct Node *currentPtr = head;

		for ( int i = 1; i < location; i++ )
			currentPtr = currentPtr->next;

		struct Node *prevPtr = currentPtr->prev;

		prevPtr->next = currentPtr->next;
		( prevPtr->next )->prev = prevPtr;

		free( currentPtr );
	} 
} 

void removeByValue( int value )
{
	struct Node *delPtr = search( value );

	if ( delPtr == NULL )
		printf( "Value not found. Cannot remove.\n" );
	else
	{
		if ( delPtr->prev == NULL ) 
			removeFromFront();
		else if ( delPtr->next == NULL ) 
			removeFromBack();
		else
		{
			struct Node *prevPtr = delPtr->prev;

			prevPtr->next = delPtr->next;
			( prevPtr->next )->prev = prevPtr;

			free( delPtr );
		} 
	} 
} 

int isEmpty()
{
	if ( head == NULL )
		return 1;
	else
		return 0;
} 

void print()
{
	if( isEmpty() ) 
	{
		printf( "\nList is empty.\n\n" );
		return;
	} 
	else
	{
		struct Node *currentPtr = head; 
		
		printf( "\nThe List is: " );
		
		while ( currentPtr != NULL )
		{
			printf( "%d ", currentPtr->data );
			currentPtr = currentPtr->next;
		} 
		
		printf( "\n\n" );
	} 
} 

struct Node *search( int searchKey )
{
	struct Node *traversePtr = head;
	
	while ( traversePtr != NULL && traversePtr->data != searchKey )
		traversePtr = traversePtr->next;
		
	return traversePtr;
} 

void displayInstructions()
{
	printf( "Please enter one of the following: \n" );
	printf( " 1 - Insert at the front of the list\n" );
	printf( " 2 - Insert at the end of the list\n" );
	printf( " 3 - Insert at an arbitrary location\n" );
	printf( " 4 - Remove from the front of the list\n" );
	printf( " 5 - Remove from the end of the list\n" );
	printf( " 6 - Remove from any given location\n" );
	printf( " 7 - Remove the first node with a given data field\n" );
	printf( " 8 - Sort the list in incresing order\n" );
	printf( " 9 - Display the contents of the list\n" );
	
	printf( "\n? " );
}

struct Node *getNewNode( int value )
{
	struct Node *newNode = ( struct Node * )malloc( sizeof( struct Node ) );

	newNode->data = value;
	newNode->next = NULL;
	newNode->prev = NULL;

	return newNode;
} 

int length()
{
	int count = 0; 

	struct Node *currentPtr = head;

	while ( currentPtr != NULL )
	{
		count++;
		currentPtr = currentPtr->next;
	} 

	return count; 
} 

void sort()
{
	struct Node *currentPtr, *nextPtr; 

	for ( currentPtr = head; currentPtr != NULL; currentPtr = currentPtr->next )
	{
		for ( nextPtr = currentPtr->next; nextPtr != NULL; nextPtr = nextPtr->next )
		{
			if ( currentPtr->data > nextPtr->data )
			{
				int temp = currentPtr->data;
				currentPtr->data = nextPtr->data;
				nextPtr->data = temp;
			} 
		} 
	} 
} 