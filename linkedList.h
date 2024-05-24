#ifndef NH_LINKEDLIST_H
#define NH_LINKEDLIST_H

#include "node.h"
#include "memtrace.h"

#include <iostream>

/**
 * @brief LinkedList class for a linked list.
 * @tparam T Type of data stored in the linked list.
 */
template<typename T>
class LinkedList{
    Node<T> *head; ///< Pointer to the head of the linked list.
    size_t size; ///< Size of the linked list.

public:
    /**
   * @brief Constructor for LinkedList class.
   * @param head Pointer to the head of the linked list.
   * @param size Size of the linked list.
   */
    LinkedList(Node<T> *head = nullptr, size_t size = 0) : head(head), size(size) {}


    /**
    * @brief Insert data into the linked list.
    * @param data Data to be inserted into the linked list.
    */
    void insert(T data){
        Node<T> *newNode = new Node<T>(data);
        if(!head){
            head = newNode;
        }else{
            Node<T> *curr = head;
            while(curr->getNext() != nullptr){
                curr = curr->getNext();
            }
            curr->setNext(newNode);
        }
        size++;

    }

    /**
    * @brief Remove data from the linked list.
    * @param data Data to be removed from the linked list.
    */
    void remove(T data){
        if(!head){
            return;
        }
        else if(head->getData() == data){
            Node<T> *tmp = head;
            head = head->getNext();
            delete tmp;
            size--;
            return;
        }
        else{
            Node<T> *curr = head;
            while(curr->getNext() != nullptr){
                if(curr->getNext()->getData() == data){
                    Node<T> *tmp = curr->getNext();

                    curr->setNext(tmp->getNext());
                    delete tmp;
                    size--;
                    return;
                }
                curr = curr->getNext();
            }
        }
        size--;
    }


    /**
     * @brief Get the iterator to the beginning of the linked list.
     * @return Iterator to the beginning of the linked list.
     */
    Node<T> * begin() const {return head;}

    /**
     * @brief Get the iterator to the end of the linked list.
     * @return Iterator to the end of the linked list.
     */
    Node<T>* end(){
        return nullptr;
    }

    /**
     * @brief Get the node at the specified index in the linked list.
     * @param index Index of the node to be retrieved.
     * @return Pointer to the node at the specified index.
     * @throw std::out_of_range if the index is out of bounds.
     */
    Node<T>* operator[](int index){
        if(index < 0 || static_cast<size_t>(index) > size){
            throw std::out_of_range("Index out of bounds");
        }

        Node<T> *curr = head;
        for(int i = 0; i < index; i++){
            curr = curr->getNext();
        }

        return curr;

    }

    /**
     * @brief Get the size of the linked list.
     * @return Size of the linked list.
     */
    size_t getSize() const {
        return size;
    }

    /**
     * @brief Destructor for LinkedList class.
     * Deletes all nodes in the linked list.
     */
    ~LinkedList(){
        Node<T> *curr = head;
        while(curr != nullptr){
            Node<T> *tmp = curr;
            curr = curr->getNext();
            delete tmp;
        }
    }
};


#endif //NH_LINKEDLIST_H
