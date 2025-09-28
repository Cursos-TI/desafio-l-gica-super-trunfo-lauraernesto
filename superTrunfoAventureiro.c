
#include <stdio.h>

int main(void) {
    // ----- Variáveis da Carta 1 -----
    char pais1[40];
    int   pop1, pontos1;
    float area1, pib1;

    // ----- Variáveis da Carta 2 -----
    char pais2[40];
    int   pop2, pontos2;
    float area2, pib2;

    // ===== Cadastro das cartas =====
    printf("=== Cadastro da Carta 1 ===\n");
    printf("Nome da cidade: ");
    scanf("%s", pais1);
    printf("Populacao: ");
    scanf("%d", &pop1);
    printf("Area (km2): ");
    scanf("%f", &area1);
    printf("PIB: ");
    scanf("%f", &pib1);
    printf("Numero de pontos turisticos: ");
    scanf("%d", &pontos1);

    printf("\n=== Cadastro da Carta 2 ===\n");
    printf("Nome da cidade: ");
    scanf("%s", pais2);
    printf("Populacao: ");
    scanf("%d", &pop2);
    printf("Area (km2): ");
    scanf("%f", &area2);
    printf("PIB: ");
    scanf("%f", &pib2);
    printf("Numero de pontos turisticos: ");
    scanf("%d", &pontos2);

    int opcao;
    do {
        // calcula densidade (habitantes por km²) — checa divisao por zero
        float dens1 = (area1 > 0.0f) ? (pop1 / area1) : -1.0f;
        float dens2 = (area2 > 0.0f) ? (pop2 / area2) : -1.0f;


        
printf("\n=== MENU DE COMPARACAO ===\n");
        printf("1 - Populacao\n"); //  (maior vence)
        printf("2 - Area \n"); // (maior vence)
        printf("3 - PIB \n"); // (maior vence)
        printf("4 - Pontos Turisticos \n"); // maior vence)
        printf("5 - Densidade Demografica \n"); //(MENOR vence)
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: // População
                printf("\n[Comparacao: Populacao]\n");
                printf("%s: %d habitantes\n", pais1, pop1);
                printf("%s: %d habitantes\n", pais2, pop2);
                if (pop1 > pop2) {
                    printf("Vencedor: %s\n", pais1);
                } else if (pop2 > pop1) {
                    printf("Vencedor: %s\n", pais2);
                } else {
                    printf("Empate!\n");
                }
                break;

            case 2: // Área
                printf("\n[Comparacao: Area]\n");
                printf("%s: %.2f km2\n", pais1, area1);
                printf("%s: %.2f km2\n", pais2, area2);
                if (area1 > area2) {
                    printf("Vencedor: %s\n", pais1);
                } else if (area2 > area1) {
                    printf("Vencedor: %s\n", pais2);
                } else {
                    printf("Empate!\n");
                }
                break;

            case 3: // PIB
                printf("\n[Comparacao: PIB]\n");
                printf("%s: %.2f\n", pais1, pib1);
                printf("%s: %.2f\n", pais2, pib2);
                if (pib1 > pib2) {
                    printf("Vencedor: %s\n", pais1);
                } else if (pib2 > pib1) {
                    printf("Vencedor: %s\n", pais2);
                } else {
                    printf("Empate!\n");
                }
                break;

            case 4: // Pontos turísticos
                printf("\n[Comparacao: Pontos Turisticos]\n");
                printf("%s: %d pontos\n", pais1, pontos1);
                printf("%s: %d pontos\n", pais2, pontos2);
                if (pontos1 > pontos2) {
                    printf("Vencedor: %s\n", pais1);
                } else if (pontos2 > pontos1) {
                    printf("Vencedor: %s\n", pais2);
                } else {
                    printf("Empate!\n");
                }
                break;

            case 5: // Densidade (menor vence)
                printf("\n[Comparacao: Densidade Demografica]\n");
                if (dens1 < 0.0f || dens2 < 0.0f) {
                    printf("Nao foi possivel calcular densidade: area deve ser > 0.\n");
                } else {
                    printf("%s: %.4f hab/km2\n", pais1, dens1);
                    printf("%s: %.4f hab/km2\n", pais2, dens2);
                    if (dens1 < dens2) {
                        printf("Vencedor: %s (menor densidade)\n", pais1);
                    } else if (dens2 < dens1) {
                        printf("Vencedor: %s (menor densidade)\n", pais2);
                    } else {
                        printf("Empate!\n");
                    }
                }
                break;

            case 0:
                printf("Saindo...\n"
                "ate a proxima!\n");
                break;

            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}