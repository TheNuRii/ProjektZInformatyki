#pragma once

template <typename T>
class Node{
public:
    Node(T data, Node<T>* next = nullptr, Node<T>* prev = nullptr);
    ~Node();

    T getData();
    Node<T>* getNextElement();
    Node<T>* getPrevElement();

    void setData(T new_data);
    void setNextElement(Node<T>* new_next);
    void setPrevElement(Node<T>* new_prev);
private:
    T data_;
    Node<T>* next_element_;
    Node<T>* prev_element_;
};

template <typename T>
class DoubleLinkedList{
public:
    DoubleLinkedList();
    ~DoubleLinkedList();

    void addElementToList(const T& new_element);
    void removeElementFromList(const T& element_to_remove);
    void printFromTheBeginning();
    void printFromTheEnd();

private:
    Node<T>* list_head_;
    Node<T>* list_tail_;
    int list_size_;
};