#include <Servo.h>
#include <stdlib.h>
int enablePin1 = 9;
int enablePin2 = 10;
int MotorLeft1 = 4;
int MotorLeft2 = 5;
int MotorRight1 = 2;
int MotorRight2 = 3;
int counter = 0;
const int maxSpeed = 100;
int rightServoSpeed = 100;
int leftServoSpeed = 100;
float p = 1.0;
float decision = (rand()) / (RAND_MAX + 1.0);
float lr = 0.1;
int Rnum = 0, Lnum = 0;
int i;
int last;
char val;
const int servo = 8;
int inputPin = 12;
int outputPin = 11;
int Fspeedd = 0;
int Rspeedd = 0;
int Lspeedd = 0;
int directionn = 8;
Servo myservo;
int Fgo = 8;
int Rgo = 6;
int Lgo = 4;
int Bgo = 2;

void setup()
{
    Serial.begin(9600);
    pinMode(MotorRight1, OUTPUT);
    pinMode(MotorRight2, OUTPUT);
    pinMode(MotorLeft1, OUTPUT);
    pinMode(MotorLeft2, OUTPUT);

    pinMode(inputPin, INPUT);
    pinMode(outputPin, OUTPUT);
    myservo.attach(servo);
}

void advance(int a)
{
    if ((last == 4) || (last == 6))
    {
        digitalWrite(MotorLeft1, HIGH);
        digitalWrite(MotorLeft2, LOW);
        digitalWrite(MotorRight1, HIGH);
        digitalWrite(MotorRight2, LOW);
        delay(100);
        digitalWrite(MotorLeft1, LOW);
        digitalWrite(MotorLeft2, LOW);
        digitalWrite(MotorRight1, LOW);
        digitalWrite(MotorRight2, LOW);
        delay(100);
    }
    digitalWrite(MotorLeft1, HIGH);
    digitalWrite(MotorLeft2, LOW);
    digitalWrite(MotorRight1, HIGH);
    digitalWrite(MotorRight2, LOW);
    delay(a * 10);
}

void turnR(int d)
{
    digitalWrite(MotorLeft1, LOW);
    digitalWrite(MotorLeft2, HIGH);
    digitalWrite(MotorRight1, HIGH);
    digitalWrite(MotorRight2, LOW);
    delay(d * 10);
    digitalWrite(MotorLeft1, LOW);
    digitalWrite(MotorLeft2, LOW);
    digitalWrite(MotorRight1, LOW);
    digitalWrite(MotorRight2, LOW);
    delay(300);
    digitalWrite(MotorLeft1, HIGH);
    digitalWrite(MotorLeft2, LOW);
    digitalWrite(MotorRight1, HIGH);
    digitalWrite(MotorRight2, LOW);
    delay(50);
    digitalWrite(MotorLeft1, LOW);
    digitalWrite(MotorLeft2, LOW);
    digitalWrite(MotorRight1, LOW);
    digitalWrite(MotorRight2, LOW);
    delay(300);
    digitalWrite(MotorLeft1, HIGH);
    digitalWrite(MotorLeft2, LOW);
    digitalWrite(MotorRight1, HIGH);
    digitalWrite(MotorRight2, LOW);
    delay(50);
    digitalWrite(MotorLeft1, LOW);
    digitalWrite(MotorLeft2, LOW);
    digitalWrite(MotorRight1, LOW);
    digitalWrite(MotorRight2, LOW);
    delay(300);
    digitalWrite(MotorLeft1, HIGH);
    digitalWrite(MotorLeft2, LOW);
    digitalWrite(MotorRight1, HIGH);
    digitalWrite(MotorRight2, LOW);
    delay(50);
    digitalWrite(MotorLeft1, LOW);
    digitalWrite(MotorLeft2, LOW);
    digitalWrite(MotorRight1, LOW);
    digitalWrite(MotorRight2, LOW);
    delay(100);
}

void turnL(int e)
{
    digitalWrite(MotorLeft1, HIGH);
    digitalWrite(MotorLeft2, LOW);
    digitalWrite(MotorRight1, LOW);
    digitalWrite(MotorRight2, HIGH);
    delay(e * 10);
    digitalWrite(MotorLeft1, LOW);
    digitalWrite(MotorLeft2, LOW);
    digitalWrite(MotorRight1, LOW);
    digitalWrite(MotorRight2, LOW);
    delay(300);
    digitalWrite(MotorLeft1, HIGH);
    digitalWrite(MotorLeft2, LOW);
    digitalWrite(MotorRight1, HIGH);
    digitalWrite(MotorRight2, LOW);
    delay(50);
    digitalWrite(MotorLeft1, LOW);
    digitalWrite(MotorLeft2, LOW);
    digitalWrite(MotorRight1, LOW);
    digitalWrite(MotorRight2, LOW);
    delay(300);
    digitalWrite(MotorLeft1, HIGH);
    digitalWrite(MotorLeft2, LOW);
    digitalWrite(MotorRight1, HIGH);
    digitalWrite(MotorRight2, LOW);
    delay(50);
    digitalWrite(MotorLeft1, LOW);
    digitalWrite(MotorLeft2, LOW);
    digitalWrite(MotorRight1, LOW);
    digitalWrite(MotorRight2, LOW);
    delay(300);
    digitalWrite(MotorLeft1, HIGH);
    digitalWrite(MotorLeft2, LOW);
    digitalWrite(MotorRight1, HIGH);
    digitalWrite(MotorRight2, LOW);
    delay(50);
    digitalWrite(MotorLeft1, LOW);
    digitalWrite(MotorLeft2, LOW);
    digitalWrite(MotorRight1, LOW);
    digitalWrite(MotorRight2, LOW);
    delay(80);
}

void stopp(int f)
{
    digitalWrite(MotorLeft1, LOW);
    digitalWrite(MotorLeft2, LOW);
    digitalWrite(MotorRight1, LOW);
    digitalWrite(MotorRight2, LOW);
    delay(f * 5);
}

void back(int g)
{
    digitalWrite(MotorLeft1, LOW);
    digitalWrite(MotorLeft2, HIGH);
    ;
    digitalWrite(MotorRight1, LOW);
    digitalWrite(MotorRight2, HIGH);
    delay(100);
    digitalWrite(MotorLeft1, LOW);
    digitalWrite(MotorLeft2, LOW);
    digitalWrite(MotorRight1, LOW);
    digitalWrite(MotorRight2, LOW);
    delay(300);
    digitalWrite(MotorLeft1, LOW);
    digitalWrite(MotorLeft2, HIGH);
    ;
    digitalWrite(MotorRight1, LOW);
    digitalWrite(MotorRight2, HIGH);
    delay(g * 100);
    digitalWrite(MotorLeft1, LOW);
    digitalWrite(MotorLeft2, LOW);
    digitalWrite(MotorRight1, LOW);
    digitalWrite(MotorRight2, LOW);
    delay(80);
}

void ask_pin_F()
{
    myservo.write(79);
    delay(70);
    digitalWrite(outputPin, LOW);
    delayMicroseconds(2);
    digitalWrite(outputPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(outputPin, LOW);
    float Fdistance = pulseIn(inputPin, HIGH);
    Fdistance = Fdistance / 5.8 / 10 - 5;
    Fspeedd = Fdistance - 2;
    if ((Fspeedd <= 30) && (directionn == 8))
    {
        stopp(20);
        Fspeedd -= 10;
    }
    if (Fspeedd <= 20)
    {
        stopp(20);
        Fspeedd = Fdistance;
    }

    myservo.write(149);
    delay(63);
    digitalWrite(outputPin, LOW);
    delayMicroseconds(2);
    digitalWrite(outputPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(outputPin, LOW);
    float FdistanceL = pulseIn(inputPin, HIGH);
    FdistanceL = FdistanceL / 5.8 / 10 - 15;
    delayMicroseconds(5);
    if (last != 8)
    {
        FdistanceL -= 13;
    }
    if ((Fspeedd <= 37) && (directionn == 8))
    {
        stopp(20);
        FdistanceL -= 22;
    }
    if (Fspeedd <= 26)
    {
        stopp(20);
        FdistanceL -= 11;
    }
    if (FdistanceL < Fspeedd)
    {
        Fspeedd = FdistanceL;
    }

    myservo.write(28);
    delay(150);
    digitalWrite(outputPin, LOW);
    delayMicroseconds(2);
    digitalWrite(outputPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(outputPin, LOW); //
    float FdistanceR = pulseIn(inputPin, HIGH);
    FdistanceR = FdistanceR / 5.8 / 10 - 7;

    delayMicroseconds(2);
    if (FdistanceR < Fspeedd)
    {
        Fspeedd = FdistanceR;
    }
    if ((Fspeedd <= 30) && (directionn == 8))
    {
        stopp(20);
        FdistanceR = FdistanceR - 17;
    }
    else if (Fspeedd <= 15)
    {
        stopp(20);
        FdistanceR -= 4;
    }
    if (FdistanceL < Fspeedd)
    {
        Fspeedd = FdistanceR;
    }
    delayMicroseconds(5);
    myservo.write(79)
}

void ask_pin_L()
{
    delay(10);
    myservo.write(177);
    delay(100);
    digitalWrite(outputPin, LOW);
    delayMicroseconds(2);
    digitalWrite(outputPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(outputPin, LOW);
    float Ldistance = pulseIn(inputPin, HIGH);
    Ldistance = Ldistance / 5.8 / 10;
    Lspeedd = Ldistance;
    delay(10);
}

void ask_pin_R()
{
    delay(10);
    myservo.write(0);
    delay(180);
    digitalWrite(outputPin, LOW);
    delayMicroseconds(2);
    digitalWrite(outputPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(outputPin, LOW);
    float Rdistance = pulseIn(inputPin, HIGH);
    Rdistance = Rdistance / 5.8 / 10;
    // Serial.print("R distance:");
    // Serial.println(Rdistance);
    Rspeedd = Rdistance;
    delay(10);
}

void detection()
{

    ask_pin_F();

    if (Fspeedd < 21)
    {
        stopp(20);
        back(2);
    }
    if ((Fspeedd >= 30) && (last != 2))
    {
        directionn = 8;
    }
    else
    {
        stopp(2);
        ask_pin_L();
        ask_pin_R();
        myservo.write(79);
        delay(80);

        if ((Lspeedd >= 25) && (Rspeedd >= 25))
        {
            decision = (rand()) / (RAND_MAX + 1.0);
            decision = p * decision;
            if (decision < 0.5)
            {
                directionn = Lgo;
                Rnum = 0;
                Lnum++;
                if (Lnum == 1)
                {
                    p = 0.5 - lr;
                }
                else if (Lnum == 2)
                {
                    p = 0.5 + 2 * lr;
                }
                else
                {
                    p = p + lr;
                }
            }
            else
            {
                directionn = Rgo;
                Rnum++;
                Lnum = 0;
                if (Rnum == 1)
                {
                    p = 0.5 + lr;
                }
                else if (Rnum == 2)
                {
                    p = 0.5 - 2 * lr;
                }
                else
                {
                    p = p - lr;
                }
            }
        }
        else
        {
            if (Lspeedd > 20)
            {
                directionn = Lgo;
                p = p + lr;
            }
            else if (Rspeedd > 20)
            {
                directionn = Rgo;
                p = p - lr;
            }
        }

        if (Lspeedd < 20 && Rspeedd < 20)
        {
            directionn = Bgo;
        }
    }
}

void loop()
{
    detection();
    if (directionn == 8)
    {
        advance(10);
        last = 8;
    }
    if (directionn == 2)
    {
        back(5);
        last = 2;
    }
    if (directionn == 4)
    {

        turnL(26);
        last = 4;
    }
    if (directionn == 6)
    {

        turnR(26);
        last = 6;
    }
}