#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    if(argc != 2)
    {
        printf("Usage: ./substitution key \n");
        return 1;
    }

    string key = argv[1];

    for(int i = 0; i < strlen(key); i++)
    {
        if(!isalpha(key[i]))
        {
            printf("Usage: ./substitution key \n");
            return 1;
        }
    }

    if(strlen(key) != 26)
    {
        printf("Key must contain 26 characters \n");
        return 1;
    }

    // determine is the code is unique
    for(int i = 0; i < strlen(key); i++)
    {
        for(int j = i + 1; j < strlen(key); j++)
        {
            if(toupper(key[i]) == toupper(key[j]))
            {
                printf("code must only contain unique letters.\n");
                return 1;
            }
        }
    }

     string plaintext = get_string("plaintext:  ");

     // convert all key characters to uppercase for math

    for(int i = 0; i < strlen(key); i++)
    {
        if(islower(key[i]))
        {
            key[i] = key[i] - 32;
        }
    }



    printf("ciphertext: ");

    for(int i = 0; i < strlen(plaintext); i++)
    {
        if(isupper(plaintext[i]))
        {
            int letter = plaintext[i] - 65;
            printf("%c", key[letter]);
        }
        else if(islower(plaintext[i]))
        {
            int letter = plaintext[i] - 97;
            printf("%c", key[letter] + 32);
        }
        else printf("%c", plaintext[i]);
    }
    printf("\n");

}

