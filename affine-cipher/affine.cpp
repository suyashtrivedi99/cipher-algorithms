#include <bits/stdc++.h>
using namespace std;

#define MAX 1000

int inv;

//function for Extended Euclidean Algorithm
int extEuclid(int a, int b, int *x, int *y)
{
    //Base Case
    if (a == 0)
    {
        *x = 0, *y = 1;
        return b;
    }

    int x1, y1; //Store results of recursive call
    int gcd = extEuclid(b%a, a, &x1, &y1);

    //Update x and y using results of recursive call
    *x = y1 - (b/a) * x1;
    *y = x1;

    return gcd;
}

//Function to find modulo inverse of a
int modInv(int a, int m)
{
    int x, y;
    int g = extEuclid(a, m, &x, &y);

    //if not possible, return -1
    if (g != 1)
        return -1;
    else
    {
        int res = ((x % m) + m) % m;
        return res;
    }
}

void encrypt(char data[], int a, int b)
{
    //checking for feasibility of 'a'
    inv = modInv(a, 26);
    if(inv == -1)
    {
        cout<<"\n\nThe value of 'a' is not feasible as "<<a<<" and 26 are not coprime\n\n";
        return;
    }

    int n = strlen(data), idx = 0;

    for (int i = 0; i < n; ++i)
    {
        int cur;
        bool ch;

        if(islower(data[i]))
        {
            cur = data[i] - 'a';
            ch = 0;
        }

        else if(isupper(data[i]))
        {
            cur = data[i] - 'A';
            ch = 1;
        }

        else continue;

        int enc = ((a*cur) + b) % 26;

        if(ch)
            data[idx++] = 'A' + enc;
        else
            data[idx++] = 'a' + enc;
    }
    data[idx] = '\0';
}

void decrypt(char data[], int a, int b)
{
    //checking for feasibility of 'a'
    inv = modInv(a, 26);
    if(inv == -1)
    {
        cout<<"\n\nThe value of 'a' is not feasible as "<<a<<" and 26 are not coprime\n\n";
        return;
    }

    int n = strlen(data), idx = 0;

    for (int i = 0; i < n; ++i)
    {
        int cur;
        bool ch;

        if(islower(data[i]))
        {
            cur = data[i] - 'a';
            ch = 0;
        }

        else if(isupper(data[i]))
        {
            cur = data[i] - 'A';
            ch = 1;
        }

        else continue;

        int dec = (26 + ((inv * (cur - b)) % 26)) % 26;

        if(ch)
            data[idx++] = 'A' + dec;
        else
            data[idx++] = 'a' + dec;
    }
    data[idx] = '\0';
}

int main()
{
    char data[MAX] = "Treasure", copy[MAX], ch = 'y';
    int t;

    //maintaining a copy of data
    strcpy(copy, data);

    do
    {
        cout<<"Main Menu\n";
        cout<<"1) Encrypt the plain text using Affine Cipher\n";
        cout<<"2) Decrypt the cipher text using Affine Cipher\n";
        cout<<"Enter choice:\n";

        cin>>t;

        switch(t)
        {
            case 1:  //restoring data
                    strcpy(data, copy);
                    int a, b;
                    cout<<"\nEnter a: ";
                    cin>>a;
                    cout<<"\nEnter b: ";
                    cin>>b;

                    //encrypting the plaintext
                    encrypt(data, a, b);

                    if(inv == -1)
                        goto end1;

                    cout<<"Successfully encrypted!\n";
                    cout<<"Original Data:\n"<<copy<<"\n";
                    cout<<"Encrypted Data:\n"<<data<<"\n";

                    end1:;
                    break;

            case 2: cout<<"Cipher Text: "<<data<<'\n';
                    cout<<"\nEnter a: ";
                    cin>>a;
                    cout<<"\nEnter b: ";
                    cin>>b;

                    //decrypting the plaintext
                    decrypt(data, a, b);

                    if(inv == -1)
                        goto end2;

                    cout<<"Successfully decrypted!\n";
                    cout<<"Decrypted Data:\n"<<data<<"\n";

                    end2:;
                    break;

            default: cout<<"Please enter a valid choice!\n";
        }

        cout<<"\nDo you wish to continue? ( Enter 'y' to continue and any other char to exit):\n";
        cin>>ch;
        cout<<"\n\n";
    }
    while(ch == 'y');

    return 0;
}

