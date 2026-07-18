#pragma once

#include <stdexcept>

template <class DataType>
class LinkedList
{
    struct ListNode
    {
        DataType storedData;
        ListNode *nextNode;

        ListNode(DataType dataParam, ListNode *nextParam = nullptr)
        {
            storedData = dataParam;
            nextNode = nextParam;
        }
    };
    ListNode *m_headNode;
    ListNode *m_tailNode;
    int m_listSize;

public:
    class Iterator
    {
    public:
        Iterator()
        {
            m_currentNode = nullptr;
        }

        Iterator(ListNode *nodeParam) { m_currentNode = nodeParam; }

        DataType &operator*() const
        {
            return m_currentNode->storedData;
        }

        Iterator &operator++()
        {
            m_currentNode = m_currentNode->nextNode;
            return *this;
        }

        bool operator!=(const Iterator &otherIterator) const
        {
            return m_currentNode != otherIterator.m_currentNode;
        }

    protected:
        ListNode *m_currentNode;
    };

    LinkedList()
    {
        m_headNode = nullptr;
        m_tailNode = nullptr;
        m_listSize = 0;
    }

    void clearList()
    {
        while (m_headNode != nullptr)
        {
            ListNode *tempNode = m_headNode;
            m_headNode = m_headNode->nextNode;
            delete tempNode;
        }
        m_tailNode = nullptr;
        m_listSize = 0;
    }

    ~LinkedList() { clearList(); }

    bool isListEmpty() const { return m_headNode == nullptr; }

    int getListSize() const { return m_listSize; }

    void insertAtBeginning(DataType value)
    {
        ListNode *newnode = new ListNode(value);
        newnode->nextNode = m_headNode;
        m_headNode = newnode;

        if (m_tailNode == nullptr)
        {
            m_tailNode = m_headNode;
        }
        m_listSize++;
    }

    void insertAtEnd(DataType value)
    {
        ListNode *nnode = new ListNode(value, nullptr);
        if (isListEmpty())
        {
            m_headNode = m_tailNode = nnode;
        }
        else
        {
            m_tailNode->nextNode = nnode;
            m_tailNode = nnode;
        }
        m_listSize++;
    }

    DataType &getElementByIndex(int index)
    {
        if (index < 0 || index >= m_listSize)
        {
            throw std::out_of_range("requested index is out of bounds");
        }
        ListNode *tmp = m_headNode;
        for (int i = 0; i < index; ++i)
        {
            tmp = tmp->nextNode;
        }
        return tmp->storedData;
    }

    int searchElement(DataType value) const
    {
        ListNode *tmp = m_headNode;
        int index = 0;
        while (tmp != nullptr)
        {
            if (tmp->storedData == value)
            {
                return index;
            }
            tmp = tmp->nextNode;
            index++;
        }
        return -1;
    }

    Iterator begin() const { return Iterator(m_headNode); }

    Iterator end() const { return Iterator(nullptr); }
};
