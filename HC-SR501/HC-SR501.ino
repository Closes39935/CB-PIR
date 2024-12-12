/*
 * Mã Arduino sử dụng cảm biến chuyển động HC-SR501 và nút nhấn
 * để bật/tắt relay 2 kênh.
 */

const int CAM_BIEN_PIN = 2; // Chân cảm biến chuyển động
const int RELAY1_PIN = 4;   // Relay kênh 1
const int RELAY2_PIN = 5;   // Relay kênh 2
const int BUTTON_PIN = 6;   // Nút nhấn

bool relayState = false;    // Trạng thái của relay
bool buttonState = false;   // Trạng thái nút nhấn
bool lastButtonState = false; // Trạng thái trước đó của nút nhấn

void setup() {
  Serial.begin(9600);

  pinMode(CAM_BIEN_PIN, INPUT);   // Cảm biến chuyển động
  pinMode(RELAY1_PIN, OUTPUT);    // Relay kênh 1
  pinMode(RELAY2_PIN, OUTPUT);    // Relay kênh 2
  pinMode(BUTTON_PIN, INPUT_PULLUP); // Nút nhấn với điện trở pull-up nội bộ

  digitalWrite(RELAY1_PIN, HIGH); // Tắt relay ban đầu
  digitalWrite(RELAY2_PIN, HIGH);
}

void loop() {
  int chuyendong = digitalRead(CAM_BIEN_PIN); // Đọc cảm biến chuyển động
  bool currentButtonState = digitalRead(BUTTON_PIN); // Đọc trạng thái nút nhấn

  // Kiểm tra trạng thái nút nhấn (nhấn để chuyển đổi trạng thái relay)
  if (currentButtonState == LOW && lastButtonState == HIGH) {
    relayState = !relayState; // Đảo trạng thái relay
    Serial.println("Nút nhấn được kích hoạt");
    digitalWrite(RELAY1_PIN, relayState ? LOW : HIGH);
    digitalWrite(RELAY2_PIN, relayState ? LOW : HIGH);
  }
  lastButtonState = currentButtonState; // Cập nhật trạng thái nút nhấn

  // Nếu không dùng nút nhấn, cảm biến sẽ điều khiển relay tự động
  if (chuyendong && !relayState) { // Chỉ bật relay nếu relay đang tắt
    Serial.println("Phát hiện chuyển động");
    digitalWrite(RELAY1_PIN, LOW);
    digitalWrite(RELAY2_PIN, LOW);
  } else if (!chuyendong && !relayState) { // Chỉ tắt relay nếu relay đang tắt
    Serial.println("Không phát hiện chuyển động");
    digitalWrite(RELAY1_PIN, HIGH);
    digitalWrite(RELAY2_PIN, HIGH);
  }

  delay(50); // Giảm nhiễu tín hiệu và debounce cho nút nhấn
}
