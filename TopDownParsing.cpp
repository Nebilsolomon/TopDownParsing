////
//  main.cpp
//  Prog1


//
//  main.cpp
//  Prog1
//Group members: Long Calamia, Nebil Gokdemir, Alex Ghasemi



#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <iomanip>



using namespace::std;


int findRow(string row);
int findColumn(string column);
bool checkString(string x);
char inputChar(string prompt, string listChars);

//int main(int argc, const char * argv[])


int main() {



    //  cout <<"my ||||||||||||||||| is " <<nebil[2][0] << endl;

    string table[5][8] =
    {

        //  a       +       -       *       /        (       )       $
          {"TQ" ,  "0",   "0",   "0",   "0",    "TQ",   "0",   "0"}, //  E
          {"0" ,  "+TQ",  "-TQ",  "0",   "0",    "0",   "z",    "z"},  // Q
          {"FR" ,  "0",   "0",   "0",   "0",    "FR",   "0",   "0"}, // T
          {"0" ,  "z",    "z",    "*FR",  "/FR",   "0",   "z",    "z"}, // R
          {"a" ,   "0",   "0",   "0",   "0",    "(E)",  "0",   "0"}, // F


        
        
        
        
        
        
        
        
        
        
    };
    while (true)
    {
        cout << endl << endl;
        cout << "The given grammar is\n\n";
        cout << "E -> TQ\n";
        cout << "Q -> +TQ | -TQ | epsilon \n";
        cout << "T -> FR\n";
        cout << "R -> *FR | /FR | epsilon \n";
        cout << "F -> (E)| a \n";
        cout << endl << "(1) Test: (a+a)*a$ \n(2) Test: a*(a/a)$ \n(3) Test: a(a+a)$ \n(4) Enter your own string \n(5) To Exit." << endl;
        string listOfOption = "12345";
        int input = inputChar(" Enter test options : ", listOfOption);

        string sourceCode;
        switch (input)
        {
        case '1':
            sourceCode = "(a+a)*a$";
            break;
        case '2':
            sourceCode = "a*(a/a)$";
            break;
        case '3':
            sourceCode = "a(a+a)$";
            break;
        case '4':
            cout << "Enter a string that ends with a $";
            cin >> sourceCode;
            break;
        case '5':
            exit(1);
        }

        stack<string> stacky;
        string topStack = "";

        cout << endl << endl << "Evaluating \"" << sourceCode << "\"" << endl;
        cout << "=========================================================================================" << endl;
        int lengthOfString = sourceCode.length();
        stacky.push("$");
        stacky.push("E"); // starting state is E
        int charOfString;

        int indexRow;
        int stringIndex = 0;
        int indexcolunm;


        string tempInput = sourceCode;

        while (lengthOfString > 0)
        {


            topStack = stacky.top();

            if (topStack == "$" && tempInput == "$")
            {
                stacky.pop();
                cout << endl << endl << "the end, " << sourceCode << " is part of the grammar";
                break;
            }


            if (checkString(stacky.top()))
            {
                tempInput = tempInput.substr(1);
                stack<string> tempStack;
                stack<string> tempStack2 = stacky;

                while (!tempStack2.empty()) // copying stack for output
                {
                    tempStack.push(tempStack2.top());
                    tempStack2.pop();
                }


                cout << endl << right << setw(8) << "Stack" << setw(20) << "Top of Stack" << setw(20) << "Input" << setw(20) << "Production" << endl;
                cout << right << setw(8);

                while (!tempStack.empty()) //outputing stack from left to right( bottom to top)
                {
                    cout << tempStack.top();
                    tempStack.pop();
                }
                cout << right << setw(7) << topStack << setw(30) << tempInput << setw(10) << "[\"" << topStack << "\" pop and go to next token]" << endl;
                // cout << "top stack   is:   " << topStack << endl<< endl;
                //cout << "yes \"" << stacky.top() << "\" is a terminal state" << endl;

                stringIndex = 1 + stringIndex;
                stacky.pop();
                lengthOfString = lengthOfString - 1;
            }
            else
            {

                indexRow = findRow(topStack); // finds the row coordinate of the predictive parsing table
                if (indexRow > 4)
                {
                    break;
                }

                string index = "";
                index += sourceCode[stringIndex];

                indexcolunm = findColumn(index); // finds the collumn coordinate of the predictive parsing table
                if (indexcolunm > 7)
                {
                    cout<< endl << endl << "INVALID character input! " << sourceCode << " is not part of the language." << endl;
                    break;
                }
                if (table[indexRow][indexcolunm] == "0")
                {
                    cout << " error not table entry for [" << topStack << ", " << index << "], " << sourceCode<< " is not part of the language. ";
                    break;
                }

                string temp = "";


                cout << endl;

                stack<string> tempStack;
                stack<string> tempStack2 = stacky;

                while (!tempStack2.empty()) // copying stack for output
                {
                    tempStack.push(tempStack2.top());
                    tempStack2.pop();
                }


                cout << right << setw(8) << "Stack" << setw(20) << "Top of Stack" << setw(20) << "Input" << setw(20) << "Production" << endl;
                cout << right << setw(8);

                while (!tempStack.empty()) //outputing stack from left to right( bottom to top)
                {
                    cout << tempStack.top();
                    tempStack.pop();
                }
                if (table[indexRow][indexcolunm] == "z")
                {
                    cout << right << setw(7) << topStack << setw(30) << tempInput << right << setw(15) << topStack << " -> epsilon" << endl;
                }
                else
                {
                    cout << right << setw(7) << topStack << setw(30) << tempInput << right << setw(15) << topStack << " -> " << table[indexRow][indexcolunm] << endl;
                }
                // cout << "top stack   is:   " << topStack << endl<< endl;

               // cout << endl << endl << "popping " << stacky.top() << "..." << endl << endl;
                stacky.pop();


                //  cout << "source code index is ---- " << index << endl << endl ;
                  //  cout << "top is  " << stack.top() << endl;
                  //cout << "table string  is:    " << table[indexRow][indexcolunm] << endl << endl;
               // cout << endl << endl << "index row: " << indexRow << "   indexcolunm: " << indexcolunm << endl << endl << endl;



                stack<string> tempStack3;

                for (int i = table[indexRow][indexcolunm].length() - 1; i >= 0; i--)
                { // disects the value of the table cells

                    temp += table[indexRow][indexcolunm][i]; // gather individidual character from cell value and concatenating it to temp

                    if (temp == "z") { // z stands for epsilon

                    }
                    else {

                        stacky.push(temp);

                    }
                    //cout << "pushing " << stacky.top() << " onto stack" << endl;


                    temp = ""; // clear the value of temp

                }// this is for for loop;

            }




        } // this is for while loop

        if (tempInput.empty() && !topStack.empty())
        {
            cout << endl << endl << "the end, input does not have $ symbol at the end, " << sourceCode << " cannot be determined. ";
        }
     }
    //cout << "yessss $$$$$$$$$$$$$$$$$$$$$$$" << stacky.top() << endl;


    //string okey = "";
    //okey = okey + sourceCode[stringIndex];

    //if (stacky.top() == okey) {

    //    cout << "yessss $$$$$$$$$$$$$$$$$$$$$$$" << stacky.top() << endl;



    //}

    //if (checkString(stacky.top())) {
    //    //  cout<<"yessss ||||||||||||||||||||||||||||||" << stack.top() << endl;

    //    stringIndex = 1 + stringIndex;
    //}


    //cout << "top of stack is " << stacky.top() << endl;

    ////         while (!stack.empty()) {
    ////              cout << ' ' << stack.top();
    ////              stack.pop();
    ////          }








    return 0;
}

//  a       +       -       *       /        (       )       $



int findColumn(string column) {

    int num = 0;


    if (column == "a") {
        num = 0;
    }
    else   if (column == "+") {
        num = 1;
    }
    else   if (column == "-") {
        num = 2;
    }

    else   if (column == "*") {
        num = 3;
    }

    else   if (column == "/") {
        num = 4;
    }

    else   if (column == "(") {
        num = 5;
    }
    else   if (column == ")") {
        num = 6;
    }
    else   if (column == "$") {
        num = 7;
    }
    else {

        num = 100;
        cout << "it is from tableColumn else part" << endl;
    }


    return num;
}




int findRow(string row) {





    int num = 0;


    if (row == "E") {
        num = 0;
    }
    else   if (row == "Q") {
        num = 1;
    }
    else   if (row == "T") {
        num = 2;
    }

    else   if (row == "R") {
        num = 3;
    }

    else   if (row == "F") {
        num = 4;
    }

    else {
        cout << endl << "INVALID input, string is not part of the language";
        return 100;
        
    }

    return num;





}




bool   checkString(string x)
{ // checks whether stringx is a terminal state return false if its is not a terminal

    string acceptedString[10] = { "a", "+", "-","*","/","(",")","$","z", "0"};// these are terminals


    for (int i = 0; i < 7; i++) {


        if (x == acceptedString[i]) {

            return  true;
        }

    }

    return false;
}






    char inputChar(string prompt, string listChars)
    {
        char input;
        do
        {
            cout << prompt;
            if (!(cin >> input))
            {
                cout << "\n\tERROR-1A: Invalid input. Must be a character type.\n";
                cin.clear();
                cin.ignore(999, '\n');
            }
            bool bfound = false;
            for (unsigned c = 0; c < listChars.length(); c++)
                if (toupper(listChars[c]) == toupper(input))
                {
                    bfound = true;
                    break;
                }
            if (!bfound)
            {
                cout << "\n\tERROR-2A: Invalid input. Must be a character from the list of '";
                cin.clear();
                cin.ignore(999, '\n');
                for (unsigned c = 0; c < listChars.length() - 1; c++)
                    cout << "'" << static_cast<char>(toupper(listChars[c])) << "', ";
                cout << "or '" << static_cast<char>(toupper(listChars.back())) << "'.\n";
            }
            else
                break;
        } while (true);
        return toupper(input);
    }
