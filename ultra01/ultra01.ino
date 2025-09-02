// Sensor Ultrassônico HC-SR04
// Pinos
const int trigPin = 4;
const int echoPin = 5;

// Variáveis
long duracao;
int distancia;

void setup() {
  // Configura os pinos
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  // Inicia a comunicação serial
  Serial.begin(9600);
  Serial.println("Sensor HC-SR04 iniciado!");
}

void loop() {
  // Limpa o pino trigger
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Envia pulso de 10 microssegundos
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Lê o tempo do pulso no pino echo
  duracao = pulseIn(echoPin, HIGH);
  
  // Calcula a distância em centímetros
  // Velocidade do som = 343 m/s = 0.0343 cm/µs
  // Distância = (tempo * velocidade) / 2
  distancia = duracao * 0.0343 / 2;
  
  // Mostra o resultado no monitor serial
  Serial.print("Distância: ");
  Serial.print(distancia);
  Serial.println(" cm");
  
  // Aguarda 500ms antes da próxima leitura
  delay(500);
}