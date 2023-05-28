#include <iostream>
#include "RedBlackTree.h"
#include <string>
#include <locale.h>
#include<fstream>
#include"myExceptions.h"
#include <chrono>

void TestHighVolumeTranslation()
{

    RedBlackTree translator;
    int wordCounter = 0;

    std::ifstream file("data.txt");
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            wordCounter++;

            std::string key, value;
            size_t delimiterPos = line.find(' ');
            if (delimiterPos != std::string::npos) {
                key = line.substr(0, delimiterPos);
                value = line.substr(delimiterPos + 1);
                
                translator.insert(key, value);
               

            }
        }
      
        translator.printDictionary(std::cout);
        std::cout << "\n translation \n ";
        std::cout << wordCounter << " words added to the dictionary from the data.txt \n ";
        std::cout << ((translator.isRedBlackTree() == true) ? "tree is balanced" : "tree is not balanced");
        file.close();
    }
    else {
        std::cout << "file cant open" << std::endl;
        exit(0);
    }
    std::cout << "\n";
    try {

        std::string sentence = "John Smith is studying Russian ." "John Smith is_an_American . He is_an_engineer but now he is studying Russian . "
            " John loves Russian language and literature . His favorite Russian writer is Fyodor Dostoevsky . John Smith reads a lot in Russian . "
            " He is studying Russian  the language is only a year_old , but already understands Russian well . Every day he writes exercises , "
            " learns words and grammar , reads , translates and tells texts , listens to a  recorder and watches Russian films .  John Smith speaks lot_of Russian . "
            " His Russian friend is Viktor Nikitin.";
        std::string translation = translator.translate(sentence);
        std::cout << "Sentence: " << sentence << std::endl;
        std::cout << "\n \n \n";
        std::cout << "Translation: " << translation << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << e.what();
    }
  /*  std::cout << "TEST _____ \n \n \n";
    auto beginAvg = std::chrono::high_resolution_clock::now();
   
    translator.deleteWord("zzz");

    auto endAvg = std::chrono::high_resolution_clock::now();
    auto elapsedAvg = std::chrono::duration_cast<std::chrono::nanoseconds>(endAvg - beginAvg);
    printf("Time measured for Average Array: %.3f seconds.\n", elapsedAvg.count() * 1e-9);*/
  
    file.close();

}

void BasicTestForOperations()
{
    RedBlackTree RedBlackTree;
    RedBlackTree.insert("hello", "приветь");
    RedBlackTree.insert("good", "хорошо");
    RedBlackTree.insert("bad", "плохо");
    RedBlackTree.insert("world", "мир");
    RedBlackTree.insert("hello", "здравствуйте");
    RedBlackTree.insert("bye", "пока");
    RedBlackTree.insert("fruit", "яблоко");
    RedBlackTree.insert("fruit", "банан");
    RedBlackTree.insert("fruit", "яблоко");
    RedBlackTree.insert("fruit", "банан");
    RedBlackTree.insert("fruit", "апельсин");
    RedBlackTree.insert("fruit", "клубника");
    RedBlackTree.insert("fruit", "вишня");
   
    std::cout << "\n";
    std::cout << ((RedBlackTree.isRedBlackTree() == true) ? "tree is balanced" : "tree is not balanced");
    std::cout << "\n";
   // RedBlackTree.printDictionary(std::cout);
    RedBlackTree.deleteWord("fruit");
    std::cout << ((RedBlackTree.isRedBlackTree() == true) ? "tree is balanced" : "tree is not balanced");
    std::cout << "\n";
  //  RedBlackTree.printDictionary(std::cout);
    std::cout << ((RedBlackTree.search("hello") == true) ? "key founded " : "key not founded") << std::endl;
    std::cout << "delete key hello "<<std::endl;
    RedBlackTree.deleteWord("hello");
    std::cout << ((RedBlackTree.isRedBlackTree() == true) ? "tree is balanced" : "tree is not balanced");
    std::cout << "\n";
   // RedBlackTree.printDictionary(std::cout);
    std::cout << ((RedBlackTree.search("world") == true) ? "key founded " : "key not founded") << std::endl;
    std::cout << "delete key world   " << std::endl;
    RedBlackTree.deleteWord("world");
    std::cout << ((RedBlackTree.isRedBlackTree() == true) ? "tree is balanced" : "tree is not balanced");
    std::cout << "\n";
    RedBlackTree.printDictionary(std::cout);
    std::cout << ((RedBlackTree.search("bye") == true) ? "key founded " : "key not founded") << std::endl;
    std::cout << "delete key bye   " << std::endl;
    RedBlackTree.deleteWord("bye");
    std::cout << ((RedBlackTree.isRedBlackTree() == true) ? "tree2 is balanced" : "tree is2 not balanced");
    std::cout << "\n";
    RedBlackTree.printDictionary(std::cout);
    std::cout << ((RedBlackTree.search("good") == true) ? "key founded " : "key not founded") << std::endl;
    std::cout << "delete key good   " << std::endl;
    RedBlackTree.deleteWord("good");
    std::cout << ((RedBlackTree.isRedBlackTree() == true) ? "tree is balanced" : "tree is not balanced");
    std::cout << "\n";
    RedBlackTree.printDictionary(std::cout);
    std::cout << ((RedBlackTree.search("bad") == true) ? "key founded " : "key not founded") << std::endl;
    std::cout << "delete key bad   " << std::endl;
    RedBlackTree.deleteWord("bad");
    std::cout << ((RedBlackTree.isRedBlackTree() == true) ? "tree is balanced" : "tree is not balanced");
    std::cout << "\n";
    RedBlackTree.printDictionary(std::cout);


}


bool hasNonLatinCharacters(const std::string& input) {
    for (char c : input) {

        if (c == ' ')
        {
            continue;
        }
        if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))) {
            return true;  // Non-Latin character found
        }
    }
    return false;  // No non-Latin characters found
}

bool isLatin(const std::string& input) {
    return !hasNonLatinCharacters(input);
}

void commands()
{



    RedBlackTree UserTestTree;
    int command;
    std::string key;
    std::string meaning;
    std::string sentence;

    bool userWantsToDoSomeTests = true;
    std::cout << "You choose info" << std::endl;
    std::cout << "insert: 1" << std::endl;
    std::cout << "delete: 2" << std::endl;
    std::cout << "search: 3" << std::endl;
    std::cout << "translate: 4" << std::endl;
    std::cout << "print word: 5" << std::endl;
    std::cout << "print dictionary: 6" << std::endl;
    std::cout << "tree balance: 7 " << std::endl;
    std::cout << "info: 8 " << std::endl;
    std::cout << "Take Dictionary From file: 9 " << std::endl;
    std::cout << "exit: 10 " << std::endl;
    while (userWantsToDoSomeTests)
    {
        std::cin >> command;
        if (!std::cin)
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "try again Wrong type of input " << std::endl;
            continue;
        }


        if (command == 1)
        {
            std::cout << "You choose insert" << std::endl;
            std::cout << "Enter your English word: ";
            std::cin >> key;
            if (!std::cin || !isLatin(key))
            {
                std::cerr << "Invalid input. A word expected. choose to again command " << std::endl;
            
                continue;
            }
            std::cout << "Enter the Russian translation: ";
            std::cin.ignore();  // Ignore the newline character in the input buffer
            std::getline(std::cin, meaning);
            if (!std::cin || !isLatin(meaning))
            {
                std::cerr << "Invalid input. Russian translation expected." << std::endl;
                continue;
            }
            UserTestTree.insert(key, meaning);
            std::cout << "Word inserted successfully." << std::endl;
        }
        else if (command == 2)
        {
            std::cout << "You choose delete" << std::endl;
            std::cout << "Enter the English word to delete: ";
            std::cin >> key;
            if (!std::cin || !isLatin(key))
            {
                std::cerr << "Invalid input. English word expected." << std::endl;
                continue;
            }
            UserTestTree.deleteWord(key);
        
        }
        else if (command == 3)
        {
            std::cout << "You choose search" << std::endl;
            std::cout << "Enter the English word to search: ";
            std::cin >> key;
            if (!std::cin || !isLatin(key))
            {
                std::cerr << "Invalid input. English word expected." << std::endl;
                continue;
            }
            if (UserTestTree.search(key))
            {
                std::cout << "Word found." << std::endl;
            }
            else
            {
                std::cout << "Word not found." << std::endl;
            }
        }
        else if (command == 4)
        {
            std::cout << "You choose translate" << std::endl;
            std::cout << "Enter the English sentence to translate: ";
            std::cin.ignore();  // Ignore the newline character in the input buffer
            std::getline(std::cin, sentence);

            if (!isLatin(sentence))
            {
                std::cout << "And  ";
                std::cerr << "Invalid input. English sentence expected." << std::endl;
                continue;
            }
            std::string translation = UserTestTree.translate(sentence);
            if (!translation.empty())
            {
                std::cout << "Translation: " << translation << std::endl;
            }
            else
            {
                std::cout << "Translation not found." << std::endl;
            }
        }

        else if (command == 5)
        {
            std::cout << "You choose print word" << std::endl;
            std::cout << "Enter the English word to print: ";
            std::cin >> key;
            if (!std::cin || !isLatin(key))
            {
                std::cerr << "Invalid input. English word expected." << std::endl;
                continue;
            }
            UserTestTree.printWord(key, std::cout);
        }
        else if (command == 6)
        {
            std::cout << "You choose print dictionary" << std::endl;
            UserTestTree.printDictionary(std::cout);
        }
      
        else if (command == 7)
        {
            std::cout << "You choose tree balance" << std::endl;
            std::cout << ((UserTestTree.isRedBlackTree() == true) ? "tree is balanced" : "tree is not balanced");
            std::cout << "\n";

        }
        else if (command == 8)
        {
            std::cout << "You choose info" << std::endl;
            std::cout << "insert: 1" << std::endl;
            std::cout << "delete: 2" << std::endl;
            std::cout << "search: 3" << std::endl;
            std::cout << "translate: 4" << std::endl;
            std::cout << "print word: 5" << std::endl;
            std::cout << "print dictionary: 6" << std::endl;
            std::cout << "tree balance: 7 " << std::endl;
            std::cout << "info: 8 " << std::endl;
            std::cout << "Take Dictionary From file: 9 " << std::endl;
            std::cout << "exit: 10 " << std::endl;
        }
        else if (command == 9)
        {
            std::string filename;
            std::cout << "Enter the file name: ";
            std::cin >> filename;
            int wordCounter = 0;

                std::ifstream file(filename);
                if (!file)
                {
                    std::cerr<<"Failed to open file. Make sure the file exists.";
                    continue;
                }

                std::string line;
                while (std::getline(file, line))
                {
                    wordCounter++;

                    std::string key, value;
                    size_t delimiterPos = line.find(' ');
                    if (delimiterPos != std::string::npos)
                    {
                        key = line.substr(0, delimiterPos);
                        value = line.substr(delimiterPos + 1);
                        UserTestTree.insert(key, value);
                    }
                }
                std::cout << wordCounter << " words added to the dictionary from the file.\n";
                std::cout << ((UserTestTree.isRedBlackTree()) ? "The tree is balanced.\n" : "The tree is not balanced.\n");
                file.close();
        }
        else if (command == 10)
        {
            std::cout << "Exiting the program." << std::endl;
               userWantsToDoSomeTests = false;  // Set the flag to exit the loop
        }
        else
        {
            std::cout << "Invalid choice. choose again " << std::endl;
            continue;
        }
    }


}
int main()
{

    setlocale(LC_ALL, "rusça");
   

        std::string commend;

        char userDecision = ' ';

        bool userWantsToExit = false;
        try
        {
            while (!userWantsToExit) {

                std::cout << "Pre-made test or input by user? Enter 'Y' for input by user, 'N' for the pre-made test, or 'E' to exit: " << std::endl;
                std::cin >> userDecision;

                if (!std::cin) {
                    std::cerr << "wrong input \n";
                }

                if (userDecision == 'Y' || userDecision == 'y') {

                    std::cout << "User input selected.\n";
                    commands();
                }
                else if (userDecision == 'N' || userDecision == 'n') {

                    std::cout << "Pre-made test selected.\n";
                    TestHighVolumeTranslation();
                    BasicTestForOperations();

                }
                else if (userDecision == 'E' || userDecision == 'e') {
                    userWantsToExit = true;
                }
            }

            std::cout << "Program ended.\n";
        }
        catch (const std::exception& e)
        {
            std::cerr << e.what();
        }
          


    return 0;

}