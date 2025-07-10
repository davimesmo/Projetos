import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

# --- Configurações ---
NOME_ARQUIVO_CSV = 'resultados.csv' 
ESTILO_GRAFICO = "whitegrid"
# Configura o tema visual dos gráficos
sns.set_theme(style=ESTILO_GRAFICO, rc={"figure.figsize": (10, 6)})

# --- Carregamento dos Dados ---
try:
    # Lê os dados do arquivo CSV para um DataFrame do pandas
    df = pd.read_csv(NOME_ARQUIVO_CSV)
except FileNotFoundError:
    print(f"Erro: Arquivo '{NOME_ARQUIVO_CSV}' não encontrado!")
    print("Certifique-se de que o script está na mesma pasta que o arquivo de resultados.")
    exit()

# --- Preparação dos Dados ---
# Filtra os dados para usar apenas os do experimento de variação de eventos.
# Com base nos seus dados, o número de pacotes foi 100 e o de clientes foi 89.
df_eventos = df[(df['NumPacotes'] == 100) & (df['NumClientes'] == 89)].copy()

# Ordena os dados pela variável do eixo X para um gráfico limpo
df_eventos.sort_values(by='NumEventos', inplace=True)

print("Dados para análise de variação de eventos:")
print(df_eventos)

# =====================================================================================
# GRÁFICO: TEMPO DE PROCESSAMENTO vs. NÚMERO TOTAL DE EVENTOS
# =====================================================================================

# Cria uma nova figura para o gráfico
plt.figure()

# Cria o gráfico de linha usando a biblioteca seaborn
sns.lineplot(
    data=df_eventos,
    x='NumEventos',             # Eixo X: Agora é o Número Total de Eventos
    y='TempoProcessamento_s',   # Eixo Y: A métrica de desempenho
    marker='o',                 # Adiciona um marcador de círculo em cada ponto de dado
    linewidth=2.5,
    label='Tempo de Processamento'
)

# --- Customização do Gráfico ---
plt.title('Desempenho vs. Número Total de Eventos', fontsize=16)
plt.xlabel('Número Total de Eventos Processados', fontsize=12)
plt.ylabel('Tempo de Processamento (segundos)', fontsize=12)
plt.legend()
plt.grid(True)
plt.tight_layout() # Ajusta o layout para evitar que os títulos se sobreponham

# --- Salvando o Gráfico ---
NOME_ARQUIVO_GRAFICO = 'grafico_tempo_vs_eventos.png'
plt.savefig(NOME_ARQUIVO_GRAFICO)

print(f"\nGráfico '{NOME_ARQUIVO_GRAFICO}' gerado com sucesso!")

# Opcional: mostra o gráfico na tela ao executar o script
# plt.show()