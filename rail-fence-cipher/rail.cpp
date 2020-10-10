#include <bits/stdc++.h>
#include <fstream>

using namespace std;

#define MAX 1000

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

//function to encrypt the data with a given key
void encrypt(char data[], int key)
{
    int r = key;
    int c = strlen(data);

    char mat[MAX][MAX];

    //filling matrix with special symbol
    for (int i = 0; i < r; ++i)
    {
        for (int j = 0; j < c; ++j)
            mat[i][j] = '*';
    }

    //to control movement
    int cur = 0, move = 1;

    for (int i = 0; i < c; ++i)
    {
        //checking boundary conditions
        if(cur == 0) move = 1;
        if(cur == r-1) move = -1;

        mat[cur][i] = data[i];
        cur += move;
    }

    cout<<"Rails Matrix:\n";
    for (int i = 0; i < r; ++i)
    {
        for (int j = 0; j < c; ++j)
            cout<<mat[i][j]<<' ';
        cout<<'\n';
    }

    //encrypting data
    cur = 0;
    for (int i = 0; i < r; ++i)
    {
        for (int j = 0; j < c; ++j)
        {
            if(mat[i][j] != '*')
                data[cur++] = mat[i][j];
        }
    }
    data[cur] = '\0';
    cout<<"\n\n";
}


void decrypt(char data[], int key)
{
    int r = key;
    int c = strlen(data);

    char mat[MAX][MAX];

    //filling matrix with special symbol
    for (int i = 0; i < r; ++i)
    {
        for (int j = 0; j < c; ++j)
            mat[i][j] = '*';
    }

    //to control movement
    int cur = 0, move = 1;

    //filling the position of chars with '$'
    for (int i = 0; i < c; ++i)
    {
        //checking boundary conditions
        if(cur == 0) move = 1;
        if(cur == r-1) move = -1;

        mat[cur][i] = '$';
        cur += move;
    }

    //decrypting data
    cur = 0;
    for (int i = 0; i < r; ++i)
    {
        for (int j = 0; j < c; ++j)
        {
            if(mat[i][j] == '$')
                mat[i][j] = data[cur++];
        }
    }

    cout<<"Rails Matrix:\n";
    for (int i = 0; i < r; ++i)
    {
        for (int j = 0; j < c; ++j)
            cout<<mat[i][j]<<' ';
        cout<<'\n';
    }

    cur = 0; move = 1;

    //decrypting data along the diagonals
    for (int i = 0; i < c; ++i)
    {
        //checking boundary conditions
        if(cur == 0) move = 1;
        if(cur == r-1) move = -1;

        data[i] = mat[cur][i];
        cur += move;
    }
    data[c] = '\0';
    cout<<"\n\n";
}

//driver program to check the above functions
int main()
{
    int key, t = 0;
    char data[MAX], copy[MAX], ch = 'y';

    //read data from "input.txt"
    fread("input.txt", data);

    //maintaining a copy of data
    strcpy(copy, data);

    do
    {
        cout<<"Main Menu\n";
        cout<<"1) Encrypt the plain text using Rail Cipher\n";
        cout<<"2) Decrypt the cipher text using Rail Cipher\n";
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

