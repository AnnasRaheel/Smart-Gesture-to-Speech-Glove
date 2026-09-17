#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

// --- Flex pins ---
const int F0 = A7; // thumb
const int F1 = A9; // index
const int F2 = A10; // middle
const int F3 = A11; // ring

// --- smoothing ---
const int MOVAVG = 6;
int flexBuf[4][MOVAVG];
int bufIdx = 0;

// --- thresholds (adjusted) ---
const int T0 =  221; // thumb bend
const int T1v = 260; // index bend
const int T2v = 254; // middle (slightly easier)
const int T3v = 228; // ring bend

const int R0 = 247;  // thumb release
const int R1r = 290; // index release
const int R2r = 299; // middle release
const int R3r = 275; // ring release

// --- gesture state ---
bool gestureActive = false;
unsigned long lastSend = 0;
const unsigned long COOLDOWN = 1200UL;
String lastMessage = "";

// --- MPU thresholds (corrected orientation) ---
const float MPU_FORWARD = -3.0;  
const float MPU_BACK    = 4.0;   
const float MPU_LEFT    = 4.0;   
const float MPU_RIGHT   = -9.0;   

// -------- Helper: send message ----------
void sendMsg(String m) {
  if (m.length() == 0) return;
  Serial.println(">>> " + m);
  Serial1.println(m);
  lastSend = millis();
  lastMessage = m;
}

// -------- Flex smooth reading -----------
float readFlexSmooth(int idx, int pin) {
  flexBuf[idx][bufIdx] = analogRead(pin);
  long s = 0;
  for (int i = 0; i < MOVAVG; i++) s += flexBuf[idx][i];
  return float(s) / MOVAVG;
}

// -------- Setup ----------
void setup() {
  Serial.begin(9600);
  Serial1.begin(9600); // HC-05
  Wire.begin();

  for (int i = 0; i < MOVAVG; i++) {
    flexBuf[0][i] = analogRead(F0);
    flexBuf[1][i] = analogRead(F1);
    flexBuf[2][i] = analogRead(F2);
    flexBuf[3][i] = analogRead(F3);
  }

  Serial.println("Initializing MPU...");
  mpu.initialize();
  if (mpu.testConnection()) Serial.println("MPU6050 FOUND");
  else Serial.println("MPU6050 NOT FOUND - MPU gestures disabled");

  delay(600);
  Serial.println("Ready - keep hand straight...");
  delay(600);
}

// -------- Loop ----------
void loop() {
  bufIdx = (bufIdx + 1) % MOVAVG;

  float fv0 = readFlexSmooth(0, F0);
  float fv1 = readFlexSmooth(1, F1);
  float fv2 = readFlexSmooth(2, F2);
  float fv3 = readFlexSmooth(3, F3);

  bool bent0 = (fv0 > T0);
  bool bent1 = (fv1 > T1v);
  bool bent2 = (fv2 > T2v);
  bool bent3 = (fv3 > T3v);

  bool released0 = (fv0 < R0);
  bool released1 = (fv1 < R1r);
  bool released2 = (fv2 < R2r);
  bool released3 = (fv3 < R3r);

  int16_t ax_raw, ay_raw, az_raw, gx, gy, gz;
  mpu.getMotion6(&ax_raw, &ay_raw, &az_raw, &gx, &gy, &gz);
  float ax = (ax_raw / 16384.0) * 9.81;
  float ay = (ay_raw / 16384.0) * 9.81;
  float az = (az_raw / 16384.0) * 9.81;

  static unsigned long lastDbg = 0;
  if (millis() - lastDbg > 400) {
    Serial.print("F: ");
    Serial.print((int)fv0); Serial.print(",");
    Serial.print((int)fv1); Serial.print(",");
    Serial.print((int)fv2); Serial.print(",");
    Serial.print((int)fv3);
    Serial.print(" | AccX: "); Serial.print(ax,2);
    Serial.print(" Ay: "); Serial.print(ay,2);
    Serial.print(" Az: "); Serial.println(az,2);
    lastDbg = millis();
  }

  String msg = "";

  if (!gestureActive) {
    // ---- FLEX single gestures ----
    if (bent0 && millis() - lastSend > COOLDOWN)
      msg = "Hello and Assalamualaikum.  I am Annas Raheel...Welcome ";
    else if (bent1 && millis() - lastSend > COOLDOWN)
      msg = "Thank you for watching! Together, we shape the future of communication.";
    else if (bent2 && millis() - lastSend > COOLDOWN)
      msg = "Our project converts gestures and sign language into speech using flex and motion sensors. This glove translates hand movements into voice for the speech-impaired.";
    else if (bent3 && millis() - lastSend > COOLDOWN)
      msg = "Ich bin Annas .";

    // ---- Combo gestures ----
    else if (bent0 && bent1 && millis() - lastSend > COOLDOWN)
      msg = "Technology that gives voice to silence.";
    else if (bent2 && bent3 && millis() - lastSend > COOLDOWN)
      msg = "Designed, developed, and demonstrated by Mechatron Predators.";

    // ---- MPU gestures ---- (axes corrected)
   
    else if (ay > MPU_BACK && millis() - lastSend > COOLDOWN)
      msg = "Let's Dive deeper into How Our System Actually Works.";
    else if (ax < MPU_RIGHT && millis() - lastSend > COOLDOWN)
      msg = "Thank you for watching! Together, we shape the future of communication.";
    else if (ax > MPU_LEFT && millis() - lastSend > COOLDOWN)
      msg = "Because every Sign Has Voice— we make it heard." ;

    if (msg.length() > 0) {
      sendMsg(msg);
      gestureActive = true;
    }
  }
  else {
    bool flexNeutral =
    (released0 && released1 &&
    released2 && released3);
    if (flexNeutral){
      gestureActive = false;
      
    }
  }
 
  delay(200);
}