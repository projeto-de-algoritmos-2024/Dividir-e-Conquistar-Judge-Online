#include <stdio.h>

int minSteps(int n) {
    int steps = 0;
    for (int i = 2; i <= n; i++) {
        while (n % i == 0) {
            steps += i;
            n /= i;
        }
    }
    return steps;
}

int main() {
    int n;
    printf("Entre com o valor de n: ");
    scanf("%d", &n);
    
    int result = minSteps(n);
    printf("Número mínimo de operações para obter %d 'A's é: %d\n", n, result);
    
    return 0;
}
