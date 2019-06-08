int unlock= 2;
int lock= 4;
int trunk= 7;
int ignition= 8;
int panic= 12;
int standard_time= 250;

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
Open_Trunk();
Close_Trunk();
Start_Car();
Panic();
}

void Unlock() //function for unlock 2 clicks
{
digitalWrite(unlock, HIGH);
delay(standard_time); // Wait for standard_time millisecond(s)
digitalWrite(unlock, LOW);
delay(standard_time); // Wait for standard_time millisecond(s)
digitalWrite(unlock, HIGH);
delay(standard_time); // Wait for standard_time millisecond(s)
digitalWrite(unlock, LOW);
delay(standard_time); // Wait for standard_time millisecond(s)
}

void Lock() //function for lock 2 clicks
{
digitalWrite(lock, HIGH);
delay(standard_time); // Wait for standard_time millisecond(s)
digitalWrite(lock, LOW);
delay(standard_time); // Wait for standard_time millisecond(s)
digitalWrite(lock, HIGH);
delay(standard_time); // Wait for standard_time millisecond(s)
digitalWrite(lock, LOW);
delay(standard_time); // Wait for standard_time millisecond(s)
}

void Trunk() //function for trunk 2 clicks
{
digitalWrite(trunk, HIGH);
delay(standard_time); // Wait for standard_time millisecond(s)
digitalWrite(trunk, LOW);
delay(standard_time); // Wait for standard_time millisecond(s)
digitalWrite(trunk, HIGH);
delay(standard_time); // Wait for standard_time millisecond(s)
digitalWrite(trunk, LOW);
delay(standard_time); // Wait for standard_time millisecond(s)
}

void Ignition() //function for ignition 2 clicks
{
digitalWrite(ignition, HIGH);
delay(standard_time); // Wait for standard_time millisecond(s)
digitalWrite(ignition, LOW);
delay(standard_time); // Wait for standard_time millisecond(s)
digitalWrite(ignition, HIGH);
delay(standard_time); // Wait for standard_time millisecond(s)
digitalWrite(ignition, LOW);
delay(standard_time); // Wait for standard_time millisecond(s)
}

void Panic() //function for panic 1 click
{
digitalWrite(panic, HIGH);
delay(standard_time); // Wait for standard_time millisecond(s)
digitalWrite(panic, LOW);
delay(standard_time); // Wait for standard_time millisecond(s)
}

//Open Trunk 
//------------------------------------------------------------------
/*Logic: 
 * First we must lock the car doors and then open the trunk door
 */
//------------------------------------------------------------------

void Open_Trunk()
{
Lock();
Trunk();
}

//Close Trunk 
//------------------------------------------------------------------
/*Logic: 
 * Press the trunk button again. This function will only run if trunk 
 * is actually open
 */
//------------------------------------------------------------------
void Close_Trunk()
{
Trunk();
}

//Start Car
//------------------------------------------------------------------
/*Logic: 
 * First we must lock the car doors and then Press the car ignition
 */
//------------------------------------------------------------------
void Start_Car()
{
Lock();
Ignition();
}
