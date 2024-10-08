#include <iostream>
#include <algorithm>
#include <cctype>
#include <cstring>

using namespace std;

class StringConverter {
public:
    static string convertToUpper(const string &text) {
        string upperText = text;
        transform(upperText.begin(), upperText.end(), upperText.begin(), ::toupper);
        return upperText;
    }

    static string convertToLower(const string &text) {
        string lowerText = text;
        transform(lowerText.begin(), lowerText.end(), lowerText.begin(), ::tolower);
        return lowerText;
    }
};

int main(int argumentCount, char *argumentValues[]) {
    if (argumentCount < 3) {
        cerr << "Usage: " << argumentValues[0] << " <upper|lower> <'text to convert'>" << endl;
        return 1;
    }

    string command(argumentValues[1]);
    string inputText;

    // Concatenate all remaining arguments into a single string
    for (int i = 2; i < argumentCount; ++i) {
        if (i > 2)
            inputText += " ";
        inputText += argumentValues[i];
    }

    if (command == "upper") {
        cout << StringConverter::convertToUpper(inputText) << endl;
    } else if (command == "lower") {
        cout << StringConverter::convertToLower(inputText) << endl;
    } else {
        cerr << "Invalid option: " << command << ". Use 'upper' or 'lower'." << endl;
        return 1;
    }

    return 0;
}