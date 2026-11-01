import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class Aluno extends Pessoa implements Avaliavel {
    private static final double MEDIA_APROVACAO = 7.0;
    private final List<Double> notas;

    public Aluno(String nome) {
        super(nome);
        this.notas = new ArrayList<>();
    }

    public void adicionarNota(double nota) throws NotaInvalidaException {
        if (nota < 0.0 || nota > 10.0) {
            throw new NotaInvalidaException(
                "A nota deve estar entre 0 e 10."
            );
        }
        notas.add(nota);
    }

    public List<Double> getNotas() {
        return Collections.unmodifiableList(notas);
    }

    @Override
    public double calcularMedia() {
        return notas.stream()
            .mapToDouble(Double::doubleValue)
            .average()
            .orElse(0.0);
    }

    @Override
    public String determinarSituacao() {
        return calcularMedia() >= MEDIA_APROVACAO
            ? "Aprovado"
            : "Reprovado";
    }

    @Override
    public String resumo() {
        return String.format(
            "%-30s %-10.2f %-12s",
            getNome(),
            calcularMedia(),
            determinarSituacao()
        );
    }
}
