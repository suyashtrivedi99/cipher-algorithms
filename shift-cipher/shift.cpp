#include <iostream>
#include <fstream>
#include <cctype>
#include <cstring>

using namespace std;

#define MAX 10000
#define K 130

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
    char ch;
    int cur, base, mod, i = 0;

    for(i = 0; data[i] != '\0'; ++i)
    {
        //checking if data is a digit
        if(isdigit(data[i]))
        {
            cur = data[i] - '0';
            cur = (10 + ((cur + key) % 10)) % 10;
            data[i] = '0' + cur;
        }

        //checking if data is an upper case alphabet
        else if(isupper(data[i]))
        {
            cur = data[i] - 'A';
            cur = (26 + ((cur + key) % 26)) % 26;
            data[i] = 'A' + cur;
        }

        //checking if data is a lower case alphabet
        else if(islower(data[i]))
        {
            cur = data[i] - 'a';
            cur = (26 + ((cur + key) % 26)) % 26;
            data[i] = 'a' + cur;
        }

        //if not an alphanumeric char for eg spaces, let it remain the same
    }
}

//decryption is just the reverse of encryption
void decrypt(char enc[], int key)
{
    encrypt(enc, -key);
}

int main()
{
    int key, t = 0, flag = 0, m, mval, cur;
    char data[MAX], copy[MAX], ch = 'y';

    //Contains alphabets in the order of their occurring frequencies
    char freq[26] = {'e','t','a','o','i','n','s','r','h','d','l','u','c','m','f','y','w','g','p','b','v','k','x','q','j','z'};
    int alpha[26];

    //read data from "input.txt"
    fread("input.txt", data);

    //maintaining a copy of data
    strcpy(copy, data);

    do
    {
        cout<<"Main Menu\n";
        cout<<"1) Encrypt the plain text\n";
        cout<<"2) Decrypt the cipher text\n";
        cout<<"3) Find encryption key using brute force attack\n";
        cout<<"4) Find encryption key using frequency analysis attack\n";
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

            case 3: //Brute Force Attack
                    //reading encrypted data from "encrypt.txt"
                    fread("encrypt.txt", data);
                    cout<<"\nEncrypted Data:\n"<<data<<"\n\n";

                    cout<<"Initializing Brute Force attack ..."<<"\n\n";
                    flag = 0;

                    for (int i = 0; i < K && flag == 0; ++i)
                    {
                        char temp[MAX], tch;
                        strcpy(temp, data);
                        cout<<"\n\nDecryption key used: "<<i<<"\n\n";
                        decrypt(temp, i);
                        cout<<"Decrypted data:\n"<<temp<<"\n\n";
                        cout<<"Is this readable and sensible? (y/n)\n";
                        cin>>tch;

                        if(tch == 'y')
                        {
                            fwrite("output.txt", temp);
                            cout<<"\n\nValue of Key found: "<<i<<"\n\n";
                            flag = 1;
                        }
                    }

                    if(flag == 0)
                        cout<<"This is not decipherable!\n\n";

                    //restoring data
                    strcpy(data, copy);
                    break;

            case 4: //Frequency Analysis Attack
                    fread("encrypt.txt", data);

                    //resetting the alpha array
                    for (int i = 0; i < 26; ++i)
                        alpha[i] = 0;

                    //storing count of all alphabets
                    for (int i = 0; data[i] != '\0'; ++i)
                    {
                        if(isupper(data[i]))
                            alpha[data[i] - 'A']++;

                        else if(islower(data[i]))
                            alpha[data[i] - 'a']++;
                    }

                    m = -1; mval = -1;
                    for (int i = 0; i < 26; ++i)
                    {
                        if(mval < alpha[i])
                        {
                            m = i;
                            mval = alpha[i];
                        }
                    }

                    flag = 0;
                    for (int i = 0; i < 26 && flag == 0; ++i)
                    {
                        cur = freq[i] - 'a';
                        cur = (26 + ((m - cur) % 26)) % 26;

                        char temp[MAX], tch;
                        strcpy(temp, data);
                        cout<<"\n\nDecryption key used: "<<cur<<"\n\n";
                        decrypt(temp, cur);
                        cout<<"Decrypted data:\n"<<temp<<"\n\n";
                        cout<<"Is this readable (excluding numbers)? (y/n)\n";
                        cin>>tch;

                        if(tch == 'y')
                        {
                            cout<<"\n\nValue of Possible Key found: "<<cur<<"\n\n";
                            key = cur;
                            flag = 1;
                        }
                    }

                    cout<<"Possible values of keys: ";
                    for (int i = key; i < K; i += 26)
                    {
                        cout<<i<<", ";
                    }
                    cout<<"\n\n";

                    flag = 0;
                    for (int i = key; i < K && flag == 0; i += 26)
                    {
                        char temp[MAX], tch;
                        strcpy(temp, data);
                        cout<<"\n\nDecryption key used: "<<i<<"\n\n";
                        decrypt(temp, i);
                        cout<<"Decrypted data:\n"<<temp<<"\n\n";
                        cout<<"Is this numerically correct? (y/n)\n";
                        cin>>tch;

                        if(tch == 'y')
                        {
                            fwrite("output.txt", temp);
                            cout<<"\n\nValue of Correct Key found: "<<i<<"\n\n";
                            flag = 1;
                        }
                    }

                    //restoring data
                    strcpy(data, copy);
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