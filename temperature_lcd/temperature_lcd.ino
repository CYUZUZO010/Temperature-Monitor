#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Initialize LCD with I2C address 0x27, 16 columns, 2 rows
LiquidCrystal_I2C lcd(0x27, 16, 2);

String candidateName = "CYUZUZO";

int scrollPos = 0;
unsigned long lastScroll = 0;
unsigned long lastRead = 0;

// Base temperature for simulation
float simulatedTemp = 24.5; 

void setup()
{
    Serial.begin(9600); // Initialize serial connection to PC

    lcd.init();
    lcd.backlight();
    lcd.clear();
}

void loop()
{
    unsigned long currentTime = millis();

    // ===== FIRST ROW: SCROLLING NAME =====
    if (currentTime - lastScroll >= 300)
    {
        lastScroll = currentTime;
        lcd.setCursor(0, 0);

        if(candidateName.length() <= 16)
        {
            lcd.print("                ");
            lcd.setCursor(0,0);
            lcd.print(candidateName);
        }
        else
        {
            String text = candidateName + "    ";
            String displayText = text + text;

            lcd.print(displayText.substring(scrollPos, scrollPos + 16));
            scrollPos++;

            if(scrollPos >= text.length())
            {
                scrollPos = 0;
            }
        }
    }

    // ===== SECOND ROW: TEMPERATURE GENERATION =====
    if (currentTime - lastRead >= 1000)
    {
        lastRead = currentTime;

        // Simulate slight environmental temperature fluctuations (-0.3 to +0.3)
        float fluctuation = ((random(0, 60) - 30) / 100.0);
        simulatedTemp += fluctuation;

        // Keep the simulated temperature within a realistic room boundary
        if (simulatedTemp < 22.0) simulatedTemp = 22.5;
        if (simulatedTemp > 28.0) simulatedTemp = 27.5;

        // Set status based on the simulated temperature
        String status = "NORMAL";
        if (simulatedTemp > 35.0) status = "HIGH";
        else if (simulatedTemp < 15.0) status = "LOW";

        // Display on LCD
        lcd.setCursor(0,1);
        lcd.print("Temp:");
        lcd.print(simulatedTemp, 1);
        lcd.print((char)223); // Degree symbol
        lcd.print("C ");
        lcd.print(status);
        lcd.print("    ");

        // Send data formatted as "temperature,status" to the PC script via Serial
        Serial.print(simulatedTemp, 1);
        Serial.print(",");
        Serial.println(status);
    }
}