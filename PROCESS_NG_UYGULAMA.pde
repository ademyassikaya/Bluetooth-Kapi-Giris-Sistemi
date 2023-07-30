import javax.swing.JOptionPane;
import processing.serial.*;

Serial myPort; // Bluetooth modülüne bağlanmak için seri port nesnesi
String portName = "COM9"; // Arduino'nun bağlı olduğu seri port adı

void setup() {
  size(400, 400);
  background(255);
  
  // Kullanıcıdan sayı girmesini isteyen bir pencere oluştur
  String input = JOptionPane.showInputDialog("Lütfen bir sayı girin:");
  
  // Girilen değeri integer'a dönüştür ve number değişkenine ata
  int number = parseInt(input);
  
  // Bluetooth modülüne bağlan
  myPort = new Serial(this, portName, 9600); // Seri portu aç ve hızını ayarla
  
  // Girilen sayı "3214" ise "a" karakterini Bluetooth modülüne gönder
  if (number == 3214) {
    myPort.write('a'); // "a" karakterini Bluetooth modülüne gönder
  }
}
