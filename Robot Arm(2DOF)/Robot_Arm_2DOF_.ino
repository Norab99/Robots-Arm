
#include <Servo.h>

int pinAttachM1 = 7;
int pinAttachM2 = 9;

Servo Motor1;
Servo Motor2;

int cw;  // To choose the way of the calculation.

// Forward Kinematic: Find X, Y and O.
// Choose cw = 1 to make the calculation for forward kinematic.
// Inverse Kinematic: Find O1 and O2.
// Choose cw = 2 to make the calculation for inverse kinematic.

float L1;    // The first length.
float L2;    // The second length.
float O1;    // The first angle(degree).
float O2;    // The second angle(degree).
float X;     // X cordinate of the end effector.
float Y;     // Y cordinate of the end effector.
float O;     // The total angle(degree).
float O1R;   // The first angle(radian).
float O2R;   // The second angle(radian).

void setup()
{
  
  Serial.begin(9600);
  Motor1.attach(pinAttachM1);
  Motor2.attach(pinAttachM2);
  
  Serial.println("Please enter the way of the calculation\n1 for farward kinematic\nand 2 for inverse kinematic:");
  while (Serial.available()==0) {}
  cw = Serial.parseInt();
  
  if (cw == 1) {     // If the user choose the forward kinematic.
    Serial.println("Please enter the first length L1:");
    while (Serial.available()==0) {}
    L1 = Serial.parseInt();
    Serial.println("Please enter the second length L2:");
    while (Serial.available()==0) {}
    L2 = Serial.parseInt();
    Serial.println("Please enter the first angle O1(degree):");
    while (Serial.available()==0) {}
    O1 = Serial.parseInt();
    Serial.println("Please enter the second angle O2(degree):");
    while (Serial.available()==0) {}
    O2 = Serial.parseInt();
    
    // Convert the angles from degree to radian.
    O1R = O1*3.14/180.0;    
    O2R = O2*3.14/180.0;
    
    // Calculate the (X,Y) cordinate of the end effector.
    X = L1*cos(O1R) + L2*cos(O1R+O2R);
    Serial.print("X cordinate is: ");
    Serial.println(X);
    Y = L1*sin(O1R) + L2*sin(O1R+O2R);
    Serial.print("Y cordinate is: ");
    Serial.println(Y);
    
    // Calculate the total angle.
    O = O1+O2;
    Serial.print("The total angle is: ");
    Serial.println(O);
  }
  
  else if (cw == 2){    // If the user choose the inverse kinematic.
    Serial.println("Please enter the first length L1:");
    while (Serial.available()==0) {}
    L1 = Serial.parseFloat();
    Serial.println("Please enter the second length L2:");
    while (Serial.available()==0) {}
    L2 = Serial.parseFloat();
    Serial.println("Please enter the x cordinate of the end effector:");
    while (Serial.available()==0) {}
    X = Serial.parseFloat();
    Serial.println("Please enter the y cordinate of the end effector:");
    while (Serial.available()==0) {}
    Y = Serial.parseFloat();
    Serial.println("Please enter the toltal angle O(degree):");
    while (Serial.available()==0) {}
    O = Serial.parseFloat();
    
    // Calculate the second angle(degree).
    float X2 = pow(X,2);
    float Y2 = pow(Y,2);
    float L12 = pow(L1,2);
    float L22 = pow(L2,2);
    float numerator = X2+Y2-L12-L22;
    float denominator = 2*L1*L2;
    float dev = numerator/denominator;
    O2R = acos(dev);
    O2 = O2R*180/3.14;
    
    
    // Calculate the first angle(degree).
    O1 = O-O2;
    
    Serial.print("The first angle(degree) is: ");
    Serial.println(O1);
    Serial.print("The second angle(degree) is: ");
    Serial.println(O2);
  }
}

void loop()
{
  // Move the first arm(first motor) O1(first angle) degree.
  Motor1.write(O1);
  
  // Wait the first motor to move and finish.
  delay(1000);
  
  // Move the second arm(second motor) O2(second angle) degree.
  Motor2.write(O2);
}
