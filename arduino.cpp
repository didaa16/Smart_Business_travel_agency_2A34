#include "arduino.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlDatabase>
#include <QObject>
Arduino::Arduino()
{
    data="";
    arduino_port_name="";
    arduino_is_available=false;
    serial=new QSerialPort;
}

QString Arduino::getarduino_port_name()
{
    return arduino_port_name;
}

QSerialPort *Arduino::getserial()
{
   return serial;
}
int Arduino::connect_arduino()
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

int Arduino::close_arduino()

{

    if(serial->isOpen()){
            serial->close();
            return 0;
        }
    return 1;


}


 QByteArray Arduino::read_from_arduino()
{

    if(serial->isReadable()){
        serial->waitForReadyRead(10);
         data=serial->readAll();
         return data;
    }
 }

 QString Arduino::cherchercode(int ID){

     QSqlDatabase bd = QSqlDatabase::database();
 QString matricule;
         QSqlQuery query;
         query.prepare("SELECT CLIENT FROM FACTUREE WHERE ID =:ID");
  query.bindValue(":ID", ID);

         query.exec();
         if (query.next())
         {

             matricule=query.value(0).toInt();
              return matricule;
         }
         else {
             return "non";
         }

 }
 QByteArray Arduino::getdata()
 {
     return data;
 }
int Arduino::write_to_arduino( QByteArray d)

{

    if(serial->isWritable()){
        serial->write(d);  // envoyer des donnés vers Arduino
    }else{
        qDebug() << "Couldn't write to serial!";
    }


}
QString Arduino::chercher(int ID){

    QSqlDatabase bd = QSqlDatabase::database();
QString nom;
        QSqlQuery query;
        query.prepare("SELECT CLIENT FROM FACTUREE WHERE ID =:ID");
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
/*int Employee::cherchercode(int code){

    QSqlDatabase bd = QSqlDatabase::database();
int matricule;
        QSqlQuery query;
        query.prepare("SELECT matricule FROM employee WHERE code =:code");
 query.bindValue(":code", code);

        query.exec();
        if (query.next())
        {

            matricule=query.value(0).toInt();
             return matricule;
        }
        else {
            return -1;
        }

}*/
