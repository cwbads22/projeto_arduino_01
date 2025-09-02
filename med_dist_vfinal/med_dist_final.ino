// Medidor de Nível de Líquido com HC-SR04 - Versão Estável
// Pinos
const int trigPin = 4;
const int echoPin = 5;

// Variáveis
long duracao;
int distanciaAtual;
int alturaRecipiente = 0;  // Altura total do recipiente (será calibrada)
int nivelLiquido = 0;      // Nível atual do líquido
int nivelAnterior = -1;    // Para detectar mudanças
int margemSeguranca = 5;   // Distância mínima do sensor (5cm)
int tolerancia = 1;        // Tolerância para mudanças (2cm)
int alturaUtil = 0;        // Altura útil (altura total - margem)
bool calibrado = false;

// Filtro de média móvel
const int numLeituras = 5;
int leituras[numLeituras];
int indiceLeitura = 0;
int somaLeituras = 0;
bool filtroInicializado = false;

void setup() {
  // Configura os pinos
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  // Inicializa array de leituras
  for (int i = 0; i < numLeituras; i++) {
    leituras[i] = 0;
  }
  
  // Inicia a comunicação serial
  Serial.begin(9600);
  Serial.println("=== MEDIDOR DE NIVEL DE LIQUIDO ===");
  Serial.println("1. Coloque o recipiente VAZIO");
  Serial.println("2. Envie qualquer caractere para calibrar");
}

void loop() {
  // Se ainda não calibrou, aguarda comando
  if (!calibrado) {
    if (Serial.available() > 0) {
      Serial.read(); // Limpa o buffer
      calibrarRecipiente();
    }
    return;
  }
  
  // Faz a leitura com filtro de média móvel
  distanciaAtual = lerDistanciaFiltrada();
  
  // Calcula o nível do líquido (considerando margem de segurança)
  nivelLiquido = alturaRecipiente - distanciaAtual;
  
  // Garante que não seja negativo e respeita a margem de segurança
  if (nivelLiquido < 0) nivelLiquido = 0;
  if (nivelLiquido > alturaUtil) nivelLiquido = alturaUtil;
  
  // Só mostra se houver mudança significativa no nível (acima da tolerância)
  if (abs(nivelLiquido - nivelAnterior) >= tolerancia) {
    Serial.print("Altura útil: ");
    Serial.print(alturaUtil);
    Serial.print(" cm | Nível atual: ");
    Serial.print(nivelLiquido);
    Serial.print(" cm (");
    Serial.print((nivelLiquido * 100) / alturaUtil);
    Serial.println("%)");
    
    // Aviso de segurança se chegar muito perto
    if (distanciaAtual <= margemSeguranca) {
      Serial.println("*** ATENÇÃO: NÍVEL MÁXIMO ATINGIDO! ***");
    }
    
    nivelAnterior = nivelLiquido;  // Atualiza o nível anterior
  }
  
  delay(200);  // Delay menor para resposta mais rápida
}

int lerDistancia() {
  // Limpa o pino trigger
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Envia pulso de 10 microssegundos
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Lê o tempo do pulso no pino echo
  duracao = pulseIn(echoPin, HIGH);
  
  // Calcula e retorna a distância
  return duracao * 0.0343 / 2;
}

int lerDistanciaFiltrada() {
  // Faz uma nova leitura
  int novaLeitura = lerDistancia();
  
  if (!filtroInicializado) {
    // Inicializa o filtro com a primeira leitura
    for (int i = 0; i < numLeituras; i++) {
      leituras[i] = novaLeitura;
    }
    somaLeituras = novaLeitura * numLeituras;
    filtroInicializado = true;
    return novaLeitura;
  }
  
  // Remove a leitura mais antiga da soma
  somaLeituras -= leituras[indiceLeitura];
  
  // Adiciona a nova leitura
  leituras[indiceLeitura] = novaLeitura;
  somaLeituras += novaLeitura;
  
  // Avança o índice (circular)
  indiceLeitura = (indiceLeitura + 1) % numLeituras;
  
  // Retorna a média
  return somaLeituras / numLeituras;
}

void calibrarRecipiente() {
  Serial.println("Calibrando...");
  delay(2000);  // Aguarda 2 segundos
  
  // Inicializa o filtro antes da calibração
  filtroInicializado = false;
  
  // Faz 10 leituras filtradas para obter uma calibração mais precisa
  int soma = 0;
  for (int i = 0; i < 10; i++) {
    soma += lerDistanciaFiltrada();
    delay(200);
  }
  
  alturaRecipiente = soma / 10;
  alturaUtil = alturaRecipiente - margemSeguranca;  // Desconta a margem
  calibrado = true;
  
  Serial.print("Calibração concluída! Altura total: ");
  Serial.print(alturaRecipiente);
  Serial.print(" cm | Altura útil: ");
  Serial.print(alturaUtil);
  Serial.print(" cm (margem segurança: ");
  Serial.print(margemSeguranca);
  Serial.println(" cm)");
  Serial.println("Agora você pode adicionar líquido...");
  Serial.println("(Mostrará apenas quando houver mudanças)");
  Serial.println();
}