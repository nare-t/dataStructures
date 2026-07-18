#include <iostream>
#include <string>

#include "map.hpp"

using namespace std;

int main()
{
    cout << "testing keyvaluepair\n";
    KeyValuePair<string, string> kv1("barev", "dzez");
    KeyValuePair<string, string> kv2("barev", "bolorin");
    KeyValuePair<string, string> kv3("mek", "erku");

    cout << "equal key true " << kv1.hasEqualKey(kv2) << "\n";
    cout << "equal key false " << kv1.hasEqualKey(kv3) << "\n";

    cout << "testing list\n";
    List<string, string> list;
    cout << "empty true " << list.isListEmpty() << "\n";

    list.insertAtBeginning(kv1);
    list.insertAtBeginning(kv3);
    cout << "empty false " << list.isListEmpty() << "\n";
    cout << "size " << list.getListSize() << "\n";

    auto foundNode = list.searchElement(kv1);
    if (foundNode != nullptr)
    {
        cout << "found element value " << foundNode->storedData.value << "\n";
    }

    cout << "remove true " << list.removeElement(kv3) << "\n";
    cout << "size after remove one " << list.getListSize() << "\n";

    list.clearList();
    cout << "size after clear zero " << list.getListSize() << "\n";

    HashMap<string, string> map(2);

    map.insertOrUpdate("nare", "torosyan");
    map.insertOrUpdate("hzor", "renjer");

    cout << "remove by key true " << map.removeByKey("hzor") << "\n";
    cout << "remove by key false " << map.removeByKey("eddy") << "\n";

    cout << "fine";
    return 0;
}