#define LUM_PIN A5

int luminance;
int max_lum; 

bool calibrated;

void setup() 
{
    pinMode(LUM_PIN, INPUT);
    Serial.begin();
}

void loop() 
{
    if (!calibrated)
    {
        calibrate_();
    }
    else if (calibrated)
    {
        luminance = analogRead(LUM_PIN);
        //print out the current luminance level for verification
        Serial.print(luminance);
        Serial.print("     ");
        //only publish event if luminance level drops to avoid spam
        if (luminance < max_lum)
        {
            Particle.publish("Light_Level", "Under Shade");
        }
        delay(5000);
    }
}

//place the system under direct sunlight for calibration
void calibrate_()
{
    calibrated = true; 
    //save the calibrated value for direct sunlight as max_lum
    for (int i = 0; i < 10; i++)
    {
        max_lum = analogRead(LUM_PIN);
    }
    
    Particle.publish("Light_Level", "Calibrated");
}