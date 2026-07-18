#pragma once

#include <stdexcept>
#include <string>
#include <vector>

template <class KeyType, class ValueType>
struct KeyValuePair
{
    KeyType key;
    ValueType value;

    KeyValuePair() {}

    KeyValuePair(KeyType keyParam, ValueType valueParam = ValueType())
    {
        key = keyParam;
        value = valueParam;
    }

    bool hasEqualKey(const KeyValuePair<KeyType, ValueType> &otherPair) const
    {
        return key == otherPair.key;
    }
};

template <class KeyType, class ValueType>
class List
{
public:
    struct ListNode
    {
        KeyValuePair<KeyType, ValueType> storedData;
        ListNode *nextNode;

        ListNode(KeyValuePair<KeyType, ValueType> data,
                 ListNode *next = nullptr)
        {
            storedData = data;
            nextNode = next;
        }
    };

private:
    ListNode *m_headNode;
    int m_listSize;

public:
    List()
    {
        m_headNode = nullptr;
        m_listSize = 0;
    }

    ~List() { clearList(); }

    void clearList()
    {
        while (m_headNode != nullptr)
        {
            ListNode *tempNode = m_headNode;
            m_headNode = m_headNode->nextNode;
            delete tempNode;
        }
        m_listSize = 0;
    }

    int getListSize() const { return m_listSize; }
    bool isListEmpty() const { return m_headNode == nullptr; }

    void insertAtBeginning(KeyValuePair<KeyType, ValueType> data)
    {
        m_headNode = new ListNode(data, m_headNode);
        m_listSize++;
    }

    ListNode *searchElement(
        const KeyValuePair<KeyType, ValueType> &targetValue) const
    {
        ListNode *currentNode = m_headNode;
        while (currentNode != nullptr)
        {
            if (currentNode->storedData.hasEqualKey(targetValue))
            {
                return currentNode;
            }
            currentNode = currentNode->nextNode;
        }
        return nullptr;
    }

    bool removeElement(KeyValuePair<KeyType, ValueType> targetValue)
    {
        ListNode *currentNode = m_headNode;
        ListNode *previousNode = nullptr;

        while (currentNode != nullptr)
        {
            if (currentNode->storedData.hasEqualKey(targetValue))
            {
                if (previousNode == nullptr)
                {
                    m_headNode = currentNode->nextNode;
                }
                else
                {
                    previousNode->nextNode = currentNode->nextNode;
                }
                delete currentNode;
                m_listSize--;
                return true;
            }
            previousNode = currentNode;
            currentNode = currentNode->nextNode;
        }
        return false;
    }

    ListNode *getHeadNode() const { return m_headNode; }
};

template <class KeyType, class ValueType>
class HashMap
{
private:
    std::vector<List<KeyType, ValueType>> m_hashTable;
    int m_tableSize;
    int m_totalElements;
    double m_maxLoadFactor;

public:
    HashMap(int initialTableSize = 101)
    {
        m_tableSize = initialTableSize;
        m_hashTable.resize(m_tableSize);
        m_maxLoadFactor = 0.75;
        m_totalElements = 0;
    }

private:
    int calculateStringHashCode(const std::string &key) const
    {
        const int hashMultiplier = 31;
        int generatedHash = 0;
        for (int i = 0; i < key.length(); ++i)
        {
            generatedHash = hashMultiplier * generatedHash + key[i];
        }
        return generatedHash;
    }

    int getCompressedBucketIndex(const std::string &key) const
    {
        int uncompressedHash = calculateStringHashCode(key);
        int nonNegativeHash = uncompressedHash & 0x7FFFFFFF;
        return nonNegativeHash % m_tableSize;
    }

    void resize()
    {
        int newTableSize = m_tableSize * 2;
        std::vector<List<KeyType, ValueType>> newHashTable(newTableSize);

        int oldTableSize = m_tableSize;
        m_tableSize = newTableSize;

        for (int i = 0; i < oldTableSize; ++i)
        {
            auto current = m_hashTable[i].getHeadNode();
            while (current != nullptr)
            {
                int newBucketIndex =
                    getCompressedBucketIndex(current->storedData.key);
                newHashTable[newBucketIndex].insertAtBeginning(
                    current->storedData);
                current = current->nextNode;
            }
        }
        m_hashTable = std::move(newHashTable);
    }

public:
    void insertOrUpdate(KeyType key, ValueType value)
    {
        double currentLoadFactor = double(m_totalElements + 1) / m_tableSize;
        if (currentLoadFactor > m_maxLoadFactor)
        {
            resize();
        }

        int bucketIndex = getCompressedBucketIndex(key);
        KeyValuePair<KeyType, ValueType> dummyPair(key, value);

        typename List<KeyType, ValueType>::ListNode *existingNode =
            m_hashTable[bucketIndex].searchElement(dummyPair);

        if (existingNode != nullptr)
        {
            existingNode->storedData.value = value;
        }
        else
        {
            m_hashTable[bucketIndex].insertAtBeginning(dummyPair);
            m_totalElements++;
        }
    }

    bool removeByKey(KeyType key)
    {
        int bucketIndex = getCompressedBucketIndex(key);
        KeyValuePair<KeyType, ValueType> dummyPair(key);

        bool isRemoved = m_hashTable[bucketIndex].removeElement(dummyPair);
        if (isRemoved)
        {
            m_totalElements--;
            return true;
        }
        return false;
    }
};