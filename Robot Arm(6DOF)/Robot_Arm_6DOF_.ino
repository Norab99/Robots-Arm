

int cw;  // To choose the way of the calculation.

// Forward Kinematic: Find p position and R rotation and orientation for the end effector.
// Choose cw = 1 to make the calculation for forward kinematic.
// Inverse Kinematic: Find joint angles Oi.
// Choose cw = 2 to make the calculation for inverse kinematic.

// Position p
float px;   
float py;   
float pz;

// Rotation and orientation R
float ax;   
float ay;   
float az;
float ox;   
float oy;   
float oz;
float nx;   
float ny;   
float nz;

// Joint angles Oi (degree)
float O1;   
float O2;   
float O3;
float O4;   
float O5;   
float O6;

// Joint angles Oi (radian)
float O1R;   
float O2R;   
float O3R;
float O4R;   
float O5R;   
float O6R;

// The length distance from zi to z(i+1) measured along zi.
float a3 = 90;
float a4 = 90;

// The offset distance from xi to x(i+1) measured along zi.
float d1 = 45;
float d5 = 30;

// For the inverse calaulation.
float numerator;
float denominator;
float x;
float y;
float dev;
float dev2;
float O12R;
float O23R;
float O34R;
float O345R;

void setup() {
  
  Serial.begin(9600);
  
  Serial.println("Please enter the way of the calculation\n1 for farward kinematic\nand 2 for inverse kinematic.");
  while (Serial.available()==0) {}
  cw = Serial.parseInt();
  
  if (cw == 1) {     // If the user choose the forward kinematic.
   
    Serial.println("Please enter the first angle O1(degree):");
    while (Serial.available()==0) {}
    O1 = Serial.parseInt();
    Serial.println("Please enter the second angle O2(degree):");
    while (Serial.available()==0) {}
    O2 = Serial.parseInt();
    Serial.println("Please enter the third angle O3(degree):");
    while (Serial.available()==0) {}
    O3 = Serial.parseInt();
    Serial.println("Please enter the fourth angle O4(degree):");
    while (Serial.available()==0) {}
    O4 = Serial.parseInt();
    Serial.println("Please enter the fifth angle O5(degree):");
    while (Serial.available()==0) {}
    O5 = Serial.parseInt();
    Serial.println("Please enter the sixth angle O6(degree):");
    while (Serial.available()==0) {}
    O6 = Serial.parseInt();
    
    
    // Convert the angles from degree to radian.
    O1R = O1*3.14/180.0;    
    O2R = O2*3.14/180.0;
    O3R = O3*3.14/180.0;    
    O4R = O4*3.14/180.0;
    O5R = O5*3.14/180.0;    
    O6R = O6*3.14/180.0;
    
    // Calculate the position of the end effector.
    px = a4*cos(O1R+O2R)*cos(O3R)*cos(O4R)-a4*cos(O1R+O2R)*sin(O3R)*sin(O4R)+d5*sin(O1R+O2R)+a3*cos(O1R+O2R)*cos(O3R);
    Serial.print("px is: ");
    Serial.println(px);
    py = a4*sin(O1R+O2R)*cos(O3R)*cos(O4R)-a4*sin(O1R+O2R)*sin(O3R)*sin(O4R)-d5*cos(O1R+O2R)+a3*sin(O1R+O2R)*cos(O3R);
    Serial.print("py is: ");
    Serial.println(py);
    pz = a4*sin(O3R)*cos(O4R)+a4*cos(O3R)*sin(O4R)+a3*sin(O3R)+d1;
    Serial.print("pz is: ");
    Serial.println(pz);
    
    // Calculate the rotation and orientation for the end effector.
    
    //n
    nx = cos(O6R)*cos(O1R+O2R)*cos(O3R+O4R+O5R)-sin(O6R)*sin(O1R+O2R);
    Serial.print("nx is: ");
    Serial.println(nx);
    ny = cos(O6R)*sin(O1R+O2R)*cos(O3R+O4R+O5R)+sin(O6R)*cos(O1R+O2R);
    Serial.print("ny is: ");
    Serial.println(ny);
    nz = cos(O6R)*sin(O3R+O4R+O5R);
    Serial.print("nz is: ");
    Serial.println(nz);
    
    //o
    ox = sin(O6R)*cos(O1R+O2R)*cos(O3R+O4R+O5R)-cos(O6R)*sin(O1R+O2R);
    Serial.print("ox is: ");
    Serial.println(ox);
    oy = -sin(O6R)*sin(O1R+O2R)*cos(O3R+O4R+O5R)+cos(O6R)*cos(O1R+O2R);
    Serial.print("oy is: ");
    Serial.println(oy);
    oz = -sin(O6R)*sin(O3R+O4R+O5R);
    Serial.print("oz is: ");
    Serial.println(oz);
    
    //a
    ax = -cos(O1R+O2R)*sin(O3R+O4R+O5R);
    Serial.print("ax is: ");
    Serial.println(ax);
    ay = -sin(O1R+O2R)*sin(O3R+O4R+O5R);
    Serial.print("ay is: ");
    Serial.println(ay);
    az = cos(O3R+O4R+O5R);
    Serial.print("az is: ");
    Serial.println(az);
  }
  
  else if (cw == 2){    // If the user choose the inverse kinematic.
    
    Serial.println("Please enter px:");
    while (Serial.available()==0) {}
    px = Serial.parseFloat();
    Serial.println("Please enter py:");
    while (Serial.available()==0) {}
    py = Serial.parseFloat();
    Serial.println("Please enter pz:");
    while (Serial.available()==0) {}
    pz = Serial.parseFloat();
    
    Serial.println("Please enter ox:");
    while (Serial.available()==0) {}
    ox = Serial.parseFloat();
    Serial.println("Please enter oy:");
    while (Serial.available()==0) {}
    oy = Serial.parseFloat();
    Serial.println("Please enter oz:");
    while (Serial.available()==0) {}
    oz = Serial.parseFloat();
    
    Serial.println("Please enter ax:");
    while (Serial.available()==0) {}
    ax = Serial.parseFloat();
    Serial.println("Please enter ay:");
    while (Serial.available()==0) {}
    ay = Serial.parseFloat();
    Serial.println("Please enter az:");
    while (Serial.available()==0) {}
    az = Serial.parseFloat();
    
    Serial.println("Please enter nx:");
    while (Serial.available()==0) {}
    nx = Serial.parseFloat();
    Serial.println("Please enter ny:");
    while (Serial.available()==0) {}
    ny = Serial.parseFloat();
    Serial.println("Please enter nz:");
    while (Serial.available()==0) {}
    nz = Serial.parseFloat();
    
    // Calculate the second angle(degree).
    float px2 = pow(px,2);
    float py2 = pow(py,2);
    float d15 = d1+d5;
    numerator = d15;
    denominator = sqrt(px2+py2);
    O2R = asin(numerator/denominator)-atan(-py/px);
    O2 = O2R*180/3.14;
    
    // Calculate the first angle(degree).
    O12R = atan(ay/ax);
    O1R = O12R-O2R;
    O1 = O1R*180/3.14;
    
    // Calculate the third angle(degree).
    float H = d1+d5+a3*sin(O2R);
    float H2 = pow(H,2);
    x = H;
    y = sqrt(px2+py2-H2);
    O3R = atan2(px,-py)-atan2(y,x);
    O3 = O3R*180/3.14;
    
    // Calculate the fourth angle(degree).
    numerator = -a3*sin(O3R)+pz-d1;
    denominator = a4;
    dev = numerator/denominator;
    O34R = asin(dev);
    O4R = O34R-O3R;
    O4 = O4R*180/3.14;
    
    // Calculate the fifth angle(degree).
    O345R = acos(az);
    O5R=O345R-O4R-O3R;
    O5 = O5R*180/3.14;
    
    // Calculate the sixth angle(degree).
    numerator = -ny*cos(O2R)+nx*sin(O2R);
    denominator = -oy*cos(O2R)+ox*sin(O2R);
    O6R = atan(numerator/denominator);
    O6 = O6R*180/3.14;
    
    Serial.print("The first angle(degree) is: ");
    Serial.println(O1);
    Serial.print("The second angle(degree) is: ");
    Serial.println(O2);
    Serial.print("The third angle(degree) is: ");
    Serial.println(O3);
    Serial.print("The fourth angle(degree) is: ");
    Serial.println(O4);
    Serial.print("The fifth angle(degree) is: ");
    Serial.println(O5);
    Serial.print("The sixth angle(degree) is: ");
    Serial.println(O6);
  }
}

void loop()
{
  // Move the Motors.
}
