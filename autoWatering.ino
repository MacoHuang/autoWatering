//腳位設定
const int soilMoisturePin=A0;
const int relayPin=7;
//感測器臨界值
const int dryThreshold=500;

void setup() {
  Serial.begin(9600);
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW);
}

void loop() {
  // 讀取土壤濕度
  int moistureValue=analogRead(soilMoisturePin);
  Serial.print("Soil Humidity: ");
  Serial.println(moistureValue);

  //檢查是否需要噴水
  if (moistureValue>dryThreshold){
    Serial.println("Let's Rainning!! ");
    digitalWrite(relayPin, HIGH);   //開水
    delay(6000);                    //噴水6秒
    digitalWrite(relayPin, LOW);    //關水
    Serial.println("Stop! wait for check");
  }
  delay(3600000); //等1小時再來
}
