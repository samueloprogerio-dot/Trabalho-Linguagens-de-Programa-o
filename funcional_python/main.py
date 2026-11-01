"""Atividade Avaliativa Final - Problema 1.

Integrantes:
Samuel de Oliveira Pinheiro Rogerio - RA 1260101643
Miguel da Silva Moura - RA 1260113472
Isaac Gabriel Pereira Rocha - RA 1260123852
Victor Hugo Barborino Moura de Vasconcellos - RA 1260122456
"""

from functools import reduce
from typing import NamedTuple


MEDIA_APROVACAO = 7.0


class Aluno(NamedTuple):
    nome: str
    notas: tuple[float, ...]


def soma_recursiva(valores: tuple[float, ...]) -> float:
    if not valores:
        return 0.0
    return valores[0] + soma_recursiva(valores[1:])


def calcular_media(notas: tuple[float, ...]) -> float:
    return soma_recursiva(notas) / len(notas)


def determinar_situacao(media: float) -> str:
    return "Aprovado" if media >= MEDIA_APROVACAO else "Reprovado"


def criar_resultado(aluno: Aluno) -> tuple[str, float, str]:
    media = calcular_media(aluno.notas)
    return aluno.nome, media, determinar_situacao(media)


def ordenar_resultados(
    resultados: tuple[tuple[str, float, str], ...],
) -> tuple[tuple[str, float, str], ...]:
    return tuple(sorted(resultados, key=lambda resultado: resultado[0].lower()))


def calcular_media_geral(
    resultados: tuple[tuple[str, float, str], ...],
) -> float:
    medias = tuple(map(lambda resultado: resultado[1], resultados))
    return reduce(lambda total, media: total + media, medias, 0.0) / len(medias)


def reunir_notas(alunos: tuple[Aluno, ...]) -> tuple[float, ...]:
    return reduce(
        lambda acumuladas, aluno: acumuladas + aluno.notas,
        alunos,
        (),
    )


def ler_inteiro_positivo(mensagem: str) -> int:
    while True:
        try:
            valor = int(input(mensagem))
            if valor > 0:
                return valor
            print("Digite um numero inteiro maior que zero.")
        except ValueError:
            print("Digite um numero inteiro valido.")


def ler_nome() -> str:
    while True:
        nome = input("Nome: ").strip()
        if nome:
            return nome
        print("O nome nao pode ficar vazio.")


def ler_nota(numero: int) -> float:
    while True:
        try:
            nota = float(input(f"Nota {numero}: ").replace(",", "."))
            if 0.0 <= nota <= 10.0:
                return nota
            print("A nota deve estar entre 0 e 10.")
        except ValueError:
            print("Digite uma nota numerica valida.")


def ler_notas_recursivamente(
    quantidade: int,
    numero_atual: int = 1,
) -> tuple[float, ...]:
    if numero_atual > quantidade:
        return ()
    return (ler_nota(numero_atual),) + ler_notas_recursivamente(
        quantidade,
        numero_atual + 1,
    )


def ler_alunos_recursivamente(
    quantidade_alunos: int,
    quantidade_notas: int,
    numero_atual: int = 1,
) -> tuple[Aluno, ...]:
    if numero_atual > quantidade_alunos:
        return ()

    print(f"\n--- Aluno {numero_atual} ---")
    aluno = Aluno(
        nome=ler_nome(),
        notas=ler_notas_recursivamente(quantidade_notas),
    )
    return (aluno,) + ler_alunos_recursivamente(
        quantidade_alunos,
        quantidade_notas,
        numero_atual + 1,
    )


def exibir_relatorio(alunos: tuple[Aluno, ...]) -> None:
    resultados = ordenar_resultados(tuple(map(criar_resultado, alunos)))
    todas_as_notas = reunir_notas(alunos)
    maior_nota = reduce(lambda a, b: a if a > b else b, todas_as_notas)
    menor_nota = reduce(lambda a, b: a if a < b else b, todas_as_notas)

    print("\n=== LISTAGEM ORDENADA ===")
    print(f"{'Aluno':<30} {'Media':<10} {'Situacao':<12}")
    print("-" * 56)

    tuple(
        map(
            lambda resultado: print(
                f"{resultado[0]:<30} "
                f"{resultado[1]:<10.2f} "
                f"{resultado[2]:<12}"
            ),
            resultados,
        )
    )

    aprovados = tuple(
        filter(lambda resultado: resultado[2] == "Aprovado", resultados)
    )

    print(f"\nMedia geral da turma: {calcular_media_geral(resultados):.2f}")
    print(f"Maior nota registrada: {maior_nota:.2f}")
    print(f"Menor nota registrada: {menor_nota:.2f}")
    print(f"Total de aprovados: {len(aprovados)}")


def main() -> None:
    quantidade_alunos = ler_inteiro_positivo("Quantidade de alunos: ")
    quantidade_notas = ler_inteiro_positivo(
        "Quantidade de notas por aluno: "
    )
    alunos = ler_alunos_recursivamente(
        quantidade_alunos,
        quantidade_notas,
    )
    exibir_relatorio(alunos)


if __name__ == "__main__":
    main()
