#include "AVLTreeNode.h"

int main()
{
    //There is no impl for an AVL tree here and no code to be executed. 
    //for that go to https://github.com/oskarGrr/myContainers/tree/main/AVLTree
    //I just wanted to include the erase function from that project 
    //as an interesting example here for my algorithms repository.

    return 0;
}

//Returns true or false indicating whether or not toErase was found and deleted.
template <typename T>
bool erase(T const& toErase)
{
    bool wasErased = false;

    //C++23's "deducing this" used here in this lamda to capture a reference to the functor
    //object in order to recursively call the lambda. passing "this" in the lambda capture only makes 
    //sense when used in the context of the project this was from, 
    //since erase was inside of an AVL tree class.
    auto deleteNode = [&wasErased, this](this auto const& self, Node*& node, T const& toErase) -> void
    {
        //Base case: the call stack has reached a leaf node in the tree
        if(!node) return;

        if(toErase < node->m_element) self(node->m_left, toErase);
        else if(toErase > node->m_element) self(node->m_right, toErase);

        else if(node->m_left && node->m_right)//if two child nodes replace toErase with its in order predecessor
        {
            auto predecessor = maxNode(node->m_left);
            node->m_element = std::move(predecessor->m_element);//try to move the contents over
            self(node->m_left, node->m_element);//now delete the predecessor
        }
        else//if one or zero child nodes
        {
            auto nodeToDelete = node;

            //make sure the parent points to the child of the node we are deleting (if any)
            node = node->m_left ? node->m_left : node->m_right;

            delete nodeToDelete;
            wasErased = true;
            return;
        }

        node->updateHeightAndBalanceFactor();
        node->reBalance(node);
        return;
    };
}