/* Super Trunfo - Países/Cidades (Nível Mestre, versão para iniciantes)
   - Feito com foco em clareza e validação de entrada.
   - Recursos:
     * Cadastrar cartas (nome + 5 atributos).
     * Comparar duas cartas com DOIS atributos escolhidos.
     * Desempate em camadas: A1 -> A2 -> média geral -> sorteio.
     * Tratamento de erros (letras onde precisa número).
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

/* -------------------- CONFIG DOS ATRIBUTOS (dinâmico) -------------------- */
#define ATTR_COUNT 5
const char *ATTR_LABELS[ATTR_COUNT] = {
    "Populacao (milhoes)    [maior vence]",
    "Area (km2)             [maior vence]",
    "IDH (0 a 1)            [maior vence]",
    "PIB (bilhoes US$)      [maior vence]",
    "Turismo (0 a 100)      [maior vence]"
};
/* Todos os atributos: MAIOR é melhor. Se quiser mudar, basta inverter comparações. */

/* -------------------- LIMITES E ESTRUTURAS ------------------------------- */
#define MAX_CARDS 50
#define NAME_LEN  60

typedef struct {
    char  nome[NAME_LEN];
    double attr[ATTR_COUNT]; /* [0]=pop, [1]=area, [2]=idh, [3]=pib, [4]=turismo */
    int   ativo;             /* 1 = usado; 0 = vazio */
} Carta;

Carta CARTAS[MAX_CARDS];
int   QTD = 0;

/* -------------------- UTIL: leitura segura -------------------------------- */
void limpar_newline(char *s) {
    size_t n = strlen(s);
    if (n > 0 && s[n-1] == '\n') s[n-1] = '\0';
}

void ler_linha(char *buf, size_t tam) {
    if (fgets(buf, (int)tam, stdin) == NULL) {
        /* EOF/erro: fornecer string vazia para evitar lixo */
        buf[0] = '\0';
        return;
    }
    limpar_newline(buf);
}

/* Lê inteiro com validação e (opcional) faixa */
int ler_int_faixa(const char *msg, int min, int max) {
    char buf[128];
    long val;
    char *end;

    while (1) {
        printf("%s", msg);
        ler_linha(buf, sizeof(buf));
        if (buf[0] == '\0') { puts("Entrada vazia. Tente novamente."); continue; }

        val = strtol(buf, &end, 10);
        if (*end != '\0') {
            puts("Isso nao parece um numero inteiro. Tente de novo.");
            continue;
        }
        if (val < min || val > max) {
            printf("Valor valido: entre %d e %d.\n", min, max);
            continue;
        }
        return (int)val;
    }
}

/* Lê double com validação; aceita vírgula ou ponto */
double ler_double(const char *msg) {
    char buf[128];
    char *end;
    double v;

    while (1) {
        printf("%s", msg);
        ler_linha(buf, sizeof(buf));
        if (buf[0] == '\0') { puts("Entrada vazia. Tente novamente."); continue; }

        /* trocar vírgula por ponto */
        for (char *p = buf; *p; ++p) if (*p == ',') *p = '.';

        v = strtod(buf, &end);
        if (*end != '\0') {
            puts("Isso nao parece um numero (use 10 ou 10.5). Tente de novo.");
            continue;
        }
        return v;
    }
}

void pausar(void) {
    printf("\n(Pressione ENTER para continuar) ");
    char tmp[8];
    ler_linha(tmp, sizeof(tmp));
}

/* -------------------- LISTAGEM / BUSCA ----------------------------------- */
void listar_cartas(void) {
    if (QTD == 0) { puts("\nNao ha cartas cadastradas."); return; }

    puts("\n=== Cartas cadastradas ===");
    for (int i = 0; i < QTD; ++i) {
        if (!CARTAS[i].ativo) continue;
        printf("\n[%d] %s\n", i + 1, CARTAS[i].nome);
        for (int a = 0; a < ATTR_COUNT; ++a) {
            printf("  - %s: %.4f\n", ATTR_LABELS[a], CARTAS[i].attr[a]);
        }
    }
}

int escolher_indice_carta(const char *prompt) {
    if (QTD == 0) { puts("Nao ha cartas para escolher."); return -1; }
    listar_cartas();
    int idx = ler_int_faixa(prompt, 1, QTD) - 1;
    if (!CARTAS[idx].ativo) {
        puts("Carta inativa. Escolha outra.");
        return -1;
    }
    return idx;
}

/* -------------------- CADASTRO ------------------------------------------- */
void cadastrar_ou_atualizar(void) {
    if (QTD >= MAX_CARDS) {
        puts("Limite de cartas atingido.");
        return;
    }

    puts("\n=== Cadastrar/Atualizar carta ===");
    printf("Nome (pais/cidade): ");
    char nome[NAME_LEN];
    ler_linha(nome, sizeof(nome));
    if (nome[0] == '\0') { puts("Nome vazio nao pode."); return; }

    /* Verifica se já existe -> atualiza */
    int pos = -1;
    for (int i = 0; i < QTD; ++i) {
        if (CARTAS[i].ativo && strcasecmp(CARTAS[i].nome, nome) == 0) { pos = i; break; }
    }

    if (pos == -1) {
        pos = QTD++;
        CARTAS[pos].ativo = 1;
        strncpy(CARTAS[pos].nome, nome, NAME_LEN-1);
        CARTAS[pos].nome[NAME_LEN-1] = '\0';
        puts("Nova carta criada!");
    } else {
        puts("Carta encontrada: atualizando valores.");
    }

    for (int a = 0; a < ATTR_COUNT; ++a) {
        char msg[128];
        snprintf(msg, sizeof(msg), "%s: ", ATTR_LABELS[a]);
        CARTAS[pos].attr[a] = ler_double(msg);
    }

    puts("Carta salva com sucesso!");
}

/* -------------------- ATRIBUTOS: menu e escolha -------------------------- */
void mostrar_atributos(void) {
    puts("\nAtributos disponiveis:");
    for (int i = 0; i < ATTR_COUNT; ++i) {
        printf("%d) %s\n", i + 1, ATTR_LABELS[i]);
    }
}

int escolher_atributo(int proibido /* -1 se nenhum */) {
    while (1) {
        int op = ler_int_faixa("Numero do atributo: ", 1, ATTR_COUNT) - 1;
        if (op == proibido) {
            puts("Esse ja foi escolhido. Pegue outro.");
            continue;
        }
        return op;
    }
}

/* -------------------- COMPARACAO E DESEMPATE ----------------------------- */
/* Retorno: -1 se A<B, 0 se A==B, 1 se A>B  (maior vence) */
int cmp_attr(double a, double b) {
    if (a < b) return -1;
    if (a > b) return 1;
    return 0;
}

/* média simples dos 5 atributos (maior vence) */
double media_carta(const Carta *c) {
    double s = 0.0;
    for (int i = 0; i < ATTR_COUNT; ++i) s += c->attr[i];
    return s / ATTR_COUNT;
}

void comparar(void) {
    if (QTD < 2) { puts("Cadastre pelo menos duas cartas primeiro."); return; }

    puts("\n=== Comparar cartas (2 atributos) ===");
    int i1 = -1, i2 = -1;

    while (i1 == -1) i1 = escolher_indice_carta("Escolha a carta 1 (numero): ");
    while (i2 == -1 || i2 == i1) {
        i2 = escolher_indice_carta("Escolha a carta 2 (numero): ");
        if (i2 == i1) puts("Nao pode comparar a carta com ela mesma.");
    }

    printf("\nCarta 1: %s\n", CARTAS[i1].nome);
    printf("Carta 2: %s\n", CARTAS[i2].nome);

    mostrar_atributos();
    printf("Escolha o ATRIBUTO PRINCIPAL:\n");
    int a1 = escolher_atributo(-1);

    printf("Escolha o ATRIBUTO SECUNDARIO (diferente do anterior):\n");
    int a2 = escolher_atributo(a1);

    /* 1) compara atributo principal */
    int r = cmp_attr(CARTAS[i1].attr[a1], CARTAS[i2].attr[a1]);

    /* operador ternário só para ilustrar (nível "mestre"): */
    printf("\nResultado Atributo 1 (%s): %s\n",
           ATTR_LABELS[a1],
           (r > 0 ? "Carta 1 venceu" : (r < 0 ? "Carta 2 venceu" : "Empate")));

    if (r == 0) {
        /* 2) desempata com atributo secundário */
        int r2 = cmp_attr(CARTAS[i1].attr[a2], CARTAS[i2].attr[a2]);
        printf("Resultado Atributo 2 (%s): %s\n",
               ATTR_LABELS[a2],
               (r2 > 0 ? "Carta 1 venceu" : (r2 < 0 ? "Carta 2 venceu" : "Empate")));

        if (r2 == 0) {
            /* 3) desempate pela média de TODOS os atributos */
            double m1 = media_carta(&CARTAS[i1]);
            double m2 = media_carta(&CARTAS[i2]);
            int rm = cmp_attr(m1, m2);
            printf("Desempate pela media geral: (C1=%.4f, C2=%.4f) -> %s\n",
                   m1, m2, (rm > 0 ? "Carta 1 venceu" : (rm < 0 ? "Carta 2 venceu" : "Empate")));

            if (rm == 0) {
                /* 4) se continuar empate, sorteio aleatório */
                int vencedor = (rand() % 2 == 0) ? 1 : 2;
                printf("Tudo empatado! Sorteio aleatorio -> Vencedor: Carta %d (%s)\n",
                       vencedor, vencedor == 1 ? CARTAS[i1].nome : CARTAS[i2].nome);
            } else {
                printf("Vencedor final: %s\n", rm > 0 ? CARTAS[i1].nome : CARTAS[i2].nome);
            }
        } else {
            printf("Vencedor final: %s\n", r2 > 0 ? CARTAS[i1].nome : CARTAS[i2].nome);
        }
    } else {
        printf("Vencedor final: %s\n", r > 0 ? CARTAS[i1].nome : CARTAS[i2].nome);
    }
}

/* -------------------- SEED E DADOS DE EXEMPLO (opcional) ------------------ */
void inserir_exemplos(void) {
    /* ajuda quem está começando: já entrar com alguns dados */
    const char *nomes[] = {"Brasil", "Estados Unidos", "Japao"};
    double dados[][ATTR_COUNT] = {
        /* pop, area,  idh,  pib,  turismo */
        {203.1, 8515767.0, 0.765, 1930.0, 65.0}, /* Brasil (valores ilustrativos) */
        {333.0, 9833517.0, 0.926, 27700.0, 80.0},/* EUA (ilustrativos) */
        {125.0, 377975.0,  0.925, 4230.0,  90.0} /* Japao (ilustrativos) */
    };
    int n = (int)(sizeof(nomes)/sizeof(nomes[0]));

    for (int i = 0; i < n && QTD < MAX_CARDS; ++i) {
        strncpy(CARTAS[QTD].nome, nomes[i], NAME_LEN-1);
        CARTAS[QTD].nome[NAME_LEN-1] = '\0';
        for (int a = 0; a < ATTR_COUNT; ++a) CARTAS[QTD].attr[a] = dados[i][a];
        CARTAS[QTD].ativo = 1;
        QTD++;
    }
}

/* -------------------- MENU PRINCIPAL ------------------------------------- */
int menu(void) {
    puts("\n===== SUPER TRUNFO - PAISES/CIDADES =====");
    puts("1) Cadastrar/Atualizar carta");
    puts("2) Listar cartas");
    puts("3) Comparar cartas (escolher 2 atributos)");
    puts("0) Sair");
    return ler_int_faixa("Escolha: ", 0, 3);
}

/* -------------------- MAIN ------------------------------------------------ */
int main(void) {
    srand((unsigned)time(NULL)); /* para o sorteio do desempate */

    inserir_exemplos(); /* opcional (pode remover se quiser começar do zero) */

    while (1) {
        int op = menu();
        switch (op) {
            case 1: cadastrar_ou_atualizar(); pausar(); break;
            case 2: listar_cartas();           pausar(); break;
            case 3: comparar();                pausar(); break;
            case 0: puts("Ate mais!"); return 0;
            default: puts("Opcao invalida.");
        }
    }
    return 0;
}