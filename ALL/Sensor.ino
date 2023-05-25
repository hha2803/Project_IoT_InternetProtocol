void sensor_DHT11(){
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
    float h = dht.readHumidity();
    // Read temperature as Celsius (the default)
    float t = dht.readTemperature();
    // Read temperature as Fahrenheit (isFahrenheit = true)
    float f = dht.readTemperature(true);

    // Check if any reads failed and exit early (to try again).
    if (isnan(h) || isnan(t) || isnan(f)) {
      Serial.println("Failed to read from DHT sensor!");
      return;
    }
    static char realtemperatureTemp[7];
    dtostrf(t, 6, 2, realtemperatureTemp);
    
    // Computes temperature values in Celsius
    float hic = dht.computeHeatIndex(t, h, false);
    static char temperatureTemp[7];
    dtostrf(hic, 6, 2, temperatureTemp);
    
    static char humidityTemp[7];
    dtostrf(h, 6, 2, humidityTemp);

    // Publishes Temperature and Humidity values
    client.publish("room/realtemperature", realtemperatureTemp);
    client.publish("room/temperature", temperatureTemp);
    client.publish("room/humidity", humidityTemp);
    
    Serial.print("Humidity: ");
    Serial.print(h);
    Serial.print(" %\t Temperature: ");
    Serial.print(t);
    Serial.print(" *C ");
    Serial.print(f);
    Serial.print(" *F\t Heat index: ");
    Serial.print(hic);
    Serial.println(" *C ");

    lcd.setCursor(0, 1);
    lcd.print("Temperature:");
    lcd.print(t);
    lcd.print(" *C");

    lcd.setCursor(0,3);
    lcd.print("Humidity:");
    lcd.print(h);
    lcd.print(" %");

    // if(t > 25){
    //   digitalWrite(fan, HIGH);
    //   Serial.println("fan_on");
    //   } 
    //  else{
    //   digitalWrite(fan, LOW);
    //   Serial.println("fan_off");
    //   } 
}
