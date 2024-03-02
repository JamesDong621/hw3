#include "llrec.h"

//*********************************************
// Provide your implementation of llpivot below
//*********************************************



void llpivotRecursive(Node* current, Node*& smaller, Node*& larger, Node*& smallTail, Node*& largeTail, int pivot) {
    if (current == nullptr) {
        // Base case: end of the original list
        return;
    }

    if (current->val <= pivot) {
        // Append current to smaller list
        if (smaller == nullptr) {
            smaller = current; // Initialize smaller list
            smallTail = current; // This node is now the tail of the smaller list
        } else {
            smallTail->next = current; // Append to smaller list
            smallTail = current; // Update tail
        }
    } else {
        // Append current to larger list
        if (larger == nullptr) {
            larger = current; // Initialize larger list
            largeTail = current; // This node is now the tail of the larger list
        } else {
            largeTail->next = current; // Append to larger list
            largeTail = current; // Update tail
        }
    }

    Node* nextNode = current->next; // Save next node before potentially modifying it
    current->next = nullptr;
    llpivotRecursive(nextNode, smaller, larger, smallTail, largeTail, pivot);
}

void llpivot(Node*& head, Node*& smaller, Node*& larger, int pivot) {
    smaller = nullptr; // Ensure smaller starts as nullptr
    larger = nullptr; // Ensure larger starts as nullptr
    Node *smallTail = nullptr, *largeTail = nullptr; // Tails for managing the end of lists

    llpivotRecursive(head, smaller, larger, smallTail, largeTail, pivot);

    // Ensure the original list is completely detached
    head = nullptr;
}