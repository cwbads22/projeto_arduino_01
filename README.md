<div align="center">
  <img src="https://github.com/devicons/devicon/blob/master/icons/arduino/arduino-original-wordmark.svg" title="Arduino" alt="Arduino" width="80" height="80"/>
  <img src="https://isocpp.org/assets/images/cpp_logo.png" title="C++" alt="C++" width="80" height="80"/>
 
</div>
<br>

Desenvolvimento de projeto com sensor ultrassônico <i>JSN-SR04T</i> para medição de altura de líquido num recipiente qualquer.<br>
<br>
✅ Código inicial utilizando o Sensor Ultrassônico HC-SR04:
<a href="https://www.makerhero.com/blog/sensor-ultrassonico-hc-sr04-ao-arduino/?srsltid=AfmBOorV8Kk0vW5b5VTlsjOEHVSQiYrYl3kehwFIULlc5DLeviVT2hGr">Link</a>
<br>
<br>
<img src="https://github.com/cwbads22/projeto_arduino_01/blob/main/hc_sr04.png"/>
- Adaptado para não precisar utilizar a biblioteca <i>ultrasonic.h</i><br>
<a href="https://github.com/cwbads22/projeto_arduino_01/tree/main/ultra01">📁/ultra01</a>
<br>
<br>
🎯 Versões do código com implementações até a versão final:<br>
<br>
<a href="https://github.com/cwbads22/projeto_arduino_01/tree/main/med_dist_v0">📁/med_dist_v0</a> - desenvolvimento inicial;<br>
<a href="https://github.com/cwbads22/projeto_arduino_01/tree/main/med_dist_v1">📁/med_dist_v1</a> - ajustes menores;<br>
<a href="https://github.com/cwbads22/projeto_arduino_01/tree/main/med_dist_v3">📁/med_dist_v3<a> - implementação de função de aviso de limite de altura de nivel do recipiente;<br>
<a href="https://github.com/cwbads22/projeto_arduino_01/tree/main/med_dist_vfinal">📁/med_dist_vfinal</a> - cancelamento da leitura contínua do sensor - só atualiza a leitura se houver mudança no nível;<br>
<br>
<b>Proximos passos e implementações</b><br>
<br>
O JSN-SR04T é uma evolução muito interessante do HC-SR04:<br>
🌟 Vantagens do JSN-SR04T:<br>
<br>
- À prova d'água (IP67): Perfeito para ambientes com líquidos!<br>
- Cabo de 2,5m: Sensor pode ficar longe da placa de controle<br>
- Mais estável: Menos interferência e ruído<br>
- Mesmo protocolo: Código praticamente idêntico ao HC-SR04<br>
<br>
🔌 Observações:<br>
<br>
O código vai funcionar quase sem modificação no JSN-SR04T. A pinagem e comunicação são idênticas:<br>
<br>
VCC → 5V<br>
GND → GND<br>
Trig → Pino 4<br>
Echo → Pino 5<br>
<br>
📝 Futuras implentações:<br>
<br>
- Sistema de alarmes com buzzer/LEDs<br>
- Display para visualização local<br>
- WiFi para monitoramento remoto<br>
- Múltiplos recipientes com EEPROM<br>

