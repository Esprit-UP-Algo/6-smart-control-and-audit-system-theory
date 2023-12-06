#include "arduinocertif.h"
#include <QtSql>
#include <QSqlQuery>


Arduinocertif::Arduinocertif()
{data = "";
    arduino_port_name = "";
    arduino_is_available = false;
    serial = new QSerialPort;

}
QString Arduinocertif::getarduino_port_name()
{
    return arduino_port_name;
}

QSerialPort *Arduinocertif::getserial()
{
    return serial;
}

// Arduino connect_arduino() method
int Arduinocertif::connect_arduino()
{
    foreach (const QSerialPortInfo &serial_port_info, QSerialPortInfo::availablePorts()) {
        if (serial_port_info.hasVendorIdentifier() && serial_port_info.hasProductIdentifier()) {
            if (serial_port_info.vendorIdentifier() == arduino_uno_vendor_id &&
                serial_port_info.productIdentifier() == arduino_uno_producy_id) {
                arduino_is_available = true;
                arduino_port_name = serial_port_info.portName();
            }
        }
    }

    if (arduino_is_available) {
        serial->setPortName(arduino_port_name);
        if (serial->open(QSerialPort::ReadWrite)) {
            serial->setBaudRate(QSerialPort::Baud9600);
            serial->setDataBits(QSerialPort::Data8);
            serial->setParity(QSerialPort::NoParity);
            serial->setStopBits(QSerialPort::OneStop);
            serial->setFlowControl(QSerialPort::NoFlowControl);
            return 0;
        } else {
            qDebug() << "Failed to open serial port:" << serial->errorString();
        }
    } else {
        qDebug() << "Arduino not available.";
    }

    return -1;
}
/*int Arduino::connect_arduino()
{   // recherche du port sur lequel la carte arduino identifée par  arduino_uno_vendor_id
    // est connectée
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
}*/

int Arduinocertif::close_arduino()
{
if (serial->isOpen()) {
serial->close();
return 0; // Success
}
return 1; // Failed to close the serial port
}

QByteArray Arduinocertif::read_from_arduino()
{
if (serial->isReadable()) {
data = serial->readAll();
return data;
}
return nullptr;
}

/*int Arduino::write_to_arduino(QByteArray d) {
    if (serial->isWritable()) {
       serial->write(d);
        qint64 bytesWritten = serial->write(d);

        if (bytesWritten == -1) {
            qDebug() << "Error writing to the serial port:" << serial->errorString();
            return 1; // Failed to write to the serial port
        } else {
            qDebug() << "Data successfully written to Arduino";
            qDebug() << "Number of bytes written:" << bytesWritten;
            return 0; // Success
        }
    } else {
        qDebug() << "Serial port is not writable";
        return 1; // Failed to write to the serial port
    }
}*/
/*void arduinocertif::write_to_arduino() {
    if (connect_arduino() == 0) {
        if (serial->isWritable()) {
            QString query = "SELECT * FROM (SELECT * FROM certificat ORDER BY DURECERTIFICAT DESC) WHERE ROWNUM = 1";

            // Create a QSqlQuery object
            QSqlQuery sqlQuery;
            sqlQuery.exec(query);

            // Check if there's a SQL error
            if (sqlQuery.lastError().isValid()) {
                qDebug() << "SQL Error:" << sqlQuery.lastError().text();
                close_arduino();
                return;  // Exit the function if there's an error
            }
            if (sqlQuery.next()) {
                qDebug() << "Row found in the query";

                // Retrieve the row data using the QSqlRecord
                QSqlRecord record = sqlQuery.record();
                int idCertificat = record.value("IDCERTIFICAT").toInt();
                QString objectifCertificat = record.value("OBJECTIFCERTIFICAT").toString();
                int dureeCertificat = record.value("DURECERTIFICAT").toInt();
                int resultatAudit = record.value("RESULTATDAUDIT").toInt();
                qDebug() << "idCertificat:" << idCertificat;
                qDebug() << "resultatAudit:" << resultatAudit;
                qDebug() << "dureeCertificat:" << dureeCertificat;

                // Create a Certificat object with the retrieved data
                Certificat certificat(idCertificat, resultatAudit, dureeCertificat, objectifCertificat);

                // Send the certificate data to Arduino
                QString data = QString::number(idCertificat)+","+
                               QString::number(resultatAudit) +","+
                               QString::number(dureeCertificat);
                qDebug() << "data:" << data;
                QByteArray dataByteArray = data.toUtf8();

                serial->write(dataByteArray);
             // serial->flush();
           //  serial->waitForBytesWritten(3000);  // Wait for the data to be written

                qDebug() << "Data successfully written to Arduino";
            } else {
                qDebug() << "No data found in the query";
            }
        } else {
            qDebug() << "Serial is not writable!";
        }

        close_arduino();
    } else {
        qDebug() << "Failed to connect to Arduino";
    }
}*/
void Arduinocertif::write_to_arduino() {
    if (connect_arduino() == 0) {
        if (serial->isWritable()) {
            QString query = "SELECT * FROM (SELECT * FROM certificat ORDER BY DURECERTIFICAT DESC) WHERE ROWNUM = 1";

            // Create a QSqlQuery object
            QSqlQuery sqlQuery;
            sqlQuery.exec(query);

            // Check if there's a SQL error
            if (sqlQuery.lastError().isValid()) {
                qDebug() << "SQL Error:" << sqlQuery.lastError().text();
                close_arduino();
                return;  // Exit the function if there's an error
            }
            if (sqlQuery.next()) {
                qDebug() << "Row found in the query";

                // Retrieve the row data using the QSqlRecord
                QSqlRecord record = sqlQuery.record();
                int idCertificat = record.value("IDCERTIFICAT").toInt();
                QString objectifCertificat = record.value("OBJECTIFCERTIFICAT").toString();
                int dureeCertificat = record.value("DURECERTIFICAT").toInt();
                int resultatAudit = record.value("RESULTATDAUDIT").toInt();
                qDebug() << "idCertificat:" << idCertificat;
                qDebug() << "resultatAudit:" << resultatAudit;
                qDebug() << "dureeCertificat:" << dureeCertificat;

                // Create a Certificat object with the retrieved data
                Certificat certificat(idCertificat, resultatAudit, dureeCertificat, objectifCertificat);

                // Send the certificate data to Arduino
               QString data ="id" + QString::number(idCertificat) +
                              "res" + QString::number(resultatAudit) +
                              "du" + QString::number(dureeCertificat) + "\n"  ;
                qDebug() << "data:" << data;
                QByteArray dataByteArray = data.toUtf8();



                serial->write(dataByteArray);

                serial->flush();
                serial->waitForBytesWritten(3000);  // Wait for the data to be written

                qDebug() << "Data successfully written to Arduino";
            } else {
                qDebug() << "No data found in the query";
            }
        } else {
            qDebug() << "Serial is not writable!";
        }

        close_arduino();
    } else {
        qDebug() << "Failed to connect to Arduino";
    }
}
