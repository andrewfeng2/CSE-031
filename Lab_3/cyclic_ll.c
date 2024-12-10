#include <stdio.h>

typedef struct node {
  int value;
  struct node *next;
} node;

int has_cycle(node *head) {
	// Your code goes here:
	if (head == NULL || head->next == NULL) { //Checks for empty list or list with only one node 
		return 0;  // No cycle in empty list or list with single node
	}

	// Step 1: Start with two pointers at the head of the list 
  // Initiates two pointers slow and fast 
	node *slow = head;  //moves one step at a time
	node *fast = head->next;   //moves two steps at a time

	// Step 2: Increment pointers and check for end of list
	while (fast != NULL && fast->next != NULL) {  //Loops until fast reaches end of list 
		
		// Step 3: Checks for cycle
		if (slow == fast) {  // a. The second pointer is the same as the first pointer
			return 1;  // Cycle detected
		}
		if (slow == fast->next) {  // b. The next node of the second pointer is pointed to by the first pointer
			return 1;  // Cycle detected
		}
		slow = slow->next;  //Moves slow pointer one step
		fast = fast->next->next; //Moves fast pointer two steps
	}

	return 0;  // No cycle found
}

void test_has_cycle(void) {
  int i;
  node nodes[25]; //enough to run our tests
  for(i=0; i < sizeof(nodes)/sizeof(node); i++) {
    nodes[i].next = 0;
    nodes[i].value = 0;
  }
  nodes[0].next = &nodes[1];
  nodes[1].next = &nodes[2];
  nodes[2].next = &nodes[3];
  printf("Checking first list for cycles. There should be none, has_cycle says it has %s cycle\n",
    has_cycle(&nodes[0])?"a":"no");
  
  nodes[4].next = &nodes[5];
  nodes[5].next = &nodes[6];
  nodes[6].next = &nodes[7];
  nodes[7].next = &nodes[8];
  nodes[8].next = &nodes[9];
  nodes[9].next = &nodes[10];
  nodes[10].next = &nodes[4];
  printf("Checking second list for cycles. There should be a cycle, has_cycle says it has %s cycle\n",
    has_cycle(&nodes[4])?"a":"no");
  
  nodes[11].next = &nodes[12];
  nodes[12].next = &nodes[13];
  nodes[13].next = &nodes[14];
  nodes[14].next = &nodes[15];
  nodes[15].next = &nodes[16];
  nodes[16].next = &nodes[17];
  nodes[17].next = &nodes[14];
  printf("Checking third list for cycles. There should be a cycle, has_cycle says it has %s cycle\n",
    has_cycle(&nodes[11])?"a":"no");
  
  nodes[18].next = &nodes[18];
  printf("Checking fourth list for cycles. There should be a cycle, has_cycle says it has %s cycle\n",
    has_cycle(&nodes[18])?"a":"no");
  
  nodes[19].next = &nodes[20];
  nodes[20].next = &nodes[21];
  nodes[21].next = &nodes[22];
  nodes[22].next = &nodes[23];
  printf("Checking fifth list for cycles. There should be none, has_cycle says it has %s cycle\n",
    has_cycle(&nodes[19])?"a":"no");
  
  printf("Checking length-zero list for cycles. There should be none, has_cycle says it has %s cycle\n",
    has_cycle(NULL)?"a":"no");
}

int main(void) {
  test_has_cycle();
  return 0;
}
