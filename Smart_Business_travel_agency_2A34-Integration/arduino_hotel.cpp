#include "arduino_hotel.h"

arduino_hotel::arduino_hotel()
{
    data="";
    arduino_port_name="";
    arduino_is_available=false;
    serial=new QSerialPort;
}
QString arduino_hotel::getarduino_port_name()
{
    return arduino_port_name;
}

QSerialPort *arduino_hotel::getserial()
{
   return serial;
}
int arduino_hotel::connect_arduino()
{   // recherche du port sur lequel la carte arduino identifée par  arduino_uno_vendor_id
    // est connectée
    serialbuffer="";
    foreach (const QSerialPortInfo &serial_port_info, QSerialPortInfo::availablePorts()){
           if(serial_port_info.hasVendorIdentifier() && serial_port_info.hasProductIdentifier()){
               if(serial_port_info.vendorIdentifier() == arduino_uno_vendor_id && serial_port_info.productIdentifier()
                       == arduino_uno_producy_id) {
                   arduino_is_available = true;
                   arduino_port_name=serial_port_info.portName();
               } } }
        qDebug() << "arduino_port_name is :" << arduino_port_name;
        if(arduino_is_available){ // configuration de la communication ( débit...)
            serial->setPortName(arduino_port_name);
            if(serial->open(QSerialPort::ReadWrite)){
                serial->setBaudRate(QSerialPort::Baud9600); // débit : 9600 bits/s
                serial->setDataBits(QSerialPort::Data8); //Longueur des données : 8 bits,
                serial->setParity(QSerialPort::NoParity); //1 bit de parité optionnel
                serial->setStopBits(QSerialPort::OneStop); //Nombre de bits de stop : 1
                serial->setFlowControl(QSerialPort::NoFlowControl);
                return 0;
            }
            return 1;
        }
        return -1;
}

int arduino_hotel::close_arduino()

{

    if(serial->isOpen()){
            serial->close();
            return 0;
        }
    return 1;


}


 QByteArray arduino_hotel::read_from_arduino()
{

    if(serial->isReadable()){
        serial->waitForReadyRead(10);
         data=serial->readAll();
         return data;
    }
 }

QString arduino_hotel::cherchercode(int ID)
{
    QSqlDatabase bd = QSqlDatabase::database();
    QString identifiant;
    QSqlQuery query;
    query.prepare("SELECT * FROM HOTEL WHERE ID =:ID");
    query.bindValue(":ID", ID);

         query.exec();
         if (query.next())
         {

             identifiant=query.value(0).toInt();
              return identifiant;
         }
         else {
             return "non";
         }

 }
 QByteArray arduino_hotel::getdata()
 {
     return data;
 }
int arduino_hotel::write_to_arduino( QByteArray d)

{

    if(serial->isWritable()){
        serial->write(d);  // envoyer des donnés vers Arduino
    }else{
        qDebug() << "Couldn't write to serial!";
    }


}
QString arduino_hotel::chercher(int ID)
{

    QSqlDatabase db = QSqlDatabase::database();
    QString nom;
    QSqlQuery query;
    query.prepare("SELECT * FROM HOTEL WHERE ID =:ID");
    query.bindValue(":ID", ID);
        query.exec();
        if (query.next())
        {

            nom=query.value(0).toString();
             return nom;
        }
        else {
            return "non";
        }
}
