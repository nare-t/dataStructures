#include <iostream>
#include <string>
#include "linked-list.hpp"

using namespace std;

int main()
{
    LinkedList<string> list;

    cout << "empty true " << list.isListEmpty() << "\n";

    list.insertAtBeginning("astx");
    list.insertAtEnd("arev");
    list.insertAtEnd("lusin");

    cout << "empty false " << list.isListEmpty() << "\n";
    cout << "size " << list.getListSize() << "\n";

    cout << "element at index one " << list.getElementByIndex(1) << "\n";
    cout << "search existing element index " << list.searchElement("lusin") << "\n";

    for (auto it = list.begin(); it != list.end(); ++it)
    {
        cout << "node data " << *it << "\n";
    }

    list.clearList();
    cout << "size after clear zero " << list.getListSize() << "\n";

    LinkedList<string> breakList;
    breakList.insertAtBeginning("nare");
    cout << "fine " << breakList.getElementByIndex(0) << "\n";

    return 0;
}