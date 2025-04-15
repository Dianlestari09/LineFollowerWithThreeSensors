int lm1 = 8;  // output motor kiri 1 (PWM tidak digunakan di sini)
int lm2 = 9;  // output motor kiri 2 (PWM tidak digunakan di sini)
int rm1 = 10; // output motor kanan 1 (PWM tidak digunakan di sini)
int rm2 = 11; // output motor kanan 2 (PWM tidak digunakan di sini)

int pwmL = 5; // Pin PWM motor kiri
int pwmR = 6; // Pin PWM motor kanan

int sl = 13;  // input sensor kiri
int sm = 7;   // input sensor tengah
int sr = 12;  // input sensor kanan

int SlV = 0;  // nilai sensor kiri
int SmV = 0;  // nilai sensor tengah
int SrV = 0;  // nilai sensor kanan

int speedL = 70; // Kecepatan motor kiri (0-255)
int speedR = 70; // Kecepatan motor kanan (0-255)

void setup()
{
  pinMode(lm1, OUTPUT);
  pinMode(lm2, OUTPUT);
  pinMode(rm1, OUTPUT);
  pinMode(rm2, OUTPUT);
  pinMode(pwmL, OUTPUT);
  pinMode(pwmR, OUTPUT);
  pinMode(sl, INPUT);
  pinMode(sm, INPUT);
  pinMode(sr, INPUT);
  sTOP();
}

void loop()
{
  // Membaca nilai dari sensor
  SlV = digitalRead(sl);
  SmV = digitalRead(sm);
  SrV = digitalRead(sr);

  // Logika gerakan berdasarkan sensor
  if (SmV == LOW && SlV == LOW && SrV == LOW)
  {
    ForWard(); // Semua sensor tidak mendeteksi garis, maju lurus
  }
  else if (SmV == HIGH && SlV == LOW && SrV == LOW)
  {
    ForWard(); // Hanya sensor tengah mendeteksi garis, maju lurus
  }
  else if (SmV == LOW && SlV == HIGH && SrV == LOW)
  {
    Left(); // Sensor kiri mendeteksi garis, belok kiri
  }
  else if (SmV == LOW && SlV == LOW && SrV == HIGH)
  {
    Right(); // Sensor kanan mendeteksi garis, belok kanan
  }
  else if (SmV == HIGH && SlV == HIGH && SrV == LOW)
  {
    Left(); // Sensor tengah dan kiri mendeteksi garis, belok kiri
  }
  else if (SmV == HIGH && SlV == LOW && SrV == HIGH)
  {
    Right(); // Sensor tengah dan kanan mendeteksi garis, belok kanan
  }
  else if (SmV == HIGH && SlV == HIGH && SrV == HIGH)
  {
    sTOP(); // Semua sensor mendeteksi garis, berhenti (misalnya tanda akhir)
  }
  else
  {
    sTOP(); // Default safety: berhenti
  }
}

// Fungsi gerakan
void ForWard()
{
  analogWrite(pwmL, speedL); // Atur kecepatan motor kiri
  analogWrite(pwmR, speedR); // Atur kecepatan motor kanan
  digitalWrite(lm1, HIGH);
  digitalWrite(lm2, LOW);
  digitalWrite(rm1, HIGH);
  digitalWrite(rm2, LOW);
}
void BackWard()
{
  analogWrite(pwmL, speedL);
  analogWrite(pwmR, speedR);
  digitalWrite(lm1, LOW);
  digitalWrite(lm2, HIGH);
  digitalWrite(rm1, LOW);
  digitalWrite(rm2, HIGH);
}
void Left()
{
  analogWrite(pwmL, speedL / 2); // Kurangi kecepatan motor kiri untuk belok kiri
  analogWrite(pwmR, speedR);
  digitalWrite(lm1, LOW);
  digitalWrite(lm2, HIGH);
  digitalWrite(rm1, HIGH);
  digitalWrite(rm2, LOW);
}
void Right()
{
  analogWrite(pwmL, speedL);
  analogWrite(pwmR, speedR / 2); // Kurangi kecepatan motor kanan untuk belok kanan
  digitalWrite(lm1, HIGH);
  digitalWrite(lm2, LOW);
  digitalWrite(rm1, LOW);
  digitalWrite(rm2, HIGH);
}
void sTOP()
{
  analogWrite(pwmL, 0); // Matikan PWM motor kiri
  analogWrite(pwmR, 0); // Matikan PWM motor kanan
  digitalWrite(lm1, LOW);
  digitalWrite(lm2, LOW);
  digitalWrite(rm1, LOW);
  digitalWrite(rm2, LOW);
}
