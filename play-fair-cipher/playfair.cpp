#include <bits/stdc++.h>
#include <fstream>

using namespace std;

#define MAX 1000
#define ump unordered_map
#define pii pair<int,int>

//matrix for encryption
char mat[5][5];

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

//function to preprocess data before encryption
void preprocess(char data[])
{
    int len = strlen(data), idx = 0;
    char data2[MAX];

    //removing spaces and special symbols and converting all alphabets to lowercase
    for (int i = 0; i < len; ++i)
    {
        if(isalpha(data[i]))
        {
            char ch = tolower(data[i]);

            //replace all 'J's by 'I's
            if(ch == 'j') ch = 'i';

            data2[idx++] = ch;
        }
    }

    data2[idx] = '\0';
    strcpy(data, data2);
}

//function to initialize key matrix
void initMat(char key[])
{
    //storing occurrence of duplicates in key
    ump<char,int> store;
    int klen = strlen(key), idx = 0;

    //appending all alphabets to the key
    for (int i = klen; i < klen + 26; ++i)
        key[i] = 'a' + i - klen;
    key[klen + 26] = '\0';

    preprocess(key);

    //entering all the chars into matrix only once
    for (int i = 0; i < 5; ++i)
    {
        for (int j = 0; j < 5; ++j, ++idx)
        {
            //checking if already entered
            if(store[key[idx]] == 0)
            {
                store[key[idx]]++;
                mat[i][j] = key[idx];
            }
            else j--;
        }
    }

    //print matrix
    cout<<"\n\nGenerated Key Matrix:\n";

    for (int i = 0; i < 5; ++i)
    {
        for (int j = 0; j < 5; ++j)
            cout<<mat[i][j]<<' ';
        cout<<'\n';
    }

    cout<<"\n\n";
}

//function for searching position of a char in matrix
pii search(char ch)
{
    pii p;
    for (int i = 0; i < 5; ++i)
    {
        for (int j = 0; j < 5; ++j)
        {
            if(mat[i][j] == ch)
            {
                p.first = i;
                p.second = j;
            }
        }
    }
    return p;
}

//function to encrypt plain text
void encrypt(char data[], char key[])
{
    preprocess(data);
    initMat(key);

    int len = strlen(data);
    int klen = strlen(key);

    //appending 'x' to plain text to make its length even
    if(len%2)
    {
        data[len++] = 'x';
        data[len] = '\0';
    }

    for (int i = 0; i < len; i += 2)
    {
        char ch1 = data[i];
        char ch2 = data[i+1];

        //if both chars are same, replace the second with x
        if(ch1 == ch2)
            ch2 = 'x';

        int r1, c1, r2, c2;
        r1 = search(ch1).first;
        c1 = search(ch1).second;
        r2 = search(ch2).first;
        c2 = search(ch2).second;

        //if same column, move both down
        if(c1 == c2)
        {
            ch1 = mat[(r1+1)%5][c1];
            ch2 = mat[(r2+1)%5][c1];
        }

        //if same row, move both right
        else if(r1 == r2)
        {
            ch1 = mat[r1][(c1+1)%5];
            ch2 = mat[r1][(c2+1)%5];
        }

        //if neither, use opposite corners
        else
        {
            ch1 = mat[r1][c2];
            ch2 = mat[r2][c1];
        }

        data[i] = ch1;
        data[i+1] = ch2;
    }
}

//function to decrypt cipher text
void decrypt(char data[], char key[])
{
    preprocess(data);
    initMat(key);

    int len = strlen(data);
    int klen = strlen(key);

    for (int i = 0; i < len; i += 2)
    {
        char ch1 = data[i];
        char ch2 = data[i+1];

        int r1, c1, r2, c2;
        r1 = search(ch1).first;
        c1 = search(ch1).second;
        r2 = search(ch2).first;
        c2 = search(ch2).second;

        //if same column, move both up
        if(c1 == c2)
        {
            ch1 = mat[(((r1-1)%5)+5)%5][c1];
            ch2 = mat[(((r2-1)%5)+5)%5][c1];
        }

        //if same row, move both left
        else if(r1 == r2)
        {
            ch1 = mat[r1][(((c1-1)%5)+5)%5];
            ch2 = mat[r1][(((c2-1)%5)+5)%5];
        }

        //if neither, use opposite corners
        else
        {
            ch1 = mat[r1][c2];
            ch2 = mat[r2][c1];
        }

        data[i] = ch1;

        if(ch2 == 'x')
        	data[i+1] = ch1;
        else 
        	data[i+1] = ch2;
    }

    //if last letter is 'x', remove it
    if(data[len-1] == 'x')
        data[len-1] = '\0';
}

int main()
{
    char data[MAX], copy[MAX], ch = 'y', key[MAX];
    int t;

    //read data from "input.txt"
    fread("input.txt", data);

    //maintaining a copy of data
    strcpy(copy, data);

    do
    {
        cout<<"Main Menu\n";
        cout<<"1) Encrypt the plain text using Playfair Cipher\n";
        cout<<"2) Decrypt the cipher text using Playfair Cipher\n";
        cout<<"Enter choice:\n";

        cin>>t;

        switch(t)
        {
            case 1: cout<<"Enter the encryption key:\n";
                cin>>key;

                //encrypting the plaintext
                encrypt(data, key);

                //writing encrypted data to "encrypted.txt"
                fwrite("encrypt.txt", data);
                cout<<"Successfully encrypted!\n\n";
                cout<<"Original Data:\n"<<copy<<"\n\n";
                cout<<"Encrypted Data:\n"<<data<<"\n";

                //restoring data
                strcpy(data, copy);
                cout<<'\n';
                break;

            case 2: //reading encrypted data from "encrypt.txt"
                fread("encrypt.txt", data);
                cout<<"\nEncrypted Data:\n"<<data<<"\n\n";
                cout<<"Enter the decryption key:\n";
                cin>>key;

                //decrypting the ciphertext
                decrypt(data, key);

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