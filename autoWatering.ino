// 設定針腳
const int soilMoisturePin = A0;    // 濕度感測器連接到A0
const int relayPin = 7;            // 繼電器連接到D7

// 設定臨界值 (需要根據你的感測器校準)
const int dryThreshold = 500;      // 高於此值表示土壤太乾
const int wetThreshold = 400;      // 低於此值表示土壤已足夠濕潤

// 設定檢測間隔
const unsigned long checkInterval = 3600000;  // 正常檢測間隔：1小時
const unsigned long wateringCheckInterval = 1000;  // 澆水時的檢測間隔：1秒

unsigned long lastCheckTime = 0;
bool isWatering = false;

void setup() {
  Serial.begin(9600);
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW);    // 確保初始狀態為關閉
}

void loop() {
  unsigned long currentTime = millis();
  
  // 讀取土壤濕度
  int moistureValue = analogRead(soilMoisturePin);
  
  // 如果正在澆水中
  if (isWatering) {
    if (currentTime - lastCheckTime >= wateringCheckInterval) {
      Serial.print("澆水中，目前濕度: ");
      Serial.println(moistureValue);
      
      // 檢查是否已達到目標濕度
      if (moistureValue <= wetThreshold) {
        Serial.println("土壤已達目標濕度，停止澆水");
        digitalWrite(relayPin, LOW);  // 關閉水泵
        isWatering = false;
        lastCheckTime = currentTime;
      } else {
        // 繼續澆水，更新檢測時間
        lastCheckTime = currentTime;
      }
    }
  } 
  // 不在澆水狀態時，定期檢查是否需要澆水
  else if (currentTime - lastCheckTime >= checkInterval) {
    Serial.print("定期檢查，目前土壤濕度: ");
    Serial.println(moistureValue);
    
    // 檢查土壤是否太乾
    if (moistureValue > dryThreshold) {
      Serial.println("土壤過乾，開始澆水...");
      digitalWrite(relayPin, HIGH);  // 開啟水泵
      isWatering = true;
    } else {
      Serial.println("土壤濕度正常，無需澆水");
    }
    
    lastCheckTime = currentTime;
  }
}
