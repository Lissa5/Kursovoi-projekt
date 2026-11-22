#include <stdio.h>
#include <locale.h>

#define MAX_N 100

#define LCL 20.0
#define UCL 60.0

#define BORDER_1 10.0
#define BORDER_2 30.0

#define K1 3.0
#define B1 2.0

#define K2 1.5
#define B2 17.0

#define K3 0.7
#define B3 41.0

int read_data(int* n, float x[]);
float compute_q(float x);
int check_control(float q);
float compute_mean(float q[], int n);
float compute_median(float q[], int n);
int count_above(float q[], int n);

int main()
{
    setlocale(LC_ALL, "Russian");

    int n;
    int i;
    int state;
    int count;

    float x[MAX_N];
    float q[MAX_N];

    float mean;
    float median;
    float fraction;

    printf("Программа анализа концентрации вещества\n\n");

    if (read_data(&n, x) == 0)
    {
        printf("Ошибка ввода данных!\n");
        return 1;
    }

    printf("\nРезультаты измерений:\n");

    for (i = 0; i < n; i++)
    {
        q[i] = compute_q(x[i]);

        state = check_control(q[i]);

        printf("\nИзмерение %d:\n", i + 1);
        printf("Концентрация: %.2f мг/л\n", x[i]);
        printf("Значение Q: %.2f\n", q[i]);

        if (state == -1)
        {
            printf("Состояние: ниже нормы\n");
        }
        else if (state == 1)
        {
            printf("Состояние: выше нормы\n");
        }
        else
        {
            printf("Состояние: в пределах нормы\n");
        }
    }

    mean = compute_mean(q, n);
    median = compute_median(q, n);
    count = count_above(q, n);

    fraction = (float)count / n;

    printf("\nСтатистические результаты:\n");

    printf("Среднее арифметическое: %.2f\n", mean);
    printf("Медиана: %.2f\n", median);
    printf("Количество значений выше UCL: %d\n", count);
    printf("Доля значений выше UCL: %.2f\n", fraction);
    printf("Доля в процентах: %.2f%%\n", fraction * 100);

    return 0;
}

int read_data(int* n, float x[])
{
    int i;

    printf("Введите количество измерений (1-%d): ", MAX_N);

    if (scanf("%d", n) != 1)
    {
        return 0;
    }

    if (*n < 1 || *n > MAX_N)
    {
        return 0;
    }

    for (i = 0; i < *n; i++)
    {
        printf("Введите концентрацию %d: ", i + 1);

        if (scanf("%f", &x[i]) != 1)
        {
            return 0;
        }

        if (x[i] < 0)
        {
            return 0;
        }
    }

    return 1;
}

float compute_q(float x)
{
    if (x < BORDER_1)
    {
        return K1 * x + B1;
    }
    else if (x < BORDER_2)
    {
        return K2 * x + B2;
    }
    else
    {
        return K3 * x + B3;
    }
}

int check_control(float q)
{
    if (q < LCL)
    {
        return -1;
    }
    else if (q > UCL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

float compute_mean(float q[], int n)
{
    int i;
    float sum = 0;

    for (i = 0; i < n; i++)
    {
        sum = sum + q[i];
    }

    return sum / n;
}

float compute_median(float q[], int n)
{
    int i;
    int j;
    float temp;
    float a[MAX_N];

    for (i = 0; i < n; i++)
    {
        a[i] = q[i];
    }

    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - 1 - i; j++)
        {
            if (a[j] > a[j + 1])
            {
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }

    if (n % 2 == 1)
    {
        return a[n / 2];
    }
    else
    {
        return (a[n / 2 - 1] + a[n / 2]) / 2;
    }
}

int count_above(float q[], int n)
{
    int i;
    int count = 0;

    for (i = 0; i < n; i++)
    {
        if (q[i] > UCL)
        {
            count++;
        }
    }

    return count;
}