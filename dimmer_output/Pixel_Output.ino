    UCSR0C = 0xC0; // Set MSPI data mode 1.
      UCSR0B = (1 << TXEN0); // Enable transmitter
      UCSR0A |= (1 << U2X0); // Double transmission speed
      UBRR0H = 0; UBRR0L = 1; // Set baud to 4,000,000bps @ 16Mhz clock
      // Send data
      cli();
      for (int n = 126; n < 638; n++) { // Loop 512 times
        op1 = B01111011; // set values to zero pixel
        if (data[n] & B10000000) op1 &= B10011111; // mask as 1 if pixel data bit is a 1
        if (data[n] & B01000000) op1 &= B11111100; // mask as 1 if pixel data bit is a 1
        while ( ! (UCSR0A & (1 << UDRE0)) ); // Wait for buffer to empty
        UDR0 = op1; // write to output buffer
        op2 = B11011110; // set values to zero pixel
        if (data[n] & B00100000) op2 &= B11100111; // mask as 1 if pixel data bit is a 1
        while ( ! (UCSR0A & (1 << UDRE0)) ); // Wait for buffer to empty
        UDR0 = op2; // write to output buffer
        op3 = B11110111; // set values to zero pixel
        if (data[n] & B00010000) op3 &= B00111111; // mask as 1 if pixel data bit is a 1
        if (data[n] & B00001000) op3 &= B11111001; // mask as 1 if pixel data bit is a 1
        while ( ! (UCSR0A & (1 << UDRE0)) ); // Wait for buffer to empty
        UDR0 = op3; // write to output buffer
        op4 = B10111101; // set values to zero pixel
        if (data[n] & B00000100) op4 &= B11001111; // mask as 1 if pixel data bit is a 1
        if (data[n] & B00000010) op4 &= B11111110; // mask as 1 if pixel data bit is a 1
        while ( ! (UCSR0A & (1 << UDRE0)) ); // Wait for buffer to empty
        UDR0 = op4; // write to output buffer
        op5 = B11101111; // set values to zero pixel
        if (data[n] & B00000010) op5 &= B01111111; // mask as 1 if pixel data bit is a 1
        if (data[n] & B00000001) op5 &= B11110011; // mask as 1 if pixel data bit is a 1
        while ( ! (UCSR0A & (1 << UDRE0)) ); // Wait for buffer to empty
        UDR0 = op5; // write to output buffer
      }
      sei();
