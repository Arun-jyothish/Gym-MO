#include<Wire.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

// Wifi network station credentials
#define WIFI_SSID "Redmi"
#define WIFI_PASSWORD "arjun1234"
#define BOT_TOKEN "5565226957:AAGRDHeCXHnBIih_vkSkH8mOyiZu06tPhtc"

const unsigned long BOT_MTBS = 1000; // mean time between scan messages
const int MPU_addr = 0x68; int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;

int minVal = 265; int maxVal = 402;

double x; double y; double z;

WiFiClientSecure secured_client;
UniversalTelegramBot bot(BOT_TOKEN, secured_client);
unsigned long bot_lasttime;          // last time messages' scan has been done
bool Start = false;

void handleNewMessages(int numNewMessages)
{
  Serial.println("handleNewMessages");
  Serial.println(String(numNewMessages));

  for (int i = 0; i < numNewMessages; i++)
  {
    String chat_id = bot.messages[i].chat_id;
    String text = bot.messages[i].text;
    Serial.print("New Message: ");
    Serial.println(text);
    String from_name = bot.messages[i].from_name;
    Serial.print("From: ");
    Serial.println(from_name);
    if (from_name == "")
      from_name = "Guest";

    if (text == "/send_test_action")
    {
      bot.sendChatAction(chat_id, "typing");
      delay(4000);
      bot.sendMessage(chat_id, "Did you see the action message?");

    }

    if (text == "/1"){
       String str1= "1:BICEPS EXCERCISE is selected";
       bot.sendMessage(chat_id,str1);
       for(i=0;i<100;i++){
       Wire.beginTransmission(MPU_addr); 
       Wire.write(0x3B); 
       Wire.endTransmission(false); 
       Wire.requestFrom(MPU_addr, 14, true); 
       AcX = Wire.read() << 8 | Wire.read(); 
       AcY = Wire.read() << 8 | Wire.read(); AcZ = Wire.read() << 8 | Wire.read(); 
       int xAng = map(AcX, minVal, maxVal, -90, 90); 
       int yAng = map(AcY, minVal, maxVal, -90, 90); 
       int zAng = map(AcZ, minVal, maxVal, -90, 90);

       x = RAD_TO_DEG * (atan2(-yAng, -zAng) + PI); y = RAD_TO_DEG * (atan2(-xAng, -zAng) + PI); z = RAD_TO_DEG * (atan2(-yAng, -xAng) + PI);

       
        int lower_angle = 240;
        int highier_angle = 100 ;
        Serial.println(x);
        if ( x > lower_angle){
        String str2= "Wrong, Too low";
        bot.sendMessage(chat_id,str2);
       }
         else if ( x < highier_angle){
        
        String str3= "Wrong, Too high";
        bot.sendMessage(chat_id,str3);
  }
       else{
        String str4= "Wrong excercise";
        bot.sendMessage(chat_id,str4);
  }
         delay(1000);
       }
    }


  

 if (text == "/2"){
       String str1= "1:ARM EXCERCISE is selected";
       bot.sendMessage(chat_id,str1);
       for(i=0;i<100;i++){
       Wire.beginTransmission(MPU_addr); 
       Wire.write(0x3B); 
       Wire.endTransmission(false); 
       Wire.requestFrom(MPU_addr, 14, true); 
       AcX = Wire.read() << 8 | Wire.read(); 
       AcY = Wire.read() << 8 | Wire.read(); AcZ = Wire.read() << 8 | Wire.read(); 
       int xAng = map(AcX, minVal, maxVal, -90, 90); 
       int yAng = map(AcY, minVal, maxVal, -90, 90); 
       int zAng = map(AcZ, minVal, maxVal, -90, 90);

       x = RAD_TO_DEG * (atan2(-yAng, -zAng) + PI); y = RAD_TO_DEG * (atan2(-xAng, -zAng) + PI); z = RAD_TO_DEG * (atan2(-yAng, -xAng) + PI);

       
        int lower_angle = 240;
        int highier_angle = 100 ;
        Serial.println(x);
        if ( x > lower_angle){
        String str2= "Wrong, Too low";
        bot.sendMessage(chat_id,str2);
       }
         else if ( x < highier_angle){
        
        String str3= "Wrong, Too high";
        bot.sendMessage(chat_id,str3);
  }
       else{
        String str4= "Wrong excercise";
        bot.sendMessage(chat_id,str4);
  }
         delay(1000);
       }
 }

       
 if (text == "/start")
    {
      String welcome = "WELCOME TO GYM TRAINING SYSTEM  1:Biceps EXCERCISE 2: EXCERCISE";
      bot.sendMessage(chat_id, welcome);
    }
  }
}

void setup()
{
  Serial.begin(115200);
  Serial.println();

  // attempt to connect to Wifi network:
  Serial.print("Connecting to Wifi SSID ");
  Serial.print(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  secured_client.setCACert(TELEGRAM_CERTIFICATE_ROOT); // Add root certificate for api.telegram.org
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.print("\nWiFi connected. IP address: ");
  Serial.println(WiFi.localIP());

  Serial.print("Retrieving time: ");
  configTime(0, 0, "pool.ntp.org"); // get UTC time via NTP
  time_t now = time(nullptr);
  while (now < 24 * 3600)
  {
    Serial.print(".");
    delay(100);
    now = time(nullptr);
  }
  Serial.println(now);

  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  Serial.begin(115200);
}

void loop()
{
  if (millis() - bot_lasttime > BOT_MTBS)
  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    while (numNewMessages)
    {
      Serial.println("got response");
      handleNewMessages(numNewMessages  );
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }

    bot_lasttime = millis();
  }
}
