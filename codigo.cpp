unsigned long startTime;
unsigned long actualTime;
unsigned long period1;
unsigned long period2;
boolean firstPass;

void setup() {
    Serial.begin(9600);
    pinMode(12, INPUT_PULLUP); // Pullup, para impedir interferência externa
    startTime = micros();      // O tempo é medido em microsegundos
}

void loop() {
    actualTime = micros();    // Registra o tempo inicial
    if(pulseIn(12, HIGH)) {
        if(firstPass) {
            period1 = actualTime - startTime;
            firstPass = false;
            // Caso a emissão seja interceptada e o pêndulo realiza o primeiro cruzamento,
            // armazena-se period1, a primeira metade do período de oscilação.
        } else {
            // Caso contrário, armazena-se period2, a segunda metade do período de oscilação.
            period2 = actualTime - startTime;
            Serial.println(period1 + period2);
            // A porta serial exibe o período total, resultado da adição dos dois períodos
            firstPass = true;
        }
        startTime = actualTime;
        // Tempo inicial zerado para retornar à medição
    }
}