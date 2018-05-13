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
char* BuildRow3(char* row3, char* row2);
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
                fflush(stdin);
                limerick[0] = BuildRow0(limerick[0]);
                break;
            case 1:
                fflush(stdin);
                limerick[1] = BuildRow1(limerick[1], limerick[0]);
                break;
            case 2:
                fflush(stdin);
                limerick[2] = BuildRow2(limerick[2]);
                break;
            case 3:
                fflush(stdin);
                limerick[3] = BuildRow3(limerick[3], limerick[2]);
                break;
            case 4:
                fflush(stdin);
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
    char *pos = strstr(str, word1);
    int wordStartingIndex = pos-str;
    int lengthWord1 = strlen(word1);
    int lengthWord2 = strlen(word2);
    int lengthStr = strlen(str);

    if(pos != 0)
    {
        char* newStr = malloc(lengthStr + lengthWord2 - lengthWord1);
        memcpy(newStr, str, wordStartingIndex );
        memcpy(newStr+wordStartingIndex, word2, lengthWord2 );
        memcpy(newStr+wordStartingIndex+lengthWord2, str+wordStartingIndex+lengthWord1, lengthStr-lengthWord1-wordStartingIndex);
        return newStr;
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
       char ch = 0;
       int i=0;
       *str = malloc(10*sizeof(char));
       while(ch != '\n')
      {
          ch = getchar();
          if(ch != '\n')
              (*str)[i] = ch;
          if(++i % 10 == 0)
            *str = realloc(*str,(i+10)*sizeof(char));
      }
    (*str)[i] = '\0';
}

        ///////////////////////////////// ************* Functions assigned to rows  ************* /////////////////////////////////

char* BuildRow0(char* row)
{
    int choice;
    char* person;
    char* origin;
    char* rowAfter;
    printf("\nRow 0: %s.", row);

    printf("\nChoose who is the the lead character:\n"
           "0 - Young man.\n"
           "1 - Old man.\n"
           "2 - Young lady.\n"
           "3 - Old lady.\n"
           "4 - Write yourself:\n");

    scanf("%d", &choice);
    getchar();
    switch(choice) {
        case 0:
            rowAfter = ReplaceWord(row, "…", "a young man");
            break;
        case 1:
            rowAfter = ReplaceWord(row, "…", "an old man");
            break;
        case 2:
            rowAfter = ReplaceWord(row, "…", "a young lady");
            break;
        case 3:
            rowAfter = ReplaceWord(row, "…", "an old lady");
            break;
        case 4:
            printf("\nWrite here: ");
            getln(&person);
            rowAfter = ReplaceWord(row, "…", person);
            free(person);
            break;
        default:
            printf("\n You need to choose between 0-4.");
            return row;
    }

    printf(rowAfter);
    printf("\nNow write here where he/she is from: ");

    getln(&origin);
    rowAfter = ReplaceWord(rowAfter, "…", origin);
    free(origin);

    return rowAfter;
}

char* BuildRow1(char* row1, char* row0)
{
    char* rhyme;
    char* rowAfter;

    printf("\nFinish the sentence:\n %s \nSo it will rhyme with the previous sentence:\n %s", row1, row0);
    printf("\n\nHere's a list of suggestions you can end the sentence with:\n");

    for (int i = 1; i < size_wordsStock; i++)
    {
        int same = HaveSimilarEnding(row0, wordsStock[i], 1);
        if(same == 1)
        {
            printf("%s ,", wordsStock[i]);
        }
    }
    printf("\n");
    getchar();
    getln(&rhyme);

    int same = HaveSimilarEnding(row0, rhyme, 1);

    if(same == 1)
    {
        rowAfter = ReplaceWord(row1, "…", rhyme);
        free(rhyme);
        return rowAfter;

    }
    else
    {
        printf("The two sentences don't rhyme.");
        free(rhyme);
        return row1;

    }
}

char* BuildRow2(char* row)
{
    char* sentence;
    char* rowAfter;

    rowAfter = DeleteWord(row, 0);

    printf("\nFinish the sentence:\n %s \n*Note that it needs to rhyme with the next row.\n", row);
    printf("Your sentence before editing:\n %s\nWrite here:\n", rowAfter);
    getchar();
    getln(&sentence);

    rowAfter = ReplaceWord(rowAfter, "…", sentence);
    free(sentence);

    return rowAfter;
}

char* BuildRow3(char* row3, char* row2)
{
    char* sentence;
    char* rowAfter;

    printf("\nWrite the sentence from the beginning:\n %s \nSo it will rhyme with the previous sentence:\n %s", row3, row2);
    printf("\nWrite here:\n");
    getchar();
    getln(&sentence);

    int same = HaveSimilarEnding(row2, sentence, 1);

    if(same == 1)
    {
        rowAfter = ReplaceWord(row3, "He/She …", sentence);
        free(sentence);
        return rowAfter;

    }
    else
    {
        printf("The two sentences don't rhyme.");
        free(sentence);
        return row3;

    }
}

char* BuildRow4(char* row)
{
    char* sentence;
    char* rowAfter;
    char* rowAfter1;

    rowAfter = ReplaceWord(row, "There was", "…");
    rowAfter1 = DeleteWord(rowAfter, 0);


    printf("\nWrite a beginning that fits the sentence: \n%s \n*Note it's the first sentence with a new beginning.\n", rowAfter1);
    getchar();
    getln(&sentence);

    rowAfter1 = ReplaceWord(rowAfter1, "…", sentence);
    free(sentence);

    return rowAfter1;

}

