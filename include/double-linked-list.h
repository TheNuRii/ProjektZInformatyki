#pragma once

template <typename T>
class Node{
public:
    Node(T data, Node<T>* next = nullptr, Node<T>* prev = nullptr);
    ~Node();

    T getData();
    Node<T>* getNext();
    Node<T>* getPrev();

    void setData(T new_data);
    void setNext(Node<T>* new_next);
    void setPrev(Node<T>* new_prev);
private:
    T data_;
    Node<T>* next_element_;
    Node<T>* prev_element_;
};