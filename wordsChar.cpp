#include<iostream>
#include <cstring>
using namespace std;

struct word { // the definition of word struct
    char *text;
    word *nextWord;
};

void destroyList(word *head){ // optional function
    word* current = head;
    word* next;   
    while (current != NULL) {
        next = current->nextWord;
        delete[] current->text; // free the char * string
        delete current;
        current = next;
    }
}

void printList(word *head){ // optional function
    word *temp = head;
    while(temp != nullptr)
    {
        cout << temp->text << endl; 
        temp = temp->nextWord;
    } 
}

void add_word(word **head, int word_size, char* word_characters) {   
    // 1. allocate a new word in the heap
    word* new_word = new word(); 
    // 2. allocate an array of char with the exact needed # of chars 
    new_word->text = new char[word_size];
    strcpy(new_word->text, word_characters);
    new_word->nextWord = NULL;
    // 3. If the sentence is empty, 
    //    so the head point to the new created word 
    if (*head == NULL){ 
        *head = new_word;
    }else { // otherwise, put the new word at the end of the sentence
        word *temp = *head;
        while(temp->nextWord != NULL){
            temp = temp->nextWord;
        }
        temp->nextWord = new_word;
    }    
} 

char * replace_redundant_letter(char *w){
    bool is_redundant = false;
    char *r_word = new char[strlen(w)];      // make a copy of w to replace the redundant letters with *
    strcpy(r_word, w); // 
    // create a pointers to the r_word
    char *head_char = r_word; 
    //check if a letter and its consecutive letter are same
    while (head_char < r_word + strlen(r_word) - 2) {
        if ( *(head_char) == *(head_char + 1)){
            *(head_char + 1) = '*';
            is_redundant = true;
        }
        head_char ++; // move the head to the next char
    }
    if (is_redundant)
        return r_word; // return a pointer to the redundant word 
    delete[] r_word;   // else, deallocate the memory reserved for it
    r_word = NULL;     // nulling the pointer 
    return NULL;
}

word* words_with_redundant_letters(word *head)
{
    word *red_list = NULL; // create a pointer to the list containing words with redundant letters
    word *temp = head;
    char *r_word;
    while (temp != NULL) { // went through all the words in the head list
        r_word = replace_redundant_letter(temp->text);
        if(r_word != NULL) // check if the word contain *
        { 
            //insert the word containing redundant letters to the new red_list
            add_word(&red_list, strlen(temp->text), r_word);
        } 
        temp = temp->nextWord;
    }
    return red_list;
}

int main ()
{
    const int MAX_SIZE = 20;
    word *head = NULL;
    char str[MAX_SIZE]; // define an array of char with fixed size to hold the input stream from cin
    
    cout << "Introduce your sentence here, type '0' at the end of the sentence" << endl;
    while (cin >> str) {
        if (str[0] == '0') // you can use a different end symbol
            break;
        add_word(&head, strlen(str), str);
    }
    cout<<"The original  list contains:"<<endl;
    printList(head);
    cout<<"-----------------------------"<<endl;
    cout<<"The list containing word with redundant letters only:"<<endl;
    word* redundant = words_with_redundant_letters(head);
    printList(redundant);
    // Destroy the two lists
    destroyList(head);
    destroyList(redundant);
    head = NULL; redundant = NULL;  // nulling the pointer: optional at the end of a program as they are going to be destroyed auto from the stack
                                     // but this is a good practice because it prevents the pointer to points to memory that has been deallocated and can no longer be accessed safely
}