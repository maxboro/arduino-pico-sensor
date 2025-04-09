#define BETA 3950
#define SENSOR_PIN 28

void setup() {
  Serial1.begin(115200);
  pinMode(SENSOR_PIN, INPUT_PULLUP);
  Serial1.println("Raspberry Pi Pico is set!");
}

float get_temp_celc(float analogValue){
  float celsius = 1 / (log(1 / (1023. / analogValue - 1)) / BETA + 1.0 / 298.15) - 273.15;
  return celsius;
}

void print_temperature(float analogValue){
  String msg = "Temperature is " + String(get_temp_celc(analogValue));
  Serial1.println(msg);
}

void loop() {
  float analogValue = analogRead(SENSOR_PIN);
  print_temperature(analogValue);
  delay(1000);
}
