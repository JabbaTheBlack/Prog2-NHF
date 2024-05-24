#ifndef NH_NODE_H
#define NH_NODE_H

#include <iostream>
#include "memtrace.h"

/**
 * @brief Node class for a linked list.
 * @tparam T Type of data stored in the node.
 */
template<typename T>
class Node{
    T data; ///< Data stored in the node.
    Node<T> *next; ///< Pointer to the next node.

public:
    /**
     * @brief Constructor for Node class.
     * @param data Data to be stored in the node.
     * @param next Pointer to the next node.
     */
    Node(T data, Node<T> *next = nullptr) : data(data), next(next){}

    /**
     * @brief Get the data stored in the node.
     * @return Data stored in the node.
     */
    T getData() const {
        return data;
    }

    /**
     * @brief Get the pointer to the next node.
     * @return Pointer to the next node.
     */
    Node<T>* getNext(){
        return next;
    }
    /**
     * @brief Set the data stored in the node.
     * @param data Data to be stored in the node.
     */
    void setData(T data){
        this->data = data;
    }

    /**
     * @brief Set the pointer to the next node.
     * @param next Pointer to the next node.
     */
    void setNext(Node<T> *next){
        this->next = next;
    }

};

#endif //NH_NODE_H
