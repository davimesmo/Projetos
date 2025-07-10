#include <iostream>
#include "list.hpp"

void List::insertNode(int data) {
  Node* aux = new Node;
  aux->data = data;
  aux->next = nullptr;
  if (head == nullptr) {
    head = aux;
    tail = aux;
  } else {
    tail->next = aux;
    tail = aux;
  }
}

void List::display() {
  Node *aux = head;
  while (aux != nullptr) {
    cout << aux->data << " ";
    aux = aux->next;
  }
  cout << endl;
}

// Você deverá implementar apenas esse método
void List::inverte(){
  Node *temp = nullptr;
  Node *temp2 = nullptr;
  while(head != nullptr){
    temp2 = head->next;
    head->next = temp;
    temp = head;
    head = temp2;
  }
  head = temp;
}



