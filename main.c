#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int HaveSimilarEnding(char* str1, char* str2, int num);
char* DeleteWord(char* str, int index);
char* InsertWord(char* str, int index, char* word);
char* ReplaceWord(char* str, char* word1, char* word2);


void main() {

    //**** testing ****//

    char string[] = "Hello my name is nikita and I am a programmer";
    char string2[] = "good";
    char string3[] = "I am programmer";

    char* stringOut = InsertWord(string, 9, string2);
    char* stringOut3 = DeleteWord(string, 2);
    int boolean = HaveSimilarEnding(string2, string, 2);
    int boolean2 = HaveSimilarEnding(string3, string, 4);
    char* stringOut4 = ReplaceWord(string, "nikita", "david");

    printf("\n InsertWord: \n%s\n", stringOut);
    printf("\n DeleteWord: \n%s\n", stringOut3);
    printf("\n is similar: %d", boolean);
    printf("\n is similar: %d\n", boolean2);
    printf("\n ReplaceWord: \n%s\n", stringOut4);


}


int HaveSimilarEnding(char* str1, char* str2, int num)
{
    int isSame = 0;
    int i;
    int lenStr1 = strlen(str1);
    int lenStr2 = strlen(str2);

    for(i=1 ; i<=num ; i++)
    {
        if(str1[lenStr1-i] == str2[lenStr2-i])
            isSame++;
    }

    if(isSame == num)
        return 1;

    return 0;
}

char* DeleteWord(char* str, int index)
{
    int wordsNum = 1;
    int charIndex = 0;
    int charIndexToDelete;
    int i = 0;

    // count number of words in string //
    while(str[charIndex] !='\0')
    {
        if(str[charIndex]==' ')
        {
            wordsNum++;
        }
        if(wordsNum == index && i == 0)
        {
            charIndexToDelete = charIndex+1;
            i++;
        }
        charIndex++;
    }

    if(wordsNum < index)
    {
        printf("There are only %d words in the sentence.", wordsNum);
        return str;
    }

    // delete chosen word //
    else
    {
        char* newStr = (char*)malloc((strlen(str))*sizeof(char));
        strncpy ( newStr, str, strlen(str) );

        while(newStr[charIndexToDelete] != ' ' && newStr[charIndexToDelete] != '\0'){
            memmove(&newStr[charIndexToDelete], &newStr[charIndexToDelete + 1], strlen(newStr) - charIndexToDelete);
        }
        // delete extra space //
        if(newStr[charIndexToDelete-1] == ' ' && newStr[charIndexToDelete] == ' ')
        {
            memmove(&newStr[charIndexToDelete], &newStr[charIndexToDelete + 1], strlen(newStr) - charIndexToDelete);
        }
        return newStr;
    }

}

char* InsertWord(char* str, int index, char* word)
{
    int wordsNum = 1;
    int charIndex = 0;
    int charIndexToPutWord;


    // count number of words in string //
    while(str[charIndex] !='\0')
    {
        if(str[charIndex]==' ')
        {
            wordsNum++;
        }
        if(wordsNum == index)
        {
            charIndexToPutWord = charIndex+1;
        }
        charIndex++;
    }

    if(wordsNum < index)
    {
        printf("There are only %d words in the sentence.", wordsNum);
    }

    else
    {
        // allocating new dynamic memory for temporary strings to work with ('firstPart' gets extra 20 for the extra word) //
        char* firstPart = (char*)malloc((charIndex+20)*sizeof(char));
        char* secondPart = (char*)malloc((charIndex - charIndexToPutWord)*sizeof(char));

        // filling the new strings with parts of the original string //
        strncpy ( firstPart, str, charIndexToPutWord );
        strncpy ( secondPart, str + charIndexToPutWord, charIndex - charIndexToPutWord);

        // building the new string to send forward //
        strcat(firstPart, " ");
        strcat(firstPart, word);
        strcat(firstPart, secondPart);

        free(secondPart);

        return firstPart;
    }

    return str;
}

char* ReplaceWord(char* str, char* word1, char* word2)
{
    int charIndex = 0;
    char *pos = strstr(str, word1);
    int wordEndingIndex;
    int wordStartingIndex = pos-str;
    int lengthWord1 = strlen(word1);
    int lengthCounter = 0;

    if (pos != NULL)
    {
        // finding 'str' length and 'word1' ending index (starting index will not suffice) //
        while(str[charIndex] !='\0')
        {
            if(wordStartingIndex <= charIndex && lengthCounter <= lengthWord1)
            {
                wordEndingIndex = charIndex;
                lengthCounter++;
            }
            charIndex++;
        }

        // allocating new dynamic memory for temporary strings to work with //
        char* firstPart = (char*)malloc((charIndex+10)*sizeof(char));
        char* secondPart = (char*)malloc((charIndex)*sizeof(char));

        // filling the new strings with parts of the original string //
        strncpy ( firstPart, str, wordStartingIndex );
        strncpy ( secondPart, str + wordEndingIndex, charIndex - wordEndingIndex);

        // building the new string to send forward //
        strcat(firstPart, word2);
        strcat(firstPart, secondPart);

        free(secondPart);

        return firstPart;
    }

    else
    {
        printf("|%s| is not a sub-string\n", word1);
        return str;
    }
}



