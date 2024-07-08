#include <stdio.h>
#include <stdlib.h>

int power_of_2(int num);

int main(void) {
    int size;
    printf("Enter size of input:\n");
    scanf("%d", &size);
    if (size <= 0) {
        printf("Invalid size\n");
        return 0;
    }
    int *numbers = malloc(size * sizeof(int));
    if (numbers == NULL)
        return 0;

    printf("Enter numbers:\n");
    for (int i = 0; i < size; ++i)
        if (scanf("%d", &numbers[i]) != 1) {
            printf("Invalid number\n");
            free(numbers);
            return 0;
        }
    int total_exp = 0;
    for (int i = 0; i < size; ++i){
        int exp =power_of_2(numbers[i]);
       if(power_of_2(numbers[i]) == -10)
           continue;
        printf("The number %d is a power of 2: %d = 2^%d\n" ,numbers[i],numbers[i], exp);
        total_exp += exp;
    }
    printf("Total exponent sum is %d\n", total_exp);
    free(numbers);
    return 0;
}

int power_of_2(int num) {
    int sum = 0;
    if(num <= 0)
        return -10;
    while (num != 1) {
        if(num % 2 != 0)
            return -10;
        num = num / 2;
        ++sum;
    }
    return sum;
}
