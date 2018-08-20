/*
 * Arduino RFID Keyboard - Outputs RFID Tag`s UUID as keyboard input.
 * MIT License
 * 
 * Copyright (c) 2018 Brunno Telma
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
/*
 * Pin layout should be as follows:
 * Signal     Pin              Pin             Pin             Pin
 *            Arduino Uno      Arduino Mega    Arduino Micro   MFRC522 board
 * --------------------------------------------------------------------------
 * Reset      9                5               6               RST
 * SPI SS     10               53              10              SDA
 * SPI MOSI   11               51              16              MOSI
 * SPI MISO   12               50              14              MISO
 * SPI SCK    13               52              15              SCK
 *
 */

#include <Keyboard.h>
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN    10
#define RST_PIN   6

MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() {
  SPI.begin();          // Init SPI bus
  mfrc522.PCD_Init();   // Init MFRC522 card
}

void loop() {
  // Look for new cards
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Read one of the cards
  if (!mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  String RFID = "";

  // Convert from bytes from UID array to String
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    if(mfrc522.uid.uidByte[i] < 0x10) {
      RFID.concat("0");
    }
    RFID.concat(String(mfrc522.uid.uidByte[i], HEX));
  }

  RFID.toUpperCase();

  Keyboard.print(RFID);
  // Print `new line` to submit or confirm on input
  Keyboard.print("\n");

  // Wait one-sec to start reading again
  delay(1000);
}
