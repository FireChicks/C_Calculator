#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <string.h>

#define MAXSIZE 50

#pragma warning(disable : 4996)



struct stack

{

    int number;

    struct stack* link;

};



struct stack* newNode();

void push(int inp);

void insertPostFix(char input, char* postFix);

int pop();



int stackIsNull();

int isSymbol(char inputChar);

void checkPriority(char inputChar, char* postFIx);

int acc(int operand1, int operand2, char operator);

//int parsing(char* postFix);

int parseInt(char inp);

int isNumber(char inp);


int pfIndex = 0;

int index = -1;

int preIndex[5];

int preIndexIndex = -1;

int opIndex = 0;



struct stack* top = NULL;

struct stack firstNode;





void main() {

    char* s1 = malloc(sizeof(char) * MAXSIZE);

    char* postFix = malloc(sizeof(char) * MAXSIZE);

    int parsingOperand[30] = { 0, };

    int j = 0;

    char temp = 0;



    scanf("%s", s1);



    for (int i = 0; i < MAXSIZE; i++) {



        if (s1[i] == '\0') {

            break;

        }



        if (isSymbol(s1[i])) {

            checkPriority(s1[i], postFix);



        }

        else {

            insertPostFix(s1[i], postFix);

        }

    }


    for (int i = 0; i < MAXSIZE; i++) {

        if (index == -1) {

            break;

        }

        temp = pop();

        if (temp == '(') {

            continue;

        }
        insertPostFix(temp, postFix);
    }
    printf("%s\n", postFix);

    for (int i = 0; i < strlen(postFix); i++) {
        if (isNumber(postFix[i])) {
            parsingOperand[opIndex++] = parseInt(postFix[i]);
        }
        else {
            opIndex--;
            parsingOperand[opIndex - 1] = acc(parsingOperand[(opIndex - 1)], parsingOperand[opIndex], postFix[i]);
        }

    }
    printf("%d", parsingOperand[0]);



    free(s1);

    free(postFix);

}



struct stack* newNode() {

    return malloc(sizeof(struct stack));

}



int stackIsNull() {

    if (top == NULL) {

        return 1;

    }

    else {

        return 0;

    }

}



int isSymbol(char inputChar) {

    if (inputChar == '(' || inputChar == ')') {

        if (inputChar == '(') {

            preIndex[preIndexIndex++] = index;

        }

        return 3;

    }

    else if (inputChar == '*' || inputChar == '/' || inputChar == '%') {

        return 2;

    }

    else if (inputChar == '+' || inputChar == '-') {

        return 1;

    }
    else {

        return 0;

    }

}



void checkPriority(char inputChar, char* postFix) {

    char temp;

    if (stackIsNull()) {

        if (inputChar == ')') {

            return;

        }

        push(inputChar);

        return;

    }



    char preChar = top->number;



    if (inputChar == ')') {

        if (index != preIndex[preIndexIndex]) {

            for (int i = index; i >= preIndex[preIndexIndex]; i--) {

                temp = pop();

                if (temp == '(') {

                    continue;

                }

                insertPostFix(temp, postFix);

            }

        }

        preIndexIndex--;

        return;

    }





    if (preChar == '(') {
        push(inputChar);
        return;

    }



    else if (isSymbol(preChar) == 2) { //이전 연산자가 *, /, %일때

        if (isSymbol(inputChar) == 3 || isSymbol(inputChar) == 2) //연산순위가 같을 때

        {
            push(inputChar);
            return;



        }
        else if (isSymbol(inputChar) == 1) {    //연산순위가 낮을 때
            insertPostFix(pop(), postFix);
            push(inputChar);
            return;

        }

    }

    else if (isSymbol(preChar) == 1) {
        push(inputChar);
        return;

    }

    else {
        insertPostFix(pop(), postFix);
        return;
    }





}

int acc(int operand1, int operand2, char operator) {
    if (operator == '*') {
        return operand1 * operand2;
    }
    else if (operator == '/') {
        return operand1 / operand2;
    }
    else if (operator == '%') {
        return operand1 % operand2;
    }
    else if (operator == '-') {
        return operand1 - operand2;
    }
    else if (operator == '+') {
        return operand1 + operand2;
    }
    else
    {
        printf("연산자가 이상합니다.");
        return;
    }
}

int parseInt(char inp) {
    if (inp >= 48 || inp <= 57) {
        return inp - 48;
    }
    else {
        printf("넣은 문자가 숫자가 아닙니다.");
        return;
    }


}

int isNumber(char inp) {
    if (inp >= 48 && inp <= 57) {
        return 1;
    }
    else {
        return 0;
    }
}








void push(int inp) {
    if (stackIsNull()) {
        top = &firstNode;
        firstNode.number = inp;
        index++;
    }
    else {
        top->link = newNode();
        top = top->link;
        top->number = inp;
        index++;
    }
}

int pop() {
    struct stack* tempNode = &firstNode;
    int temp;
    if (stackIsNull()) {
        printf("스택이 비어있습니다.\n");
        return 0;
    }
    else {
        if (&top->number == &firstNode.number) {
            top = NULL;
            temp = firstNode.number;
            firstNode.number = NULL;
            firstNode.link = NULL;
            index--;
            return temp;
        }
        for (int i = 0; i < index; i++) {
            if (i == (index - 1)) {
                top = tempNode;
            }
            tempNode = tempNode->link;
        }
        index--;
        int output = tempNode->number;
        tempNode = top;
        free(top->link);
        return output;
    }
}

void insertPostFix(char input, char* postFix) {



    if (pfIndex > (MAXSIZE - 2)) {

        printf("최대 입력가능한 개수를 초과했습니다.");

        return;

    }



    postFix[pfIndex++] = input;

    postFix[pfIndex] = '\0';

    return;

}