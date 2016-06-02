#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<math.h>
#include<time.h>

#define maxWordSize 70
#define dictSize 236000


struct word
{
  char vocab[maxWordSize];
  double number;
};
struct ansArr
{
  char str[maxWordSize];
  int strLen;
  double value;
  struct ansArr *next;
};

/*char letterFrequency[] = "eothasinrdluymwfgcbpkvjqxz";
abcdefghijklmn
could set the prime number from small to big in this sequence to reduce the caluculation and memory*/
int reference[26] = {2,41,5,7,11,43,17,19,23,29,31,37,3,13,47,53,59,61,67,71,73,79,83,89,97,101};
struct word wordTable[dictSize];
void buildTable(char* buf,int count)
{
  int i = 0;
  double num = 1;
  char c;
  while((c=*(buf+i))!='\n'){
    wordTable[count].vocab[i] = tolower(c);
    num *= reference[tolower(c)-'a'];
    i++;
  }
  wordTable[count].vocab[i]='\0';
  wordTable[count].number = num;
}


void searchForAna(char* a, struct ansArr* answer, int dicNum, int* found)
{
  int i = 0;
  char c;
  int len = 0;
  *found = 0;
  double aNum = 1;
  struct ansArr* maxVal = answer;

  maxVal->next = NULL;
  maxVal->strLen = 0;

  while ((c = *(a + len)) != '\0')
  {
    aNum *= reference[tolower(c) -'a'];
    len++;
  }
  //printf("the number is %f\n", aNum);
  //printf("the word is %s\n", a);
  for (i=0; i<dicNum; i++)
  {
    if (fmod(aNum,(wordTable[i].number)) != 0) continue;
    else
    {
      char searchW[maxWordSize];
      strcpy(searchW, wordTable[i].vocab);
      int searchWlength = strlen(searchW);

      //if(strcmp(searchW, a)==0) continue; // if they are the same word
      if(*found == 0)
      {
        *found = 1;
        strcpy(maxVal->str, searchW);
        maxVal->strLen = searchWlength;
      }
      else
      {
        if((maxVal->strLen)>searchWlength) {continue;}

        else if ((maxVal->strLen)<searchWlength)
        {
          strcpy(maxVal->str, searchW);
          maxVal->strLen = searchWlength;
          maxVal->next = NULL;
        }
        else if ((maxVal->strLen) == searchWlength)
        {
          struct ansArr* temp = malloc(sizeof(struct ansArr));
          temp = maxVal;
          while (temp->next!=NULL){
            temp = temp->next;
          }
          temp->next = malloc(sizeof(struct ansArr));
          struct ansArr* nextAns = temp->next;
          strcpy(nextAns->str, searchW);
          nextAns->strLen = searchWlength;
          nextAns->next = NULL;
        }
      }
    }
  }
}

int main(int argc, char* argv[])
{
    clock_t begin, end;
    double timeSpent;
    if (argc <= 1) {printf("please input vocabulary.\n"); return -1;}
    int i;
    char * ana = malloc(sizeof(char)*maxWordSize) ;
    ana[0]='\0';
    for (i = 1; i < argc; i++){
        strcat(ana, argv[i]);
    }
    struct ansArr* answer = malloc(sizeof(struct ansArr));

    char* fileName = "dictionary.txt";
    char  buf[maxWordSize];
    FILE* fp = fopen(fileName, "r");
    if (fp == NULL)
    {
      perror("popen");
      return -1;
    }
    int count = 0;
    while (fgets(buf, maxWordSize, fp)) {
        buildTable(buf, count);
        count++;
    }
    fclose(fp);

    begin = clock();
    int* find = malloc(sizeof(int));
    searchForAna(ana, answer, count, find);
    end = clock();
    timeSpent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("the time for searching is %f\n",timeSpent);
    if (*find == 0) printf("no match\n");
    else
    {
      do{
        printf("the anagram is %s\n", answer->str);
        answer = answer->next;
      }while(answer!=NULL);
    }

    return 0;
}
