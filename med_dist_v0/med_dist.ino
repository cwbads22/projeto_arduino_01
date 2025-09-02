// Medidor de Nível de Líquido com HC-SR04
// Pinos
const int trigPin = 4;
const int echoPin = 5;

// Variáveis
long duracao;
int distanciaAtual;
int alturaRecipiente = 0;  // Altura total do recipiente (será calibrada)
int nivelLiquido = 0;      // Nível atual do líquido
bool calibrado = false;

void setup() {
  // Configura os pinos
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
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
  
  // Faz a leitura normal
  distanciaAtual = lerDistancia();
  
  // Calcula o nível do líquido
  nivelLiquido = alturaRecipiente - distanciaAtual;
  
  // Garante que não seja negativo
  if (nivelLiquido < 0) nivelLiquido = 0;
  if (nivelLiquido > alturaRecipiente) nivelLiquido = alturaRecipiente;
  
  // Mostra os resultados
  Serial.print("Altura recipiente: ");
  Serial.print(alturaRecipiente);
  Serial.print(" cm | Nível atual: ");
  Serial.print(nivelLiquido);
  Serial.print(" cm (");
  Serial.print((nivelLiquido * 100) / alturaRecipiente);
  Serial.println("%)");
  
  delay(1000);
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

void calibrarRecipiente() {
  Serial.println("Calibrando...");
  delay(2000);  // Aguarda 2 segundos
  
  // Faz 5 leituras para obter uma média mais precisa
  int soma = 0;
  for (int i = 0; i < 5; i++) {
    soma += lerDistancia();
    delay(200);
  }
  
  alturaRecipiente = soma / 5;
  calibrado = true;
  
  Serial.print("Calibração concluída! Altura do recipiente: ");
  Serial.print(alturaRecipiente);
  Serial.println(" cm");
  Serial.println("Agora você pode adicionar líquido...");
  Serial.println();
}