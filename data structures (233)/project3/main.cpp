/* @Author
 * Student Name: Muhammet Uçan * Student ID: 150140707
 * Date: 23.12.2016
 */

#include <iostream>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <limits.h>
#include <math.h>
#include "stack.h"
#include "queue.h"
using namespace std;

// function for handling newline character for all operating systems
std::istream& safeGetline(std::istream& is, std::string& t)
{
    t.clear();
    
    std::istream::sentry se(is, true);
    std::streambuf* sb = is.rdbuf();
    
    for(;;) {
        int c = sb->sbumpc();
        switch (c) {
            case '\n':
                return is;
            case '\r':
                if(sb->sgetc() == '\n')
                    sb->sbumpc();
                return is;
            case EOF:
                // Also handle the case when the last line has no line ending
                if(t.empty())
                    is.setstate(std::ios::eofbit);
                return is;
            default:
                t += (char)c;
        }
    }
}

string operators[11] = {"abs", "sqrt" , "sub" , "div" , "exp" , "log" , "mod" , "sum" , "product" , "min" , "max"};

long sub(int n1, int n2) {
    return n1 - n2;
}
long _div(int n1, int n2) {
    return n1 / n2;
}
long exp(int x, int n) {
    return pow(x, n);
}
long log(int x, int n) {
    return log(n) / log(x);
}
long mod(int n) {
    return fmod(n, 10);
}
long mod(int x, int n) {
    return fmod(n, x);
}
long sum(int num[], int size) {
    int sum = 0;
    for (int i=0; i<size; i++) sum += num[i];
    return sum;
}
long product(int num[], int size) {
    int product = 1;
    for (int i=0; i<size; i++) product *= num[i];
    return product;
}
long min(int num[], int size) {
    int min = num[0];
    for (int i = 1; i<size; i++) {if (min > num[i]) min = num[i];}
    return min;
}
long max(int num[], int size) {
    int max = num[0];
    for (int i = 1; i<size; i++) if (max < num[i]) max = num[i];
    return max;
}

bool isOperator(string s){
    bool isOp = false;
    for(int i=0;i<11;i++) {
        if(strcmp(s.c_str(), operators[i].c_str()) == 0) isOp = true;
    }
    return isOp;
}
bool isLeftPara(string s) {
    return (strcmp(s.c_str(), "(") == 0);
}
bool isRightPara(string s) {
    return (strcmp(s.c_str(), ")") == 0);
}
bool isDigit(string s) {
    return s.find_first_not_of( "-0123456789ansinf" ) == string::npos; // ans ve inf yüzünden kombinasyonları da sayı olarak görünüyor asn ifn gibi
}
// my own toString function, thanks to not having c++11 support
string toString(int x) {
    stringstream ss;
    ss << x;
    string s;
    ss >> s;
    return s;
}

void evaluate(string str, Queue *queue,bool print) {
    Stack stack;
    stack.create();
    string token;
    istringstream sstream(str);
    long result = 0;
    static long ans = 0;
    // checking whether it correct syntax or operator is valid
    bool validOperator = true;
    bool syntaxErr = false;
    bool operatorPushed = false;
    srand( static_cast<unsigned int>(time(NULL)));
    
    // turning prefix to postfix
    string postfix;
    int lCount = 0, rCount = 0;
    int numOfLeftPara = 0, numOfRightPara = 0;
    while (getline(sstream, token, ' ')) {
        if(!isDigit(token) && !isLeftPara(token) && !isRightPara(token) && !isOperator(token))  {
            validOperator = false;
            if (token.find_first_of(".") != string::npos || token.find_first_of(",") != string::npos) cout << "Only use integers!" <<  endl << endl;
            else cout << "There is no operation like: " << token << ", try again!" <<  endl << endl;
        }
        else if(isOperator(token)) {
            stack.push(token);
            operatorPushed = true;
        }
        else if (isRightPara(token)) {
            postfix.append(stack.pop());
            postfix.append(" ) ");
            numOfRightPara++;
        }
        else {
            postfix.append(token);
            postfix.append(" ");
            operatorPushed ? rCount++ : lCount++ ;
            if (isLeftPara(token)) { rCount = 0; lCount = 0; operatorPushed = false; numOfLeftPara++;}
        }
    }
    while (!stack.isEmpty()) {
        postfix.append(stack.pop());
        postfix.append(" ");
    }
    if (validOperator && (lCount >= rCount || numOfLeftPara != numOfRightPara)) {syntaxErr = true;}
    if (print && validOperator && !syntaxErr) {
        cout << endl << "Postfix string: ";
        for (int i=0; i<str.length(); i++) cout << postfix[i];
    }
    
    // evaluating postfix form
    istringstream ss(postfix);
    while (getline(ss, token, ' ')) {
        // if operator
        if (isOperator(token)) {
            if (strcmp(token.c_str(), "abs") == 0) {
                if (stack.top().compare("inf") == 0 || stack.top().compare("-inf") == 0) { result = LONG_MAX; stack.pop();}
                else result = abs(atol(stack.pop().c_str()));
            }
            else if (strcmp(token.c_str(), "sqrt") == 0) {
                if (stack.top().compare("inf") == 0) { result = LONG_MAX; stack.pop(); }
                else if (atoi(stack.top().c_str()) >= 0) result = sqrt(atol(stack.pop().c_str()));
                else syntaxErr = true;
            }
            else if (strcmp(token.c_str(), "min") == 0) {
                bool nInf = false;
                int num[15];
                int i=0;
                while (!stack.isEmpty() && isDigit(stack.top())) {
                    if (stack.top().compare("inf") == 0) {i--; stack.pop();}
                    else if (stack.top().compare("-inf") == 0) {nInf = true; stack.pop();}
                    else if (!stack.isEmpty()) num[i] = atoi(stack.pop().c_str());
                    i++;
                }
                if (!nInf) result = min(num, i);
                else result = LONG_MIN;
            }
            else if (strcmp(token.c_str(), "max") == 0) {
                bool pInf = false;
                int num[15];
                int i=0;
                while (!stack.isEmpty() && isDigit(stack.top())) {
                    if (stack.top().compare("inf") == 0) {pInf = true; stack.pop();}
                    else if (stack.top().compare("-inf") == 0) {i--; stack.pop();}
                    else if (!stack.isEmpty()) num[i] = atoi(stack.pop().c_str());
                    i++;
                }
                if (!pInf) result = max(num, i);
                else result = LONG_MAX;
            }
            else if (strcmp(token.c_str(), "exp") == 0) {
                if (stack.top().compare("inf") == 0 || (!stack.isEmpty() && isDigit(stack.top()) && stack.head->next && stack.head->next->data.compare("inf") == 0)) {
                    result = LONG_MAX;
                    stack.pop();
                    if (!stack.isEmpty() && isDigit(stack.top())) stack.pop();
                }
                else {
                    int second = atoi(stack.pop().c_str());
                    result = exp(second);
                    
                    if (!stack.isEmpty() && isDigit(stack.top())) {
                        result = exp(atoi(stack.pop().c_str()), second);
                    }
                }
            }
            else if (strcmp(token.c_str(), "log") == 0) {
                if (stack.top().compare("inf") == 0 || (!stack.isEmpty() && isDigit(stack.top()) && stack.head->next && stack.head->next->data.compare("inf") == 0)) {
                    result = LONG_MAX;
                    stack.pop();
                    if (!stack.isEmpty() && isDigit(stack.top())) stack.pop();
                }
                else {
                    int second = atoi(stack.pop().c_str());
                    if (1 > second) syntaxErr = true;
                    else {
                        result = log(second);
                        cout << result;
                        if (!stack.isEmpty() && isDigit(stack.top())) {
                            result = log(atoi(stack.pop().c_str()), second);
                        }
                    }
                }
            }
            else if (strcmp(token.c_str(), "div") == 0) {
                int second;
                if (stack.top().compare("inf") == 0 || stack.top().compare("-inf") == 0) result = 0;
                else {
                    second = atoi(stack.pop().c_str());
                    if (second == 0) syntaxErr = true;
                    else {
                        
                        if (stack.top().compare("inf") == 0) result = LONG_MAX;
                        else if (stack.top().compare("-inf") == 0) result = LONG_MIN;
                        else result = _div(atoi(stack.pop().c_str()), second);
                    }
                }
                
            }
            else if (strcmp(token.c_str(), "mod") == 0) {
                if (stack.top().compare("inf") == 0 || (!stack.isEmpty() && isDigit(stack.top()) && stack.head->next && stack.head->next->data.compare("inf") == 0)) {
                    result = LONG_MAX;
                    stack.pop();
                    if (!stack.isEmpty() && isDigit(stack.top())) stack.pop();
                }
                else {
                    int second = atoi(stack.pop().c_str());
                    result = mod(second);
                    if (!stack.isEmpty() && isDigit(stack.top())) {
                        result = mod(atoi(stack.pop().c_str()), second);
                    }
                }
            }
            else if (strcmp(token.c_str(), "product") == 0) {
                bool pInf = false, nInf = false;
                int num[15];
                int i=0;
                while (!stack.isEmpty() && isDigit(stack.top())) {
                    if (stack.top().compare("inf") == 0) pInf = true;
                    else if (stack.top().compare("-inf") == 0) nInf = true;
                    num[i] = atoi(stack.pop().c_str());
                    i++;
                }
                if (!pInf && !nInf) result = product(num, i);
                else if (pInf) result = LONG_MAX;
                else if (nInf) result = LONG_MIN;
            }
            else if (strcmp(token.c_str(), "sub") == 0) {
                if (stack.top().compare("inf") == 0 || stack.top().compare("-inf") == 0 || (!stack.isEmpty() && isDigit(stack.top()) && stack.head->next->data.compare("inf") == 0) || (!stack.isEmpty() && isDigit(stack.top()) && stack.head->next->data.compare("-inf") == 0)) {
                    result = LONG_MAX;
                    stack.pop();
                    stack.pop();
                }
                else {
                    int second = atoi(stack.pop().c_str());
                    result = sub(atoi(stack.pop().c_str()), second);
                }
            }
            else if (strcmp(token.c_str(), "sum") == 0) {
                bool pInf = false, nInf = false;
                int num[15];
                int i=0;
                while (!stack.isEmpty() && isDigit(stack.top())) {
                    if (stack.top().compare("inf") == 0) pInf = true;
                    else if (stack.top().compare("-inf") == 0) nInf = true;
                    num[i] = atoi(stack.pop().c_str());
                    i++;
                }
                if (!pInf && !nInf) result = sum(num, i);
                else if (pInf) result = LONG_MAX;
                else if (nInf) result = LONG_MIN;
            }
            
            // if there is ans from former calculations push it to the stach
            if (!stack.isEmpty() && isLeftPara(stack.top())) stack.pop();
            if (result == LONG_MAX) stack.push("inf");
            else if (result == LONG_MIN) stack.push("-inf");
            else stack.push(toString((int)result));
            
        } // if either number or left or right paranthesis
        else if (isDigit(token) || isLeftPara(token)) {
            if (!queue->isEmpty()) {
                if (strcmp(token.c_str(), "ans") == 0) {
                    if (ans == LONG_MAX) {
                        token.replace(0, 3, "inf");
                    }
                    else if (ans == LONG_MIN) {
                        token.replace(0, 3, "-inf");
                    }
                    else {
                        token.replace(0,3,toString((int)ans));
                    }
                }
            }
            stack.push(token);
        }
    }
    
    if (print && validOperator && !syntaxErr) {
        if (result == LONG_MIN ) cout << endl << "Answer: -inf" << endl << endl;
        else if (result == LONG_MAX)  cout << endl << "Answer: inf" << endl << endl;
        else cout << endl << "Answer: " << result << endl << endl;
    }
    else if (syntaxErr) {
        cout << endl << "Syntax Error!" << endl << endl;
    }
    
    if (validOperator && !syntaxErr) ans = result;
    if (validOperator && !syntaxErr) queue->enqueue((long)result);
}

int main(int argc, char *argv[]) {
    Queue queue;
    queue.create();
    bool cont = true;
	
	string str;
    
    if (argc > 1) {
        ifstream file (argv[1]);
        cont = false;
        cout << endl;
        // in order to get rid of gibberish end line character or unwanted characaters str size should be larger than 5, min amount of char for a valid calculation,
        while (safeGetline(file,str) && str.size() >= 5) {
            evaluate(str,&queue,false);
        }
    }
    if (cont) cout << endl << "Initializing the interpreter..." << endl << endl;
    while (cont) {
        cout << ">> ";
        getline(cin,str);
        if (strcmp(str.c_str(), "exit") == 0) {
            cout << endl << "Terminating the interpreter..." << endl;
            break;
        }
        evaluate(str,&queue,true);
    }
    
    cout << "Answer queue: ";
    while (!queue.isEmpty()) {
        
        if (queue.first() == LONG_MAX) {
            cout << "inf" << " -> ";
            queue.dequeue();
        } else if (queue.first() == LONG_MIN) {
            cout << "-inf" << " -> ";
            queue.dequeue();
        } else {
            cout << queue.dequeue();
            if (!queue.isEmpty()) cout << " -> ";
        }
        
    }
    cout << endl << endl;
    return 0;
}
