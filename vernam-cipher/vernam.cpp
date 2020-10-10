#include <bits/stdc++.h>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

#define MAX 1000

char key[MAX];
char hexa[MAX];
char buf[MAX];
int ptr = 0;

//function to read from a file
void fread(char fname[], char data[])
{
    ifstream in;
    in.open(fname);
    int i = 0; char ch;

    //reading the file char by char
    while (!in.eof())
    {
        in.get(ch);
        data[i++] = ch;
    }

    data[i-1] = '\0';
    in.close();
}

//function to write into file
void fwrite(char fname[], char data[])
{
    ofstream out;
    out.open(fname);
    int i = 0;

    //write into file char by char
    while (data[i] != '\0')
        out.put(data[i++]);

    out.close();
}

//function to convert to hex codes
void hexcode(int n)
{
    //counter for hexadecimal number array
    int i = 0;
    while(n!=0)
    {
        // temporary variable to store remainder
        int temp  = 0;

        // storing remainder in temp variable.
        temp = n % 16;

        // check if temp < 10
        if(temp < 10)
        {
            buf[i] = temp + 48;
            i++;
        }
        else
        {
            buf[i] = temp + 55;
            i++;
        }

        n = n/16;
    }
    buf[i] = '\0';
}

//function that generates a random key of length n
void genkey(int n)
{
    srand(time(0));

    for(int i = 0; i < n; i++)
    {
        int choose = rand() % 2;
        int p = rand() % 26;

        if(choose)
            key[i] = (char)(65 + p);
        else
            key[i] = (char)(97 + p);
    }
    key[n] = '\0';
}

//function to print binary representation of a string
void binary(char data[])
{
    int n = strlen(data);

    for (int i = 0; i < n; ++i)
    {
        int cur = data[i];
        int bin[7];

        for (int j = 0; j < 7; ++j)
        {
            bin[j] = cur%2;
            cur /= 2;
        }

        for (int j = 6; j >= 0; --j)
            cout<<bin[j]<<' ';
        cout<<'\n';
    }
}

void encrypt(char data[])
{
    int n = strlen(data);
    cout<<"Randomly generated key: "<<key<<"\n";

    cout<<"\nPlaintext in ASCII:\n";
    binary(data);

    cout<<"\nRandomly generated key in ASCII:\n";
    binary(key);

    cout<<"\n\nGenerated Ciphertext in ASCII:\n";

    //generating cipher text by XOR
    for (int i = 0; i < n; ++i)
        data[i] = data[i] ^ key[i];

    binary(data);
}

void decrypt(char data[])
{
    int n = strlen(data);
    cout<<"Randomly generated key: "<<key<<"\n";

    cout<<"\nCiphertext in ASCII:\n";
    binary(data);

    cout<<"\nRandomly generated key in ASCII:\n";
    binary(key);

    //generating cipher text by XOR
    for (int i = 0; i < n; ++i)
        data[i] = data[i] ^ key[i];

    cout<<"\n\nRecovered Plaintext in ASCII:\n";
    binary(data);
}

int main()
{
    char data[MAX], copy[MAX], ch = 'y';
    int t;

    //read data from "input.txt"
    fread("input.txt", data);

    //Generating key of same length as Plaintext
    int datalen = strlen(data);
    genkey(datalen);

    //maintaining a copy of data
    strcpy(copy, data);

    do
    {
        cout<<"Main Menu\n";
        cout<<"1) Encrypt the plain text using Vernam Cipher\n";
        cout<<"2) Decrypt the cipher text using Vernam Cipher\n";
        cout<<"Enter choice:\n";

        cin>>t;

        switch(t)
        {
            case 1:
                //encrypting the plaintext
                encrypt(data);
                ptr = 0;

                //writing encrypted data to "encrypted.txt"
                fwrite("encrypt.txt", data);

                for (int i = 0; i < strlen(data); ++i)
                {
                    int curc = (int)(data[i]);
                    hexcode(curc);

                    hexa[ptr++] = '0';
                    hexa[ptr++] = 'x';

                    for (int j = strlen(buf) - 1; j >= 0; --j)
                        hexa[ptr++] = buf[j];

                    hexa[ptr++] = ' ';
                }

                hexa[ptr] = '\0';
                fwrite("encryptt.txt", hexa);

                cout<<"Successfully encrypted!\n\n";
                cout<<"Original Data:\n"<<copy<<"\n\n";
                cout<<"Encrypted Data:\n"<<data<<"\n";

                //restoring data
                strcpy(data, copy);
                cout<<'\n';
                break;

            case 2:
                //reading encrypted data from "encrypt.txt"
                fread("encrypt.txt", data);
                cout<<"\nEncrypted Data:\n"<<data<<"\n\n";

                //decrypting the ciphertext
                decrypt(data);

                cout<<"\nDecrypted plaintext is:\n";
                cout<<data<<'\n';

                //writing decrypted data to "output.txt"
                fwrite("output.txt", data);

                //restoring data
                strcpy(data, copy);
                cout<<'\n';
                break;

            default: cout<<"Please enter a valid choice!\n";
        }

        cout<<"Do you wish to continue? ( Enter 'y' to continue and any other char to exit):\n";
        cin>>ch;
        cout<<"\n\n";
    }
    while(ch == 'y');

    return 0;
}

