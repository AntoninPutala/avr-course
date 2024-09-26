
// Online C Compiler - Build, Compile and Run your C programs online in your favorite browser

#include<stdio.h>
#include<stdint.h>

uint8_t* stringInvertor(uint8_t*,uint8_t*);

uint8_t* stringInvertor(uint8_t* pString,uint8_t *pInvertedString)
{
    uint8_t i = 0;
    for (i; *(pString+i) != '\0'; i++);
    
    for (uint8_t j = 0; j < i; j++)
    {
        *(pInvertedString+j) = *(pString+i-j-1);
    }
    
    *(pInvertedString+i) = '\0';
    return pInvertedString;
}

int main()
{
    uint8_t string[] = "FERNETSTOCK";
    uint8_t *pString = &string[0];
    uint8_t InvertedString[50] = {0};
    uint8_t *pInvertedString = &InvertedString[0];
    
    pInvertedString = stringInvertor(pString, InvertedString);
    
    printf("%s\n",string);
    
    for (uint8_t i = 0; *(pInvertedString + i) != '\0'; i++)
    {
     printf("%c", *(pInvertedString+i));   
    }
    return 0; 
}
