#include "../include/double-linked-list.h"

using namespace std;

// Implementacja klasy Node
template <typename T>
Node<T>::Node(T data, Node<T>* next, Node<T>* prev){
    data_ = data;
    next_element_ = next;
    prev_element_ = prev;
}

template <typename T>
Node<T>::~Node() {
    next_element_ = nullptr;
    prev_element_ = nullptr;
}

template <typename T>
T Node<T>::getData() {return data_;}

template <typename T>
Node<T>* Node<T>::getNextElement(){return next_element_;}

template <typename T>
Node<T>* Node<T>::getPrevElement(){return prev_element_;}

template <typename T>
void Node<T>::setData(T new_data){data_ = new_data;}

template <typename T>
void Node<T>::setNextElement(Node<T>* new_next){next_element_ = new_next;}

template <typename T>
void Node<T>::setPrevElement(Node<T>* new_prev){prev_element_ = new_prev;}

// Implementacja klasy DoubleLinkedList

template <typename T>
DoubleLinkedList<T>::DoubleLinkedList(){
    list_head_ = nullptr;
    list_tail_ = nullptr;
    list_size_ = 0;
}

template <typename T>
DoubleLinkedList<T>::~DoubleLinkedList(){
     while (list_head_ != nullptr) {
            Node<T> *temp = list_head_;
            list_head_ = list_head_->getNextElement();
            delete temp;
    }
    list_head_ = nullptr;
    list_tail_ = nullptr;
}

template <typename T>
void DoubleLinkedList<T>::addElementToList(const T& new_element){
    Node<T>* new_element_node = new Node<T>(new_element);
    if (list_head_ == nullptr){
        list_head_ = new_element_node;
        list_tail_ = new_element_node;
        list_size_++;
    } else {
        list_tail_->setNextElement(new_element_node);
        new_element_node->setPrevElement(list_tail);
        list_tail_ = new_element_node;
        list_size_++;
    }
}

template <typename T>
void DoubleLinkedList<T>::removeElementFromList(const T& elemnt_to_remove){
    Node<T>* current = list_head_;
    while (current != nullptr) {
        if(current->getData() == elemnt_to_remove){
            if(current == list_head_){
                list_head_ = current->getNextElement();
                list_head_->setPrevElement(nullptr);
                delete current;
                list_size_--;
            }
            else if(current == list_tail_){
                list_tail_ = current->getPrevElement();
                list_tail_->setNextElement(nullptr);
                delete current;
                list_size_--;
            }
            else{
                current->getPrevElement()->setNextElement(current->getNextElement());
                current->getNextElement()->setPrevElement(current->getPrevElement());
                delete current;
                list_size_--;
            }
            break;
        }
    }
}
