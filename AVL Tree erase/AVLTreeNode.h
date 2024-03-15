#pragma once
#include <utility>//std::move

template <typename T>
struct Node
{
    T m_element{};
    Node* m_left = nullptr, *m_right = nullptr;
    int m_balanceFactor = 0, m_height = 0;

    Node(T&& elem) : m_element{std::move(elem)} {} //move an element into a node.
    Node(T const& elem) : m_element{elem} {} //copy an element into a node

    Node() = delete;//No default construction of Nodes allowed.

    //No move construction of Nodes allowed.
    //Instead The tree will try to move the underlying T with the constructor overload
    //That takes a T rvalue reference. This is because the Node still needs to be used
    //after that move (NOT the m_element since that will be moved from by then).
    Node(Node&&) = delete;

    Node(Node const&) = default;

    void updateHeightAndBalanceFactor()
    {
        int rightTreeHeight = m_right ? m_right->m_height : -1;
        int leftTreeHeight  = m_left  ? m_left->m_height  : -1;
        m_height = std::max(rightTreeHeight, leftTreeHeight) + 1;
        m_balanceFactor = rightTreeHeight - leftTreeHeight;
    }

    //Should be called after the above method is called, since the balance factor needs to be updated first.
    //parentsChildPtr is the pointer (inside this' parent) that points to this node.
    void reBalance(Node*& parentsChildPtr)
    {   
        if(m_balanceFactor == -2)//this node is left heavy
        {
            //a left-right double rotation is necessary
            if(m_left->m_balanceFactor == 1) 
                m_left->leftRotate(m_left);

            rightRotate(parentsChildPtr);
        }       
        else if(m_balanceFactor == 2)//this node is right heavy
        {
            //a right-left double rotation is necessary
            if(m_right->m_balanceFactor == -1) 
                m_right->rightRotate(m_right);
            
            leftRotate(parentsChildPtr);
        }
    }

    //parentsChildPtr is the pointer (inside this' parent) that points to this node.
    void leftRotate(Node*& parentsChildPtr)
    {
        auto oldRightChild = m_right;//save the pointer to the right child (this nodes right child will become this node's new parent)
        m_right = oldRightChild->m_left;//assign a new right child to this node
        oldRightChild->m_left = this;//the new parent of this node is now this node's old right child
        parentsChildPtr = oldRightChild;//the old parent of this node now points to this node's old right child
        updateHeightAndBalanceFactor();//update the height and BF of this node before we update this node's new parent
        oldRightChild->updateHeightAndBalanceFactor();//update this node's new parent
    }

    //parentsChildPtr is the pointer (inside this' parent) that points to this node.
    void rightRotate(Node*& parentsChildPtr)
    {
        auto oldLeftChld = m_left;//save the pointer to the left child (this nodes left child will become this node's new parent)
        m_left = oldLeftChld->m_right;//assign a new left child to this node
        oldLeftChld->m_right = this;//the new parent of this node is now this node's old left child
        parentsChildPtr = oldLeftChld;//the old parent of this node now points to this node's old left child
        updateHeightAndBalanceFactor();//update the height and BF of this node before we update this node's new parent
        oldLeftChld->updateHeightAndBalanceFactor();//update this node's new parent
    }
};