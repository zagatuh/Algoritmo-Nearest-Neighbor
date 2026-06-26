#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#define PX 0
#define PY 0

typedef struct {
    int x;
    int y;
} Ponto;

typedef struct {
    Ponto endereco;
    double distancia;
} Encomenda;

double calcularDistancia(int x2, int y2, int x1, int y1) {
    return sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
}

Encomenda criarEncomenda(int i) {
    Encomenda e;

    printf("Digite o endereço da %dª encomenda X e Y: ", i + 1);
    scanf("%d %d", &e.endereco.x, &e.endereco.y);

    e.distancia = calcularDistancia(e.endereco.x, e.endereco.y, PX, PY);

    return e;
}

int main() {
    int qntdEncomendas;
    double percurso = 0;

    printf("Digite o número de encomendas: ");
    scanf("%d", &qntdEncomendas);

    bool visitado[qntdEncomendas];
    for (int i = 0; i < qntdEncomendas; i++) visitado[i] = false;

    Encomenda x[qntdEncomendas];

    for (int i = 0; i < qntdEncomendas; i++) {
        x[i] = criarEncomenda(i);
        printf("Endereço: x = %d, y = %d\nDistância: %.2lfkm\n\n",
               x[i].endereco.x, x[i].endereco.y, x[i].distancia);
    }

    int melhor;
    double menorDist = -1;
    int marcacao[qntdEncomendas];
    double distancias[qntdEncomendas]; 

    Ponto atual = {0, 0};

    for (int i = 0; i < qntdEncomendas; i++) {
        menorDist = -1;
        for (int j = 0; j < qntdEncomendas; j++) {
            if (visitado[j] == false) {
                double d = calcularDistancia(x[j].endereco.x, x[j].endereco.y, atual.x, atual.y);
                if (menorDist < 0 || d < menorDist) {
                    menorDist = d;
                    melhor = j;
                    marcacao[i] = melhor;
                }
            }
        }

        distancias[melhor] = menorDist;
        visitado[melhor] = true;
        percurso += menorDist;
        atual.x = x[melhor].endereco.x;
        atual.y = x[melhor].endereco.y;
    }

    double distRetorno = calcularDistancia(atual.x, atual.y, PX, PY);
    percurso += distRetorno;

    printf("origem -> %dª entrega: %.2lfkm\n", marcacao[0] + 1, distancias[marcacao[0]]);

    for (int i = 0; i < qntdEncomendas; i++) {
        if (i == qntdEncomendas - 1) {
            printf("%dª entrega -> origem: %.2lfkm\n", marcacao[i] + 1, distRetorno);
        } else {
            printf("%dª entrega -> %dª entrega: %.2lfkm\n", marcacao[i] + 1, marcacao[i+1] + 1, distancias[marcacao[i+1]]);
        }
    }

    printf("\nPercurso Total: %.2lfkm", percurso);

    return 0;
}