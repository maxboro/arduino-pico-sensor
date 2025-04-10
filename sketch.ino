#define BETA 3950
#define SENSOR_PIN 28
#define LED_BLUE_PIN 11
#define LED_GREEN_PIN 12
#define LED_RED_PIN 13

void setup() {
  Serial1.begin(115200);
  pinMode(SENSOR_PIN, INPUT_PULLUP);

  pinMode(LED_BLUE_PIN, OUTPUT);
  pinMode(LED_GREEN_PIN, OUTPUT);
  pinMode(LED_RED_PIN, OUTPUT);

  Serial1.println("Raspberry Pi Pico is set!");
}

float get_temp_celc(float analogValue){
  float celsius = 1 / (log(1 / (1023. / analogValue - 1)) / BETA + 1.0 / 298.15) - 273.15;
  return celsius;
}

void print_temperature(float conv_temp_celc){
  String msg = "Temperature is " + String(conv_temp_celc);
  Serial1.println(msg);
}

void handle_led(float conv_temp_celc){
  int led_blue_value = LOW;
  int led_green_value = LOW;
  int led_red_value = LOW;
  if (conv_temp_celc < 0){
    led_blue_value = HIGH;
  } else if (conv_temp_celc >= 0 && conv_temp_celc <= 25){
    led_green_value = HIGH;
  } else {
    led_red_value = HIGH;
  }
  digitalWrite(LED_BLUE_PIN, led_blue_value);
  digitalWrite(LED_GREEN_PIN, led_green_value);
  digitalWrite(LED_RED_PIN, led_red_value);
}

void loop() {
  float analogValue = analogRead(SENSOR_PIN);
  float conv_temp_celc = get_temp_celc(analogValue);
  print_temperature(conv_temp_celc);
  handle_led(conv_temp_celc);
  delay(1000);
}
