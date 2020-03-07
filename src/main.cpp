/*
 *     main.cpp - 05-pwm-var
 *
 *         Usando PWM, realizar una barrida continua
 *         variando la intensidad del LED de minimo a
 *         maximo y de maximo a minimo
 *
 *         Usada para mostrar las instrucciones de
 *         control de repeticion 'while' y 'for'
 */

#include <Arduino.h>

/*
 *     Definiciones
 *      constantes definidas en platformio.ini
 *          LED1        Led IOPort
 *          ANAIN       A/D converter IOPort
 *      constante definida por el ambiente:
 *          ESP32       solo existe en ESP32 SoC
 */

/*
 *     otra forma de definir constantes
 *     como si fuesen variables inicializadas
 *     que no cambian
 * 
 */

const long LOOP_DELAY = 2;
const int MIN_VALUE = 0;
const int MAX_VALUE = 1023;

#ifdef ESP32
// setting PWM properties
const int freq = 5000;
const int ledChannel = 0;
const int resolution = 10;
#endif

/*
 *     Funciones auxiliares
 */

/*
 *  write_with_delay:
 *      Receives value of PWM to set
 */

void
write_with_delay(int value)
{
#ifdef ESP32
    ledcWrite(ledChannel, value);
#else
    analogWrite( LED1, value );
#endif
    delay(LOOP_DELAY);
}

/*
 *  configure_pwm:
 */

void
configure_pwm(void)
{
#ifdef ESP32
    // configure LED PWM functionalitites
    ledcSetup(ledChannel, freq, resolution);

    // attach the channel to the GPIO to be controlled
    ledcAttachPin(LED1, ledChannel);
#endif
}

/*
 *  up_ramp:
 *      Sets PWM value from Min to Max value
 */

void
up_ramp(void)
{
    int value;

    Serial.println(__FUNCTION__);
    value = MIN_VALUE;
    while (value <= MAX_VALUE)
    {
        write_with_delay(value);
        value++; // value = value + 1 o value += 1
    }
}

/*
 *  down_ramp:
 *      Sets PWM value from Max to Min value
 */

void
down_ramp(void)
{
    int value;

    Serial.println(__FUNCTION__);
    for (value = MAX_VALUE - 1; value > MIN_VALUE; --value)
        write_with_delay(value);
}

/*
 *  main functions
 */

void
setup()
{
    Serial.begin(SERIAL_BAUD);
    configure_pwm();
}

void
loop()
{
    up_ramp();
    down_ramp();
}
