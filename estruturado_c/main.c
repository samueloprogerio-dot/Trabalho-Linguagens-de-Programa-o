/*
 * Atividade Avaliativa Final - Problema 1
 * Samuel de Oliveira Pinheiro Rogerio - RA 1260101643
 * Miguel da Silva Moura - RA 1260113472
 * Isaac Gabriel Pereira Rocha - RA 1260123852
 * Victor Hugo Barborino Moura de Vasconcellos - RA 1260122456
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_NOME 100
#define MEDIA_APROVACAO 7.0

typedef struct {
    char nome[TAM_NOME];
    double *notas;
    int quantidadeNotas;
    double media;
} Aluno;

void limparEntrada(void) {
    int caractere;
    while ((caractere = getchar()) != '\n' && caractere != EOF) {
    }
}

int lerInteiroPositivo(const char *mensagem) {
    int valor;

    while (1) {
        printf("%s", mensagem);
        if (scanf("%d", &valor) == 1 && valor > 0) {
            limparEntrada();
            return valor;
        }

        printf("Valor invalido. Digite um numero inteiro maior que zero.\n");
        limparEntrada();
    }
}

double lerNota(const char *mensagem) {
    double nota;

    while (1) {
        printf("%s", mensagem);
        if (scanf("%lf", &nota) == 1 && nota >= 0.0 && nota <= 10.0) {
            limparEntrada();
            return nota;
        }

        printf("Nota invalida. Digite um valor entre 0 e 10.\n");
        limparEntrada();
    }
}

void lerNome(char *nome) {
    while (1) {
        printf("Nome: ");
        if (fgets(nome, TAM_NOME, stdin) != NULL) {
            nome[strcspn(nome, "\n")] = '\0';
            if (strlen(nome) > 0) {
                return;
            }
        }
        printf("O nome nao pode ficar vazio.\n");
    }
}

double calcularMedia(const double notas[], int quantidade) {
    double soma = 0.0;

    for (int i = 0; i < quantidade; i++) {
        soma += notas[i];
    }

    return soma / quantidade;
}

const char *determinarSituacao(double media) {
    return media >= MEDIA_APROVACAO ? "Aprovado" : "Reprovado";
}

int compararAlunosPorNome(const void *primeiro, const void *segundo) {
    const Aluno *alunoA = (const Aluno *)primeiro;
    const Aluno *alunoB = (const Aluno *)segundo;
    return strcmp(alunoA->nome, alunoB->nome);
}

double calcularMediaGeral(const Aluno alunos[], int quantidadeAlunos) {
    double soma = 0.0;

    for (int i = 0; i < quantidadeAlunos; i++) {
        soma += alunos[i].media;
    }

    return soma / quantidadeAlunos;
}

void encontrarMaiorEMenorNota(
    const Aluno alunos[],
    int quantidadeAlunos,
    double *maiorNota,
    double *menorNota
) {
    *maiorNota = alunos[0].notas[0];
    *menorNota = alunos[0].notas[0];

    for (int i = 0; i < quantidadeAlunos; i++) {
        for (int j = 0; j < alunos[i].quantidadeNotas; j++) {
            if (alunos[i].notas[j] > *maiorNota) {
                *maiorNota = alunos[i].notas[j];
            }
            if (alunos[i].notas[j] < *menorNota) {
                *menorNota = alunos[i].notas[j];
            }
        }
    }
}

void exibirRelatorio(const Aluno alunos[], int quantidadeAlunos) {
    double maiorNota;
    double menorNota;

    encontrarMaiorEMenorNota(
        alunos,
        quantidadeAlunos,
        &maiorNota,
        &menorNota
    );

    printf("\n=== LISTAGEM ORDENADA ===\n");
    printf("%-30s %-10s %-12s\n", "Aluno", "Media", "Situacao");
    printf("--------------------------------------------------------\n");

    for (int i = 0; i < quantidadeAlunos; i++) {
        printf(
            "%-30s %-10.2f %-12s\n",
            alunos[i].nome,
            alunos[i].media,
            determinarSituacao(alunos[i].media)
        );
    }

    printf("\nMedia geral da turma: %.2f\n",
           calcularMediaGeral(alunos, quantidadeAlunos));
    printf("Maior nota registrada: %.2f\n", maiorNota);
    printf("Menor nota registrada: %.2f\n", menorNota);
}

void liberarMemoria(Aluno alunos[], int quantidadeAlunos) {
    for (int i = 0; i < quantidadeAlunos; i++) {
        free(alunos[i].notas);
    }
    free(alunos);
}

int main(void) {
    int quantidadeAlunos =
        lerInteiroPositivo("Quantidade de alunos: ");
    int quantidadeNotas =
        lerInteiroPositivo("Quantidade de notas por aluno: ");

    Aluno *alunos = calloc(quantidadeAlunos, sizeof(Aluno));
    if (alunos == NULL) {
        fprintf(stderr, "Erro: nao foi possivel reservar memoria.\n");
        return 1;
    }

    for (int i = 0; i < quantidadeAlunos; i++) {
        printf("\n--- Aluno %d ---\n", i + 1);
        lerNome(alunos[i].nome);
        alunos[i].quantidadeNotas = quantidadeNotas;
        alunos[i].notas = malloc(quantidadeNotas * sizeof(double));

        if (alunos[i].notas == NULL) {
            fprintf(stderr, "Erro: nao foi possivel reservar memoria.\n");
            liberarMemoria(alunos, i);
            return 1;
        }

        for (int j = 0; j < quantidadeNotas; j++) {
            char mensagem[40];
            snprintf(mensagem, sizeof(mensagem), "Nota %d: ", j + 1);
            alunos[i].notas[j] = lerNota(mensagem);
        }

        alunos[i].media =
            calcularMedia(alunos[i].notas, quantidadeNotas);
    }

    qsort(
        alunos,
        quantidadeAlunos,
        sizeof(Aluno),
        compararAlunosPorNome
    );

    exibirRelatorio(alunos, quantidadeAlunos);
    liberarMemoria(alunos, quantidadeAlunos);
    return 0;
}
// seco