#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define limericksSize 5
#define size_wordsStock 29

const char* wordsStock[] = {
        "bill", "hill", "pill", "meal", "stamina", "bend", "defend", "demand", "rent", "pizza",
         "visa", "vodka", "badly", "sadly", "vividly", "portal", "normal", "sauna", "branch", "crunch",
         "Tarzan", "seaman", " woman", "ran", "man", "sand", "cargo", "Virgo", "receipt"
};

void PrintLimerick(char* arr[], int sz);
void getln(char** str);

int HaveSimilarEnding(char* str1, const char* str2, int num);
char* DeleteWord(char* str, int wordIndex);
char* InsertWord(char* str, int index, char* word);
char* ReplaceWord(char* str, char* word1, char* word2);

char* BuildRow0(char* row);
char* BuildRow1(char* row1, char* row0);
char* BuildRow2(char* row);
char* BuildRow3(char* row1, char* row0);
char* BuildRow4(char* row);


void main() {

    int indexRow;
    char* limerick[limericksSize];
    limerick[0] = "There was … from …";
    limerick[1] = "Who …";
    limerick[2] = "When he/she …";
    limerick[3] = "He/She …";
    limerick[4] = "… from ….";

    while(indexRow != -1)
    {
        PrintLimerick(limerick, limericksSize);
        printf("Enter index of row you want to fill (0-4) (-1 to exit) : ");
        scanf("%d", &indexRow);


        switch(indexRow) {
            case 0:
                limerick[0] = BuildRow0(limerick[0]);
                break;
            case 1:
                limerick[1] = BuildRow1(limerick[1], limerick[0]);
                break;
            case 2:
                limerick[2] = BuildRow2(limerick[2]);
                break;
            case 3:
                limerick[3] = BuildRow3(limerick[3], limerick[2]);
                break;
            case 4:
                limerick[4] = BuildRow4(limerick[0]);
                break;
            default:
                printf("You entered wrong value.");
                break;
        }
    }

}


        ///////////////////////////////// ************* Basic assembling functions ************* /////////////////////////////////


int HaveSimilarEnding(char* str1, const char* str2, int num)
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
    int wordsNum = 0;
    int charIndex = 0;
    int charIndexToDelete = 0;
    int i = 0;

    // count number of words in string //
    while(str[charIndex] !='\0')
    {
        if(str[charIndex]==' ')
        {
            wordsNum++;
        }
        if(wordsNum-1 == index && i == 0)
        {
            charIndexToDelete = charIndex+1;
            i++;
        }
        charIndex++;
    }

    if(wordsNum < index)
    {
        printf("There are only %d words in the sentence.", wordsNum+1);  // wordsNum is index, output is real num.
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
    int wordsNum = 0;
    int charIndex = 0;
    int charIndexToPutWord = 0;
    int i = 0;

    // count number of words in string //
    while(str[charIndex] !='\0')
    {
        if(str[charIndex]==' ')
        {
            wordsNum++;
        }
        if(wordsNum-1 == index && i == 0)
        {
            charIndexToPutWord = charIndex+1;
            i++;
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
        strcat(firstPart, word);
        strcat(firstPart, " ");
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


void PrintLimerick(char* arr[], int sz)
{
    int i;

    printf("\n\nMy Limerick:\n");
    for (i = 0; i < sz; i++)
        printf("%s.\n", arr[i]);

    printf("\n");
}

void getln(char** str)
{
       char ch;
       int i=0;
       while(ch != '\n')
      {
          ch = getchar();
          *str[i] = ch;
          i++;
          *str = realloc(*str,i*sizeof(char));
      }
      *str[i] = '\0';
}

        ///////////////////////////////// ************* Functions assigned to rows  ************* /////////////////////////////////

char* BuildRow0(char* row)
{
    int choice;
    char* before = "…";
    char* person = (char*)malloc(1*sizeof(char));
    char* origin = (char*)malloc(1*sizeof(char));
    char* rowAfter;
    printf("\nRow 0: %s.", row);

    printf("\nChoose who is the the lead character:\n"
           "0 - Young  man.\n"
           "1 - Old man.\n"
           "2 - Young lady.\n"
           "3 - Old lady.\n"
           "4 - Write yourself:\n");

    scanf("%d", &choice);

    switch(choice) {
        case 0:
            strcpy(person, "a young man");
            rowAfter = ReplaceWord(row, before, person);
            break;
        case 1:
            strcpy(person, "an old man");
            rowAfter = ReplaceWord(row, before, person);
            break;
        case 2:
            strcpy(person, "a young lady");
            rowAfter = ReplaceWord(row, before, person);
            break;
        case 3:
            strcpy(person, "an old lady");
            rowAfter = ReplaceWord(row, before, person);
            break;
        case 4:
            printf("\nWrite here: ");
            getln(&person);
            rowAfter = ReplaceWord(row, before, person);
            break;
        default:
            printf("\n You need to choose between 0-4.");
            return row;
    }

    printf("%s", rowAfter);
    printf("\n\nNow write here where he/she is from: ");
    getln(&origin);
    rowAfter = ReplaceWord(rowAfter, before, origin);

    free(person);
    free(origin);

    return rowAfter;
}

char* BuildRow1(char* row1, char* row0)
{
    char* before = "…";
    char* rhyme = (char*)malloc(1*sizeof(char));
    char* rowAfter;

    printf("\nFinish the sentence:\n %s \nSo it will rhyme with the previous sentence:\n %s", row0, row1);
    printf("\n\nHere's a list of suggestions you can end the sentence with:\n");

    for (int i = 1; i < size_wordsStock; i++)
    {
        int same = HaveSimilarEnding(row0, wordsStock[i], 1);
        if(same == 1)
        {
            printf("%s ,", wordsStock[i]);
        }
    }
    getln(&rhyme);
    rowAfter = ReplaceWord(row1, before, rhyme);
    free(rhyme);

    return rowAfter;
}

char* BuildRow2(char* row)
{
    char* before = "…";
    char* sentence = (char*)malloc(1*sizeof(char));
    char* rowAfter;

    rowAfter = DeleteWord(row, 0);

    printf("\nFinish the sentence:\n %s \n*Note that it needs to rhyme with the next row.\n", row);
    getln(&sentence);

    rowAfter = ReplaceWord(row, before, sentence);
    free(sentence);

    return rowAfter;
}

char* BuildRow3(char* row1, char* row0)
{
    char* before = "…";
    char* sentence = (char*)malloc(1*sizeof(char));
    char* rowAfter;

    rowAfter = DeleteWord(row1, -1);

    printf("\nFinish the sentence:\n %s \nSo it will rhyme with the previous sentence:\n %s", row1, row0);
    getln(&sentence);

    int same = HaveSimilarEnding(row0, row1, 1);

    if(same == 1)
    {
        rowAfter = ReplaceWord(row1, before, sentence);
        free(sentence);
        return rowAfter;

    }
    else
    {
        printf("The two sentences don't rhyme.");
        free(sentence);
        return row1;

    }
}

char* BuildRow4(char* row)
{
    char* before = "…";
    char* sentence = (char*)malloc(1*sizeof(char));
    char* rowAfter;

    rowAfter = DeleteWord(row, -1);
    rowAfter = DeleteWord(rowAfter, 0);

    printf("Write a a begining that fits the sentence: \n%s \n*Note it's the first sentence with a new beginning.\n", rowAfter);
    getln(&sentence);

    rowAfter = InsertWord(rowAfter, 0, sentence);
    free(sentence);

    return rowAfter;

}

