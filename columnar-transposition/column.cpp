#include <bits/stdc++.h>
#include <fstream>

using namespace std;

#define MAX 1000
#define mp map<char,vector<char>>
#define pb push_back

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

void encrypt(char key[], char data[])
{
    mp hmap;
    char mat[MAX][MAX];

    int len = strlen(data);
    int c = strlen(key);
    int r = len/c;

    if(len%c) r++;

    //splitting message into a matrix
    int idx = 0;
    for (int i = 0; i < r; ++i)
    {
        for (int j = 0; j < c; ++j, ++idx)
        {
            if(idx < len)
                mat[i][j] = data[idx];
            else
                mat[i][j] = ' ';
        }
    }

    cout<<"The matrix before encryption:\n";
    for (int i = 0; i < r; ++i)
    {
        for (int j = 0; j < c; ++j)
            cout<<mat[i][j]<<' ';
        cout<<'\n';
    }

    //encrypting and saving
    for (int i = 0; i < c; ++i)
    {
        for (int j = 0; j < r; ++j)
            hmap[key[i]].pb(mat[j][i]);
    }

    cout<<"\n\nThe matrix after encryption:\n";
    idx = 0;
    for (auto it = hmap.begin(); it != hmap.end(); ++it)
    {
        auto cur = it->second;

        for (int i = 0; i < cur.size(); ++i, ++idx)
        {
            data[idx] = cur[i];
            cout<<data[idx]<<' ';
        }
        cout<<'\n';
    }
    data[idx] = '\0';
    cout<<"\n\n";
}

void decrypt(char key[], char data[])
{
    mp hmap;
    char mat[MAX][MAX];

    char sorted[MAX];
    strcpy(sorted, key);
    sort(sorted, sorted + strlen(key));

    int len = strlen(data);
    int c = strlen(key);
    int r = len/c;

    if(len%c) r++;

    //splitting message into a matrix
    int idx = 0;
    for (int i = 0; i < c; ++i)
    {
        for (int j = 0; j < r; ++j, ++idx)
        {
            if(idx < len)
                mat[j][i] = data[idx];
            else
                mat[j][i] = ' ';
        }
    }

    cout<<"The matrix before decryption:\n";
    for (int i = 0; i < r; ++i)
    {
        for (int j = 0; j < c; ++j)
            cout<<mat[i][j]<<' ';
        cout<<'\n';
    }

    //decrypting and saving
    for (int i = 0; i < c; ++i)
    {
        for (int j = 0; j < r; ++j)
            hmap[sorted[i]].pb(mat[j][i]);
    }

    cout<<"\n\nThe matrix after decryption:\n";
    idx = 0;
    for (int i = 0; i < r; ++i)
    {
        for (int j = 0; j < c; ++j, ++idx)
        {
            data[idx] = hmap[key[j]][i];
            cout<<data[idx]<<' ';
        }
        cout<<'\n';
    }
    data[idx] = '\0';
    cout<<"\n\n";
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
        cout<<"1) Encrypt the plain text using Columnar Transposition Cipher\n";
        cout<<"2) Decrypt the cipher text using Columnar Transposition Cipher\n";
        cout<<"Enter choice:\n";

        cin>>t;

        switch(t)
        {
            case 1: cout<<"Enter the encryption key:\n";
                cin>>key;

                //encrypting the plaintext
                encrypt(key, data);

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
                decrypt(key, data);

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

