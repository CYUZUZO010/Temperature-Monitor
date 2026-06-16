#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

String candidateName = "CYUZUZO IRAFASHA Sandra";

int scrollPos = 0;
unsigned long lastScroll = 0;
unsigned long lastRead = 0;

float simulatedTemp = 24.5;

void setup()
{
    Serial.begin(9600);

    lcd.init();
    lcd.backlight();
    lcd.clear();
}

void loop()
{
    unsigned long currentTime = millis();

    // ===== LCD ROW 1: SCROLL NAME =====
    if (currentTime - lastScroll >= 300)
    {
        lastScroll = currentTime;
        lcd.setCursor(0, 0);

        if (candidateName.length() <= 16)
        {
            lcd.print("                ");
            lcd.setCursor(0, 0);
            lcd.print(candidateName);
        }
        else
        {
            String text = candidateName + "    ";
            String displayText = text + text;

            lcd.print(displayText.substring(scrollPos, scrollPos + 16));
            scrollPos++;

            if (scrollPos >= text.length())
                scrollPos = 0;
        }
    }

    // ===== TEMP + SERIAL OUTPUT =====
    if (currentTime - lastRead >= 1000)
    {
        lastRead = currentTime;

        float fluctuation = ((random(0, 60) - 30) / 100.0);
        simulatedTemp += fluctuation;

        if (simulatedTemp < 22.0) simulatedTemp = 22.5;
        if (simulatedTemp > 28.0) simulatedTemp = 27.5;

        String status = "NORMAL";
        if (simulatedTemp > 35.0) status = "HIGH";
        else if (simulatedTemp < 15.0) status = "LOW";

        // ===== LCD ROW 2 =====
        lcd.setCursor(0, 1);
        lcd.print("Temp:");
        lcd.print(simulatedTemp, 1);
        lcd.print((char)223);
        lcd.print("C ");
        lcd.print(status);
        lcd.print("    ");

        // ===== SERIAL OUTPUT (CLEAN FORMAT) =====
        Serial.println("================================");
        Serial.println("Candidate name:");
        Serial.println(candidateName);
        Serial.println();
        Serial.println("Temperature:");
        Serial.print(simulatedTemp, 1);
        Serial.print(simulatedTemp, 1);
Serial.print(",");
Serial.println(status);
    }
}