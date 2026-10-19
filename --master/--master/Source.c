#include <stdio.h>
#include <locale.h>

task1()
{
    setlocale(LC_ALL, "RUS");
    int n;
    float x[100];
    float q[100];
    float sum = 0;
    float mean, median, temp, fraction;
    int count = 0;
    int i, j;

    printf("Введите количество измерений: ");
    scanf("%d", &n);

    if (n <= 0 || n > 100)
    {
        printf("Ошибка!\n");
        return 0;
    }

    for (i = 0; i < n; i++)
    {
        printf("Введите концентрацию x[%d]: ", i + 1);
        scanf("%f", &x[i]);

        if (x[i] < 10)
        {
            q[i] = 3 * x[i] + 2;
        }
        else if (x[i] < 30)
        {
            q[i] = 1.5 * x[i] + 17;
        }
        else
        {
            q[i] = 7 * x[i] + 41;
        }

        sum = sum + q[i];

        if (q[i] > 60)
        {
            count = count + 1;
        }
    }

    mean = sum / n;

    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - 1 - i; j++)
        {
            if (q[j] > q[j + 1])
            {
                temp = q[j];
                q[j] = q[j + 1];
                q[j + 1] = temp;
            }
        }
    }

    if (n % 2 == 1)
    {
        median = q[n / 2];
    }
    else
    {
        median = (q[n / 2 - 1] + q[n / 2]) / 2;
    }

    fraction = (float)count / n;

    printf("Среднее значение: %f\n", mean);
    printf("Медиана: %f\n", median);
    printf("Количество значений выше UCL: %d\n", count);
    printf("Доля значений выше UCL: %f\n", fraction);

    return 0;
}

int main()
{
    task1();
    return 0;
}