int unlock= 2;
int lock= 4;
int trunk= 7;
int ignition= 8;
int panic= 12;

void setup()
{
pinMode(unlock, OUTPUT); //Unlock button on FOB
pinMode(lock, OUTPUT); //Lock button on FOB
pinMode(trunk, OUTPUT); //Trunk button on FOB
pinMode(ignition, OUTPUT); //Ignition button on FOB
pinMode(panic, OUTPUT); //Panic button on FOB
}

void loop()
{
Unlock();
Lock();
Trunk();
Ignition();
Panic();
}

void Unlock()
{
digitalWrite(unlock, HIGH);
delay(250); // Wait for 250 millisecond(s)
digitalWrite(unlock, LOW);
delay(250); // Wait for 250 millisecond(s)
digitalWrite(unlock, HIGH);
delay(250); // Wait for 250 millisecond(s)
digitalWrite(unlock, LOW);
delay(250); // Wait for 250 millisecond(s)
}

void Lock()
{
digitalWrite(lock, HIGH);
delay(250); // Wait for 250 millisecond(s)
digitalWrite(lock, LOW);
delay(250); // Wait for 250 millisecond(s)
digitalWrite(lock, HIGH);
delay(250); // Wait for 250 millisecond(s)
digitalWrite(lock, LOW);
delay(250); // Wait for 250 millisecond(s)
}

void Trunk()
{
digitalWrite(trunk, HIGH);
delay(250); // Wait for 250 millisecond(s)
digitalWrite(trunk, LOW);
delay(250); // Wait for 250 millisecond(s)
digitalWrite(trunk, HIGH);
delay(250); // Wait for 250 millisecond(s)
digitalWrite(trunk, LOW);
delay(250); // Wait for 250 millisecond(s)
}

void Ignition()
{
digitalWrite(ignition, HIGH);
delay(250); // Wait for 250 millisecond(s)
digitalWrite(ignition, LOW);
delay(250); // Wait for 250 millisecond(s)
digitalWrite(ignition, HIGH);
delay(250); // Wait for 250 millisecond(s)
digitalWrite(ignition, LOW);
delay(250); // Wait for 250 millisecond(s)
}

void Panic()
{
digitalWrite(panic, HIGH);
delay(250); // Wait for 250 millisecond(s)
digitalWrite(panic, LOW);
delay(250); // Wait for 250 millisecond(s)
}
