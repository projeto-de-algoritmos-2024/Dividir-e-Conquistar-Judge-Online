#include <stdio.h>

int mesclarEContar(int* numeros, int inicio, int meio, int fim) {
    int contador = 0;
    int indiceDireita = meio + 1;

    for (int indiceEsquerda = inicio; indiceEsquerda <= meio; indiceEsquerda++) {
        while (indiceDireita <= fim && numeros[indiceEsquerda] > 2LL * numeros[indiceDireita]) {
            indiceDireita++;
        }
        contador += (indiceDireita - (meio + 1));
    }

    int tamanhoEsquerda = meio - inicio + 1;
    int tamanhoDireita = fim - meio;

    int esquerda[tamanhoEsquerda], direita[tamanhoDireita];
    for (int i = 0; i < tamanhoEsquerda; i++) esquerda[i] = numeros[inicio + i];
    for (int i = 0; i < tamanhoDireita; i++) direita[i] = numeros[meio + 1 + i];

    int i = 0, j = 0, k = inicio;
    while (i < tamanhoEsquerda && j < tamanhoDireita) {
        if (esquerda[i] <= direita[j]) {
            numeros[k++] = esquerda[i++];
        } else {
            numeros[k++] = direita[j++];
        }
    }

    while (i < tamanhoEsquerda) numeros[k++] = esquerda[i++];
    while (j < tamanhoDireita) numeros[k++] = direita[j++];

    return contador;
}

int ordenarEContar(int* numeros, int inicio, int fim) {
    if (inicio >= fim) return 0;

    int meio = (inicio + fim) / 2;
    int contador = ordenarEContar(numeros, inicio, meio);
    contador += ordenarEContar(numeros, meio + 1, fim);
    contador += mesclarEContar(numeros, inicio, meio, fim);

    return contador;
}

int reversePairs(int* numeros, int tamanhoNumeros) {
    return ordenarEContar(numeros, 0, tamanhoNumeros - 1);
}

int main() {
    int numeros[] = {1, 3, 2, 3, 1};
    int tamanhoNumeros = sizeof(numeros) / sizeof(numeros[0]);
    printf("Número de pares invertidos: %d\n", reversePairs(numeros, tamanhoNumeros));
    return 0;
}
