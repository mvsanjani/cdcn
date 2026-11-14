
#include <stdio.h>
#include <string.h>

// Perform CRC division
void crcDivision(char data[], char generator[], char remainder[])
{
    int dataLen = strlen(data);
    int genLen = strlen(generator);

    for (int i = 0; i <= dataLen - genLen; i++)
    {
        if (data[i] == '1')
        {
            for (int j = 0; j < genLen; j++)
            {
                if (data[i + j] == generator[j])
                    data[i + j] = '0';
                else
                    data[i + j] = '1';
            }
        }
    }

    strncpy(remainder, data + dataLen - genLen + 1, genLen - 1);
    remainder[genLen - 1] = '\0';
}

// Convert word into binary
void wordToBinary(char word[], char binary[])
{
    int k = 0;

    for (int i = 0; word[i] != '\0'; i++)
    {
        int ch = word[i];

        for (int j = 7; j >= 0; j--)
        {
            if (ch & (1 << j))
                binary[k++] = '1';
            else
                binary[k++] = '0';
        }
    }

    binary[k] = '\0';
}

int main()
{
    char word[100];
    char binary[1000];
    char paddedData[1100];
    char generator[] = "10011";
    char remainder[10];
    char transmitted[1100];
    char received[1100];
    char check[10];

    printf("Enter a word: ");
    scanf("%99s", word);

    // Convert word into binary
    wordToBinary(word, binary);

    printf("\nData in binary : %s", binary);
    printf("\nGenerator      : %s", generator);

    // Append zeros
    strcpy(paddedData, binary);

    int len = strlen(generator);

    for (int i = 0; i < len - 1; i++)
        strcat(paddedData, "0");

    // Calculate CRC
    crcDivision(paddedData, generator, remainder);

    printf("\nCRC Remainder  : %s", remainder);

    // Generate transmitted data
    strcpy(transmitted, binary);
    strcat(transmitted, remainder);

    printf("\nTransmitted Data: %s", transmitted);

    // Receive data
    strcpy(received, transmitted);

    // Check for errors
    crcDivision(received, generator, check);

    printf("\nReceiver Remainder: %s", check);

    if (strcmp(check, "0000") == 0)
        printf("\nNo Error Detected\n");
    else
        printf("\nError Detected\n");

    return 0;
}
