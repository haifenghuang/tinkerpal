var s = new Serial(UART0);

s.print('Hello!');
s.write('Hello!');
s.write(65);
s.write(['hello1\n','hello2\n','hello3\n']);