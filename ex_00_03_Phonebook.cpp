#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

// Struct to represent a contact
struct Contact {
    std::string name;
    std::string phoneNumber;
    std::string nickname;
    bool isBookmarked;
};

// Class to handle the phonebook operations
class Phonebook {
private:
    std::vector<Contact> contacts;
    std::map<std::string, int> phoneMap;

    void displayContact(const Contact& contact, int index) {
        std::cout << "-------------------------" << std::endl;
        std::cout << "Index: " << index << std::endl;
        std::cout << "Name: " << contact.name << std::endl;
        std::cout << "Phone Number: " << contact.phoneNumber << std::endl;
        std::cout << "Nickname: " << contact.nickname << std::endl;
        std::cout << "Bookmarked: " << (contact.isBookmarked ? "Yes" : "No") << std::endl;
        std::cout << "-------------------------" << std::endl;
    }

    bool caseInsensitiveCompare(const std::string& a, const std::string& b) {
        std::string lowerA = a;
        std::string lowerB = b;
        std::transform(lowerA.begin(), lowerA.end(), lowerA.begin(), ::tolower);
        std::transform(lowerB.begin(), lowerB.end(), lowerB.begin(), ::tolower);
        return lowerA == lowerB;
    }

public:
    void add() {
        Contact newContact;
        std::string bookmark_status;

        std::cout << "\nEnter Name: ";
        std::cin.ignore();
        getline(std::cin, newContact.name);

        std::cout << "Enter Phone number: ";
        std::cin >> newContact.phoneNumber;

        // Check if phone number exists
        if (phoneMap.find(newContact.phoneNumber) != phoneMap.end()) {
            std::cout << "Error: This phone number already exists. Try a different number.\n";
            return;
        }

        std::cout << "Enter Nickname: ";
        std::cin >> newContact.nickname;

        std::cout << "Bookmark Status (y/n): ";
        std::cin >> bookmark_status;

        newContact.isBookmarked = (bookmark_status == "y");

        contacts.push_back(newContact);
        phoneMap[newContact.phoneNumber] = contacts.size() - 1;

        std::cout << "Contact added successfully!\n";
    }

    void search() {
        std::string query;
        std::cout << "\nEnter Name or Phone Number: ";
        std::cin >> query;

        bool found = false;
        for (int i = 0; i < contacts.size(); ++i) {
            if (caseInsensitiveCompare(contacts[i].name, query) || contacts[i].phoneNumber == query) {
                displayContact(contacts[i], i);
                found = true;
            }
        }

        if (!found) {
            std::cout << "No contacts found with that name or phone number.\n";
        }
    }

    void edit() {
        std::string phone;
        std::cout << "\nEnter Phone Number to Edit: ";
        std::cin >> phone;

        if (phoneMap.find(phone) == phoneMap.end()) {
            std::cout << "Contact not found!\n";
            return;
        }

        int index = phoneMap[phone];
        Contact& contact = contacts[index];

        std::cout << "Editing Contact:\n";
        displayContact(contact, index);

        std::string newName, newPhone, newNickname, bookmarkStatus;
        std::cout << "Enter New Name (or press Enter to keep current): ";
        std::cin.ignore();
        getline(std::cin, newName);

        std::cout << "Enter New Phone Number (or press Enter to keep current): ";
        getline(std::cin, newPhone);

        std::cout << "Enter New Nickname (or press Enter to keep current): ";
        getline(std::cin, newNickname);

        std::cout << "Bookmark Status (y/n or press Enter to keep current): ";
        getline(std::cin, bookmarkStatus);

        // Update only if the user provided new values
        if (!newName.empty()) contact.name = newName;
        if (!newPhone.empty() && phoneMap.find(newPhone) == phoneMap.end()) {
            phoneMap.erase(contact.phoneNumber);  // Remove old phone number from map
            contact.phoneNumber = newPhone;
            phoneMap[newPhone] = index;
        }
        if (!newNickname.empty()) contact.nickname = newNickname;
        if (!bookmarkStatus.empty()) contact.isBookmarked = (bookmarkStatus == "y");

        std::cout << "Contact updated successfully!\n";
    }

    void remove() {
        std::string query;
        std::cout << "\nEnter Phone Number to Remove: ";
        std::cin >> query;

        if (phoneMap.find(query) != phoneMap.end()) {
            int index = phoneMap[query];
            contacts.erase(contacts.begin() + index);
            phoneMap.erase(query);

            // Update phoneMap indexes for contacts after the removed contact
            for (int i = index; i < contacts.size(); ++i) {
                phoneMap[contacts[i].phoneNumber] = i;
            }

            std::cout << "Contact removed successfully!\n";
        } else {
            std::cout << "Contact not found.\n";
        }
    }

    void listAll() {
        std::cout << "\nList of All Contacts:\n";
        for (int i = 0; i < contacts.size(); ++i) {
            displayContact(contacts[i], i);
        }
    }

    void listBookmarks() {
        std::cout << "\nBookmarked Contacts:\n";
        bool found = false;
        for (int i = 0; i < contacts.size(); ++i) {
            if (contacts[i].isBookmarked) {
                displayContact(contacts[i], i);
                found = true;
            }
        }

        if (!found) {
            std::cout << "No bookmarked contacts.\n";
        }
    }
};

int main() {
    Phonebook phonebook;
    std::string command;

    std::cout << "Welcome to the Phonebook Manager!\n";

    while (true) {
        std::cout << "\nEnter command (ADD, SEARCH, EDIT, REMOVE, LIST, BOOKMARKS, EXIT): ";
        std::cin >> command;

        if (command == "ADD") {
            phonebook.add();
        } else if (command == "SEARCH") {
            phonebook.search();
        } else if (command == "EDIT") {
            phonebook.edit();
        } else if (command == "REMOVE") {
            phonebook.remove();
        } else if (command == "LIST") {
            phonebook.listAll();
        } else if (command == "BOOKMARKS") {
            phonebook.listBookmarks();
        } else if (command == "EXIT") {
            std::cout << "Exiting Phonebook Manager. Goodbye!\n";
            break;
        } else {
            std::cout << "Invalid command! Please try again.\n";
        }
    }

    return 0;
}
