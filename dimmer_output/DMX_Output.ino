      //Send DMX on usart0
      UCSR0B = (1 << TXEN0); // Enable transmitter
      UCSR0A |= (1 << U2X0); // Double transmission speed
      while ( ! (UCSR0A & (1 << UDRE0)) );  // Wait for buffer to empty
      // Send break and mark after break
      UBRR0H = 0; UBRR0L = 17; // Set baud to 100,000bps @ 16Mhz clock
      UCSR0C = (3 << UCSZ00) | (2 << UPM00); // Set 8 data bits, E parity and 1 stop bit.
      UDR0 = 0x00; // load data into usart buffer and send
      UCSR0A |= (1 << TXC0); // Clear transmit complete flag
      while ( ! (UCSR0A & (1 << TXC0)) ); // Wait for transmit complete flag
      // Send start code 0x00
      UBRR0H = 0; UBRR0L = 7; // Set baud to 250,000bps @ 16Mhz clock
      UCSR0C = (1 << USBS0) | (3 << UCSZ00); // Set 8 data bits, no parity and 2 stop bits
      UDR0 = 0x00; // Load data into usart buffer and send
      // Send data
      for (int n = 126; n < 638; n++) { // Loop 512 times
        while ( ! (UCSR0A & (1 << UDRE0)) ); // Wait for buffer to empty
        UDR0 = data[n]; // load data into usart buffer and send
      }
