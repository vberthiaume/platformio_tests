# Feather TFT ESP32-S3 SPIFFS tester
## PlatformIO instructions:
- Build Filesystem Image
- Upload Filesystem Image
- On your `adafruit_feather_esp32s3_tft` board, hold the `Boot` button, click the `Rst` button, and release the boot button
- Upload the code
- Click the `Rst` button
- When connecting a Serial Monitor, you should see this line printed over and over:

```
Hello World!
```
Instead what I see is this:
```
An Error has occurred while mounting SPIFFS
```
