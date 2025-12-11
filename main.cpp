
#include <iostream>
#include <cstring>
using namespace std;

void func(int &x) { x = 20; }
void func(int x) { x = 30; }
int *findChars(char *s, char c)
{
    int i = 0;
    int j = 0;
    int *res = new int[100];
    while (s[i] != '\0')
    {
        if (tolower(s[i]) == c)
        {
            *(res + j) = i;
            j++;
        }
        i++;
    }
    *(res + j) = -1;
    return res;
}

int sum(int n)
{
    if (n == 1)
        return 1;
    return n + sum(n - 1);
}

int diagSum(int** arr, int n)
{
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += arr[i][i];
    }
    return sum;
}

void concatStr(char *dest, char *source)
{
    int i = 0;
    int j = 0;

    while (dest[i] != '\0')
    {
        i++;
    }
    dest[i] = ' ';
    i++;
    while (source[j] != '\0')
    {
        dest[i] = source[j];
        i++;
        j++;
    }

    dest[i] = '\0';
}

int main()
{
    int n = 2;
    int **arr = new int *[n];

    for (int i = 0; i < n; i++)
    {
        arr[i] = new int[n];
    }
    arr[0][0] = 1;
    arr[0][1] = 2;
    arr[1][0] = 1;
    arr[1][1] = 2;
    cout << diagSum(arr, 2);
}
