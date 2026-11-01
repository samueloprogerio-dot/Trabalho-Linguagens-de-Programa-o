import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;

public class SistemaNotas {
    private final List<Aluno> alunos = new ArrayList<>();

    public void adicionarAluno(Aluno aluno) {
        if (aluno == null) {
            throw new IllegalArgumentException("O aluno nao pode ser nulo.");
        }
        alunos.add(aluno);
    }

    public double calcularMediaGeral() {
        return alunos.stream()
            .mapToDouble(Aluno::calcularMedia)
            .average()
            .orElse(0.0);
    }

    public double encontrarMaiorNota() {
        return alunos.stream()
            .flatMap(aluno -> aluno.getNotas().stream())
            .mapToDouble(Double::doubleValue)
            .max()
            .orElse(0.0);
    }

    public double encontrarMenorNota() {
        return alunos.stream()
            .flatMap(aluno -> aluno.getNotas().stream())
            .mapToDouble(Double::doubleValue)
            .min()
            .orElse(0.0);
    }

    public void exibirRelatorio() {
        alunos.sort(
            Comparator.comparing(
                Aluno::getNome,
                String.CASE_INSENSITIVE_ORDER
            )
        );

        System.out.println("\n=== LISTAGEM ORDENADA ===");
        System.out.printf(
            "%-30s %-10s %-12s%n",
            "Aluno",
            "Media",
            "Situacao"
        );
        System.out.println(
            "--------------------------------------------------------"
        );

        for (Aluno aluno : alunos) {
            Pessoa pessoa = aluno;
            System.out.println(pessoa.resumo());
        }

        System.out.printf(
            "%nMedia geral da turma: %.2f%n",
            calcularMediaGeral()
        );
        System.out.printf(
            "Maior nota registrada: %.2f%n",
            encontrarMaiorNota()
        );
        System.out.printf(
            "Menor nota registrada: %.2f%n",
            encontrarMenorNota()
        );
    }
}
