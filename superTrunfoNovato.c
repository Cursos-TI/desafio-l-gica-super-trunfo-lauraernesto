#include <stdio.h>

int main() {
    // Variáveis da Carta 1
    char estado1[30], codigo1[10], cidade1[50];
    int populacao1, pontos1;
    float area1, pib1;

    // Variáveis da Carta 2
    char estado2[30], codigo2[10], cidade2[50];
    int populacao2, pontos2;
    float area2, pib2;

    // Cadastro da primeira carta
    printf("Cadastro da Carta 1\n");
    printf("Digite o estado: ");
    scanf("%s", estado1);
    printf("Digite o codigo da carta: ");
    scanf("%s", codigo1);
    printf("Digite o nome da cidade: ");
    scanf("%s", cidade1);
    printf("Digite a populacao: ");
    scanf("%d", &populacao1);   // <-- CORRETO
    printf("Digite a area (km2): ");
    scanf("%f", &area1);        // <-- CORRETO
    printf("Digite o PIB: ");
    scanf("%f", &pib1);         // <-- CORRETO
    printf("Digite o numero de pontos turisticos: ");
    scanf("%d", &pontos1);      // <-- CORRETO

    printf("\n--------------------------------------\n");

    // Cadastro da segunda carta
    printf("Cadastro da Carta 2\n");
    printf("Digite o estado: ");
    scanf("%s", estado2);
    printf("Digite o codigo da carta: ");
    scanf("%s", codigo2);
    printf("Digite o nome da cidade: ");
    scanf("%s", cidade2);
    printf("Digite a populacao: ");
    scanf("%d", &populacao2);
    printf("Digite a area (km2): ");
    scanf("%f", &area2);
    printf("Digite o PIB: ");
    scanf("%f", &pib2);
    printf("Digite o numero de pontos turisticos: ");
    scanf("%d", &pontos2);

    printf("\n======================================\n");
    printf("As cartas cadastradas foram:\n");
    printf("Carta 1: %s - Populacao: %d\n", cidade1, populacao1);
    printf("Carta 2: %s - Populacao: %d\n", cidade2, populacao2);
    printf("======================================\n\n");

    // Comparação por população
    if (populacao1 > populacao2) {
        printf("A carta vencedora e: %s (maior populacao)\n", cidade1);
    } else if (populacao2 > populacao1) {
        printf("A carta vencedora e: %s (maior populacao)\n", cidade2);
    } else {
        printf("Empate! As duas cidades tem a mesma populacao.\n");
    }

    return 0;
}