public abstract class Pessoa {
    private final String nome;

    protected Pessoa(String nome) {
        if (nome == null || nome.isBlank()) {
            throw new IllegalArgumentException("O nome nao pode ficar vazio.");
        }
        this.nome = nome.trim();
    }

    public String getNome() {
        return nome;
    }

    public abstract String resumo();
}
