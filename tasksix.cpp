#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

// Splits text into words
vector<string> getWords(const string& text) {
    vector<string> words;
    istringstream stream(text);
    string word;
    while (stream >> word) {
        words.push_back(word);
    }
    return words;
}

// Displays text with word wrapping
void displayWrappedText(const vector<string>& words, int maxWidth) {
    int width = 0;
    int lineNum = 1;

    for (const string& word : words) {
        // If word exceeds the max width, start a new line
        if (width + word.length() > maxWidth) {
            cout << endl << "line " << lineNum << ": " << word;
            width = word.length() + 1; // Add space after the word
            lineNum++;
        } else {
            // If not at the beginning, add a space before the word
            if (width > 0) {
                cout << " ";
                width++; // Count the space
            }
            cout << word;
            width += word.length();
        }
    }
    cout << endl;
}

int main() {
    string textToWrap = "Mary loves to sing and perform tapdancing.";
    int maxLineLength = 10;

    // Get the words from the text
    vector<string> words = getWords(textToWrap);

    // Print the text with word wrapping
    displayWrappedText(words, maxLineLength);

    return 0;
}
