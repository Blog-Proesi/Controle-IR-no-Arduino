/*
Proesi componentes Eletronicos
Autor: Venancio Miranda

Programa teste para modulo IR controle e recptoor Keyes
Ultima revisão 08/2021
*/

#define DECODE_NEC          1
#include <IRremote.h>

#define LED 8

int IR_RECEIVE_PIN = 11, ledum = 0, comando = 0;

void setup() 
{
    Serial.begin(9600);
    

    pinMode(LED, OUTPUT);
    
    IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK); // inicia o receptor no pino definido, habilita feedback do receptor

    Serial.print(F("Pronto para receber o sinal do controle"));
    Serial.println(IR_RECEIVE_PIN);

    ledum = LOW; // Variavel ledum inicia com valor LOW
}

void loop() 
{
    comando = 0;
    digitalWrite(LED, ledum); //Liga ou desliga saída LED de acordo com valor gravado em ledum
    if (IrReceiver.decode())
    {
        IrReceiver.printIRResultShort(&Serial);
        comando = (IrReceiver.decodedIRData.command); //armazena valor lido
        delay(500);
        Serial.println(IrReceiver.decodedIRData.command);//imprimi valor lado na porta serial
        Serial.println(); //imprimi uma quebra de linha
        IrReceiver.resume(); //prepara programa para nova captura
    }
    
    if(comando == 70)
    {
        ledum = !ledum; //caso o valor tecla com valor 70 seja prescionada, inverte o valor de ledum de LOW <-> HIGH e vice versa.
    }
}   
