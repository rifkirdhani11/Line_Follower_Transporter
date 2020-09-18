//LCD Initialization
#define LCD_SDA 20
#define LCD_SCL 21
LiquidCrystal_I2C lcd(0x27, 16, 2);

void LCDSetup()
{
  // Initialize the LCD
  lcd.begin();
  // Turn on the blacklight and print a message
  lcd.backlight();
  lcd.print("  MECHATRONICS  ");
  lcd.setCursor(0,1);
  lcd.print("  TEAM PROJECT  ");
}

void LCD()
{
  // Put your main code here, to run repeatedly:
  // User Interface is under maintenance
}
