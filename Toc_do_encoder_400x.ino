const int encoderPin = 2; // Chân kết nối tín hiệu từ encoder
volatile unsigned long pulseCount = 0; // Biến đếm xung

unsigned long lastTime = 0;
unsigned long interval = 100; // Khoảng thời gian đo lường (100 ms)
float speed = 0; // Biến lưu trữ tốc độ

void setup() {
  Serial.begin(9600); // Khởi động Serial để in kết quả ra màn hình
  pinMode(encoderPin, INPUT); // Cấu hình chân tín hiệu từ encoder là đầu vào
  attachInterrupt(digitalPinToInterrupt(encoderPin), countPulse, RISING); // Gán ngắt để đếm xung
}

void loop() {
  unsigned long currentTime = millis(); // Lấy thời gian hiện tại

  if (currentTime - lastTime >= interval) { // Nếu đã đủ khoảng thời gian đo lường
    noInterrupts(); // Tắt ngắt để không bị gián đoạn khi đọc giá trị
    unsigned long pulses = pulseCount; // Lưu lại giá trị đếm xung
    pulseCount = 0; // Đặt lại biến đếm xung
    interrupts(); // Bật lại ngắt

    // Tính toán tốc độ (số xung trong khoảng thời gian tính bằng giây)
    speed = (float)pulses / (interval / 1000.0);

    // In kết quả ra màn hình
    Serial.print("Tốc độ: ");
    Serial.print(speed);
    Serial.println(" xung/giây");

    lastTime = currentTime; // Cập nhật thời gian cuối cùng
  }
}

void countPulse() {
  pulseCount++; // Hàm xử lý ngắt để tăng biến đếm xung
}
