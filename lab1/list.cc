#include <iostream>
#include "list.h"

List::List(){
	first = NULL;
}

List::~List() {
	while(first != NULL) {
					 Node * n = first->next;
					 delete first;
					 first = n;
			 }
}

bool List::exists(int d) const {

	Node* curr = first;
	while (curr != NULL){
		if (curr->value == d){
			return true;
		}
		curr = curr->next;
	}
	return false;
}

int List::size() const {
	int counter = 0;
	Node* curr = first;

	while (curr != NULL){
		curr = curr->next;
		counter++;
	}

	return counter;
}

bool List::empty() const {
	return first == NULL;
}

void List::insertFirst(int d) {
	if(first == NULL){
		first = new Node(d, NULL);
	} else {
 	Node* temp = new Node(d, first->next);
 	first->next = temp;
 }
}


void List::remove(int d, DeleteFlag df) {
	Node* prev = NULL;
	Node* curr = first;

	bool shouldDelete = false;
	while (curr != NULL){
		switch(df){
			case DeleteFlag::EQUAL:
					shouldDelete = curr->value == d;
					break;
			case DeleteFlag::LESS:
						shouldDelete = curr->value < d;
				 break;
			case DeleteFlag::GREATER:
						shouldDelete = curr->value > d;
						break;
			}

		if (shouldDelete){
			if (prev == NULL){
				if (curr->next == NULL){
					delete first;
					delete curr;
					first = NULL;
					curr = NULL;
				} else {
				Node* temp = first;
				first = first->next;
				curr = first->next;
				delete temp;
			}
			} else{
				prev->next = curr->next;
				delete curr;
				curr = prev->next;
			}

			return;
		} else{
			prev = curr;
			curr = curr->next;
		}
}}

void List::print() const {
	if(first == NULL){
		std:: cout << "Empty List";
	}
	Node* curr = first;

	while (curr != NULL){
		std::cout << curr->value << std::endl;
		curr = curr->next;
	}
}
