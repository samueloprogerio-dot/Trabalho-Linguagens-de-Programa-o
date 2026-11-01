/*
 * Atividade Avaliativa Final - Problema 1
 * Samuel de Oliveira Pinheiro Rogerio - RA 1260101643
 * Miguel da Silva Moura - RA 1260113472
 * Isaac Gabriel Pereira Rocha - RA 1260123852
 * Victor Hugo Barborino Moura de Vasconcellos - RA 1260122456
 */

import java.util.InputMismatchException;
import java.util.Scanner;

public class Main {
    private static int lerInteiroPositivo(
        Scanner entrada,
        String mensagem
    ) {
        while (true) {
            try {
                System.out.print(mensagem);
                int valor = entrada.nextInt();
                entrada.nextLine();

                if (valor > 0) {
                    return valor;
                }
                System.out.println(
                    "Digite um numero inteiro maior que zero."
                );
            } catch (InputMismatchException erro) {
                System.out.println("Digite um numero inteiro valido.");
                entrada.nextLine();
            }
        }
    }

    private static String lerNome(Scanner entrada) {
        while (true) {
            System.out.print("Nome: ");
            String nome = entrada.nextLine().trim();

            if (!nome.isEmpty()) {
                return nome;
            }
            System.out.println("O nome nao pode ficar vazio.");
        }
    }

    private static double lerNota(Scanner entrada, int numero) {
        while (true) {
            try {
                System.out.printf("Nota %d: ", numero);
                double nota = entrada.nextDouble();
                entrada.nextLine();
                return nota;
            } catch (InputMismatchException erro) {
                System.out.println("Digite uma nota numerica valida.");
                entrada.nextLine();
            }
        }
    }

    public static void main(String[] args) {
        try (Scanner entrada = new Scanner(System.in)) {
            SistemaNotas sistema = new SistemaNotas();
            int quantidadeAlunos = lerInteiroPositivo(
                entrada,
                "Quantidade de alunos: "
            );
            int quantidadeNotas = lerInteiroPositivo(
                entrada,
                "Quantidade de notas por aluno: "
            );

            for (int i = 1; i <= quantidadeAlunos; i++) {
                System.out.printf("%n--- Aluno %d ---%n", i);
                Aluno aluno = new Aluno(lerNome(entrada));

                for (int j = 1; j <= quantidadeNotas; j++) {
                    boolean notaAdicionada = false;

                    while (!notaAdicionada) {
                        try {
                            aluno.adicionarNota(lerNota(entrada, j));
                            notaAdicionada = true;
                        } catch (NotaInvalidaException erro) {
                            System.out.println(erro.getMessage());
                        }
                    }
                }

                sistema.adicionarAluno(aluno);
            }

            sistema.exibirRelatorio();
        }
    }
}
